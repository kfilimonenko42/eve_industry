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

#include "FormAppraisal.hpp"
#include "WxTextToVectorStr.hpp"
#include "VectorStrToTypeIndustry.hpp"
#include "wxVirtualListCtrl.hpp"
#include "ListLayout_MaterialsAppraisal.hpp"
#include "TotalValues.hpp"
#include "StringTools.hpp"
#include "RegionPanel.hpp"
#include "SolarSystemPanel.hpp"
#include "StationPanel.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::MaterialAppraisal>;

EVE::Industry::FormAppraisal::FormAppraisal(wxWindow* parent)
	: wxWindow(parent, wxID_ANY)
{
	createControls();
}

void EVE::Industry::FormAppraisal::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::FormAppraisal::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::FormAppraisal::updatePrices()
{
	m_Materials.setPrices();
	refreshList();
	updateTotalLabels();
}

void EVE::Industry::FormAppraisal::updateImages()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	m_Materials.setImages(_list);
}

void EVE::Industry::FormAppraisal::createControls()
{
	wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY);
	splitter->SetSashGravity(0.2);
	splitter->SetMinimumPaneSize(200);

	wxPanel* m_leftPanel = new wxPanel(splitter, wxID_ANY, wxDefaultPosition);
	wxPanel* m_btnPanel = new wxPanel(m_leftPanel, wxID_ANY);
	wxPanel* m_rightPanel = new wxPanel(splitter, wxID_ANY);
	
	m_RegionPanel = new RegionPanel(m_leftPanel);
	m_SolarSystemPanel = new SolarSystemPanel(m_leftPanel);
	dynamic_cast<SolarSystemPanel*>(m_SolarSystemPanel)->bindRegionPanel(m_RegionPanel);
	m_StationPanel = new StationPanel(m_leftPanel);
	dynamic_cast<StationPanel*>(m_StationPanel)->bindRegionPanel(m_RegionPanel);
	dynamic_cast<StationPanel*>(m_StationPanel)->bindSolarSystemPanel(m_SolarSystemPanel);

	wxButton* m_btn_Submit = new wxButton(m_btnPanel, wxID_ANY, "Submit", wxDefaultPosition, wxDefaultSize);
	m_btn_Submit->Bind(wxEVT_BUTTON, &FormAppraisal::OnSubmit, this);

	wxButton* m_btn_Clear = new wxButton(m_btnPanel, wxID_ANY, "Clear", wxDefaultPosition, wxDefaultSize);
	m_btn_Clear->Bind(wxEVT_BUTTON, &FormAppraisal::OnClear, this);

	m_TypesText = new wxTextCtrl(m_leftPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2 | wxTE_NOHIDESEL | wxTE_PROCESS_TAB);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer->Add(m_btn_Submit);
	btn_sizer->AddStretchSpacer();
	btn_sizer->Add(m_btn_Clear);
	m_btnPanel->SetSizer(btn_sizer);

	wxBoxSizer* left_sizer = new wxBoxSizer(wxVERTICAL);
	left_sizer->Add(m_RegionPanel, 0, wxALL, 1);
	left_sizer->Add(m_SolarSystemPanel, 0, wxALL, 1);
	left_sizer->Add(m_StationPanel, 0, wxALL, 1);
	left_sizer->Add(m_btnPanel, 0, wxALIGN_RIGHT | wxALL, 5);
	left_sizer->Add(m_TypesText, 1, wxEXPAND | wxALL, 5);
	m_leftPanel->SetSizer(left_sizer);

	m_VirtualList = new vListCtrl(
		m_rightPanel,
		std::make_unique<ListLayoutMaterialsAppraisal>(),
		&m_Materials.get(),
		wxDefaultPosition,
		wxSize(200, 200));

	std::function<void()> updatePricesMethod = std::bind(&FormAppraisal::updatePrices, this);
	std::function<void()> updateImageMethod = std::bind(&FormAppraisal::updateImages, this);

	m_Materials.addUpdater(std::make_unique<PriceUpdater>(updatePricesMethod, m_EsiSettings));
	m_Materials.addUpdater(std::make_unique<ImagesUpdater>(updateImageMethod));

	wxPanel* _panelResults = new wxPanel(m_rightPanel);

	wxFont font = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	m_TotalPriceSell = new wxStaticText(_panelResults, wxID_ANY, "Total Price (sell): - ");
	m_TotalPriceSell->SetFont(font);
	m_TotalPriceBuy = new wxStaticText(_panelResults, wxID_ANY, "Total Price (buy): - ");
	m_TotalPriceBuy->SetFont(font);

	wxBoxSizer* _resultSizer = new wxBoxSizer(wxVERTICAL);
	_resultSizer->AddSpacer(5);
	_resultSizer->Add(m_TotalPriceSell, 0, wxEXPAND);
	_resultSizer->AddSpacer(5);
	_resultSizer->Add(m_TotalPriceBuy, 0, wxEXPAND);
	_resultSizer->AddSpacer(5);
	_panelResults->SetSizer(_resultSizer);

	wxBoxSizer* right_sizer = new wxBoxSizer(wxVERTICAL);
	right_sizer->Add(m_VirtualList, 1, wxEXPAND | wxALL, 5);
	right_sizer->Add(_panelResults, 0, wxEXPAND | wxLEFT | wxBottom | wxRight, 5);
	m_rightPanel->SetSizer(right_sizer);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxVERTICAL);
	base_sizer->Add(splitter, 1, wxEXPAND);

	splitter->SplitVertically(m_leftPanel, m_rightPanel);

	this->SetSizer(base_sizer);
	base_sizer->SetSizeHints(this);
}

void EVE::Industry::FormAppraisal::updateTotalLabels()
{
	m_TotalPriceSell->SetLabelText(std::format(std::locale(""), "Total Price (sell): {:.2Lf}", totalPriceSell(m_Materials.get())));
	m_TotalPriceBuy->SetLabelText(std::format(std::locale(""), "Total Price (buy): {:.2Lf}", totalPriceBuy(m_Materials.get())));
}

void EVE::Industry::FormAppraisal::OnSubmit(wxCommandEvent& event)
{ 
	m_Materials.clear();

	const BaseRecord& region = dynamic_cast<RegionPanel*>(m_RegionPanel)->get();
	const BaseRecord& solSystem = dynamic_cast<SolarSystemPanel*>(m_SolarSystemPanel)->get();
	const BaseRecord& station = dynamic_cast<StationPanel*>(m_StationPanel)->get();

	if (region.id() == 0)
	{
		wxMessageBox("set 'region'");
		return;
	}

	m_EsiSettings.m_RegionID = region.id();
	m_EsiSettings.m_SolarSystemID = solSystem.id();
	m_EsiSettings.m_StationID = station.id();

	std::vector<std::string> _str_types;
	std::vector<MaterialProject> _types;

	WxTextToVectorStr textToVector{};
	textToVector(m_TypesText, _str_types);

	VectorStrToTypeIndustry strsToTypes{};
	strsToTypes(_str_types, _types);

	std::vector<MaterialAppraisal> _tmp;
	for (auto& element : _types)
	{
		_tmp.emplace_back(std::forward<TypeRecord>(element.m_Type), element.m_Type.getQuantity());
	}
	m_Materials.setEsiSettings(m_EsiSettings);
	m_Materials.update(std::move(_tmp));

	this->updateList();
}

void EVE::Industry::FormAppraisal::OnClear(wxCommandEvent& event)
{
	m_TypesText->Clear();
}