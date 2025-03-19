/*
	EVE bulk indy
	Copyright (C) 2025 Kirill Filimonenko

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _WX_VIRTUAL_LISTCTRL_HPP_
#define _WX_VIRTUAL_LISTCTRL_HPP_

#include <vector>
#include <algorithm>
#include <memory>
#include <cassert>
#include <map>
#include <future>
#include <thread>
#include <optional>
#include <functional>
#include <chrono>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <concepts>

#include "ListDataWrapper.hpp"
#include "IListCtrlLayout.hpp"
#include "wxSettings.hpp"
#include "ChronoTools.hpp"
#include "AppraisalContainer.hpp"
#include "BitmapContainer.hpp"

template<typename T>
concept TSupportsEsiSettings = requires(T x) { x.m_EsiSettings; };

template<typename T>
class wxVirtualListCtrl : public wxListCtrl
{
public:
	wxVirtualListCtrl(
		wxWindow* parent,
		std::unique_ptr<IListCtrlLayout> layout,
		EVE::Industry::ListDataWrapper<T>* list,
		const wxPoint& position = wxDefaultPosition,
		const wxSize& size = wxDefaultSize);
	~wxVirtualListCtrl() override = default;

	wxVirtualListCtrl(const wxVirtualListCtrl& tmp) = delete;
	wxVirtualListCtrl& operator=(const wxVirtualListCtrl& tmp) = delete;
	wxVirtualListCtrl(wxVirtualListCtrl&& tmp) = delete;
	wxVirtualListCtrl& operator=(wxVirtualListCtrl&& tmp) = delete;

	void refreshAfterUpdate();
	void updateImages(
		const wxVector<wxBitmapBundle>& vIcons,
		const std::map<std::uint32_t, std::size_t>& vIdsIcons);
	std::size_t size() const;
	std::vector<long> getSelected() const;
	void selectAll();
	void copyToClipboardSelected(const std::vector<long>& columns) const;
	void singleSelection(bool enable = true);

	void OnUpdateTimer(wxTimerEvent& event);
	void setIsPrices(bool value);
	time_point LastRefreshPrice() const;
	void updateLastRefreshPrice(time_point time);
	void setIsImages(bool value);
	time_point LastUpdImages() const;
	void updateLastUpdImages(time_point time);

private:
	void createColumns();

	wxString OnGetItemText(long index, long column) const wxOVERRIDE;
	int OnGetItemImage(long index) const wxOVERRIDE;
	void OnActivateListItem(wxListEvent& event);
	void OnKeyDown(wxListEvent& event);

private:
	wxWindow* m_Parent{};
	wxEvtHandler* m_EvtHandler{};
	std::unique_ptr<IListCtrlLayout> m_Layout;
	EVE::Industry::ListDataWrapper<T>* m_List;
	std::map<std::uint32_t, std::size_t> m_IdsIcons;
	time_point m_LastRefreshPrice;
	time_point m_LastUpdImages;
	bool m_IsPrices{};
	bool m_IsImages{};
};

template<typename T>
inline wxVirtualListCtrl<T>::wxVirtualListCtrl(
	wxWindow* parent,
	std::unique_ptr<IListCtrlLayout> layout,
	EVE::Industry::ListDataWrapper<T>* list,
	const wxPoint& position,
	const wxSize& size)
	: wxListCtrl(parent, wxID_ANY, position, size, wxLC_REPORT | wxLC_VIRTUAL),
	m_Parent{ parent }, m_Layout{ std::move(layout) }, m_List{ list },
	m_LastRefreshPrice{ std::chrono::high_resolution_clock::now() },
	m_LastUpdImages{ std::chrono::high_resolution_clock::now() }
{
	createColumns();
	this->Bind(wxEVT_LIST_ITEM_ACTIVATED, &wxVirtualListCtrl<T>::OnActivateListItem, this);
	this->Bind(wxEVT_LIST_KEY_DOWN, &wxVirtualListCtrl<T>::OnKeyDown, this);
}

template<typename T>
inline void wxVirtualListCtrl<T>::refreshAfterUpdate()
{
	this->SetItemCount(m_List->size());
	this->Refresh();

	if constexpr (TSupportsEsiSettings<T>)
	{
		if (this->m_IsPrices)
		{
			m_List->sendUpdatePrices(this->GetId());
		}
	}

	if (this->m_IsImages)
	{
		m_List->sendUpdateImages(this->GetId());
	}
}

template<typename T>
inline void wxVirtualListCtrl<T>::updateImages(
	const wxVector<wxBitmapBundle>& vIcons,
	const std::map<std::uint32_t, std::size_t>& vIdsIcons)
{
	m_IdsIcons = vIdsIcons;
	this->SetSmallImages(vIcons);
}

template<typename T>
inline std::size_t wxVirtualListCtrl<T>::size() const
{
	assert(m_List);
	return m_List->size();
}

template<typename T>
inline std::vector<long> wxVirtualListCtrl<T>::getSelected() const
{
	std::vector<long> selected;

	long item = -1;
	for (;;)
	{
		item = this->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (item == -1) break;

		selected.push_back(item);
	}

	return selected;
}

template<typename T>
inline void wxVirtualListCtrl<T>::selectAll()
{
	const auto _count = this->GetItemCount();

	if (_count <= 0)
	{
		return;
	}

	for (auto index = 0; index < _count; ++index)
	{
		this->SetItemState(index, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	}
}

template<typename T>
inline void wxVirtualListCtrl<T>::copyToClipboardSelected(const std::vector<long>& columns) const
{
	void* tmp = reinterpret_cast<void*>(&(m_List->get()));
	const std::vector<long> items = this->getSelected();
	return m_Layout->copyToClipboard(tmp, items, columns);
}

template<typename T>
inline void wxVirtualListCtrl<T>::singleSelection(bool enable)
{
	this->SetSingleStyle(wxLC_SINGLE_SEL, enable);
}

template<typename T>
inline void wxVirtualListCtrl<T>::OnUpdateTimer(wxTimerEvent& event)
{
	const int list_id = this->GetId();

	bool needRefresh{};
	if constexpr (TSupportsEsiSettings<T>)
	{
		auto& appContainer = EVE::Industry::AppraisalContainer::Instance();
		const auto lastUpdPrice = appContainer.lastUpdate(list_id);
		if (this->m_IsPrices && EVE::Industry::priceUpdOwner(list_id, this->m_LastRefreshPrice))
		{
			this->updateLastRefreshPrice(lastUpdPrice);
			needRefresh = true;
		}
	}

	auto& bitmapContainer = EVE::Industry::BitmapContainer::Instance();
	const auto lastUpdImages = bitmapContainer.lastUpdate(list_id);
	if (this->m_IsImages && EVE::Industry::bitmapUpdOwner(list_id, this->m_LastUpdImages))
	{
		wxVector<wxBitmapBundle> vIcons;
		std::map<std::uint32_t, std::size_t> vIdsIcons;
		bitmapContainer.get16(m_List->ids(), vIcons, vIdsIcons);
		this->updateImages(vIcons, vIdsIcons);
		this->updateLastUpdImages(lastUpdImages);
		needRefresh = true;
	}

	if (needRefresh)
	{
		this->Refresh();
	}
}

template<typename T>
inline void wxVirtualListCtrl<T>::setIsPrices(bool value)
{
	this->m_IsPrices = value;
}

template<typename T>
inline time_point wxVirtualListCtrl<T>::LastRefreshPrice() const
{
	return this->m_LastRefreshPrice;
}

template<typename T>
inline void wxVirtualListCtrl<T>::updateLastRefreshPrice(time_point time)
{
	this->m_LastRefreshPrice = time;
}

template<typename T>
inline void wxVirtualListCtrl<T>::setIsImages(bool value)
{
	this->m_IsImages = value;
}

template<typename T>
inline time_point wxVirtualListCtrl<T>::LastUpdImages() const
{
	return this->m_LastUpdImages;
}

template<typename T>
inline void wxVirtualListCtrl<T>::updateLastUpdImages(time_point time)
{
	this->m_LastUpdImages = time;
}

template<typename T>
inline void wxVirtualListCtrl<T>::createColumns()
{
	m_Layout->createColumns(this);
}

template<typename T>
inline wxString wxVirtualListCtrl<T>::OnGetItemText(long index, long column) const
{
	void* tmp = reinterpret_cast<void*>(&(m_List->get()));
	return m_Layout->getItemText(this->GetId(), tmp, index, column);
}

template<typename T>
inline int wxVirtualListCtrl<T>::OnGetItemImage(long index) const
{
	void* tmp = reinterpret_cast<void*>(&(m_List->get()));
	return m_Layout->getItemImage(tmp, index, m_IdsIcons);
}

template<typename T>
inline void wxVirtualListCtrl<T>::OnActivateListItem(wxListEvent& event)
{
	long index = event.GetIndex();
	if (index >= 0)
	{
		void* tmp = reinterpret_cast<void*>(&(m_List->get()));
		m_Layout->activateListItem(tmp, index, m_Parent);
	}

	event.Skip();
}

template<typename T>
inline void wxVirtualListCtrl<T>::OnKeyDown(wxListEvent& event)
{
	int _key = (int)event.GetKeyCode();

	if (wxGetKeyState(WXK_CONTROL) && _key == 65)
	{
		this->selectAll();
	}
	else if (wxGetKeyState(WXK_DELETE))
	{
		void* tmp = reinterpret_cast<void*>(&(m_List->get()));

		std::vector<long> items = this->getSelected();
		m_Layout->deleteSelectedListItems(tmp, items);

		this->refreshAfterUpdate();
	}

	event.Skip();
}

#endif // _WX_VIRTUAL_LISTCTRL_HPP_