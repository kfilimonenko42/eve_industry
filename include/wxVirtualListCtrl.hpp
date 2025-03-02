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
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/menu.h>

#include "IListCtrlLayout.hpp"
#include "wxSettings.hpp"

template<typename T>
class wxVirtualListCtrl : public wxListCtrl
{
public:
	wxVirtualListCtrl(
		wxWindow* parent,
		std::unique_ptr<IListCtrlLayout> layout,
		std::vector<T>* list,
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

private:
	void createColumns();

	wxString OnGetItemText(long index, long column) const wxOVERRIDE;
	int OnGetItemImage(long index) const wxOVERRIDE;
	void OnActivateListItem(wxListEvent& event);
	void OnKeyDown(wxListEvent& event);

private:
	wxWindow* m_Parent;
	std::unique_ptr<IListCtrlLayout> m_Layout;
	std::vector<T>* m_List;
	std::map<std::uint32_t, std::size_t> m_IdsIcons;
};

template<typename T>
inline wxVirtualListCtrl<T>::wxVirtualListCtrl(
	wxWindow* parent,
	std::unique_ptr<IListCtrlLayout> layout,
	std::vector<T>* list,
	const wxPoint& position,
	const wxSize& size)
	: wxListCtrl(parent, wxID_ANY, position, size, wxLC_REPORT | wxLC_VIRTUAL),
	m_Parent{ parent }, m_Layout{ std::move(layout) }, m_List{ list }
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
	void* tmp = reinterpret_cast<void*>(m_List);
	const std::vector<long> items = this->getSelected();
	return m_Layout->copyToClipboard(tmp, items, columns);
}

template<typename T>
inline void wxVirtualListCtrl<T>::singleSelection(bool enable)
{
	this->SetSingleStyle(wxLC_SINGLE_SEL, enable);
}

template<typename T>
inline void wxVirtualListCtrl<T>::createColumns()
{
	m_Layout->createColumns(this);
}

template<typename T>
inline wxString wxVirtualListCtrl<T>::OnGetItemText(long index, long column) const
{
	void* tmp = reinterpret_cast<void*>(m_List);
	return m_Layout->getItemText(tmp, index, column);
}

template<typename T>
inline int wxVirtualListCtrl<T>::OnGetItemImage(long index) const
{
	void* tmp = reinterpret_cast<void*>(m_List);
	return m_Layout->getItemImage(tmp, index, m_IdsIcons);
}

template<typename T>
inline void wxVirtualListCtrl<T>::OnActivateListItem(wxListEvent& event)
{
	long index = event.GetIndex();
	if (index >= 0)
	{
		void* tmp = reinterpret_cast<void*>(m_List);
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
		void* tmp = reinterpret_cast<void*>(m_List);

		std::vector<long> items = this->getSelected();
		m_Layout->deleteSelectedListItems(tmp, items);

		this->refreshAfterUpdate();
	}

	event.Skip();
}

#endif // _WX_VIRTUAL_LISTCTRL_HPP_