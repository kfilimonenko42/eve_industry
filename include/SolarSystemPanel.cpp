#include "SolarSystemPanel.hpp"
#include "FormSelectSolarSystem.hpp"
#include "RegionPanel.hpp"

EVE::Industry::SolarSystemPanel::SolarSystemPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	createControls();
}

void EVE::Industry::SolarSystemPanel::bindRegionPanel(wxPanel* regionPanel)
{
	if (regionPanel)
	{
		m_RegionPanel = regionPanel;
	};
}

const EVE::Industry::SolarSystemRecord& EVE::Industry::SolarSystemPanel::get() const
{
	return m_SolarSystem;
}

void EVE::Industry::SolarSystemPanel::createControls()
{
	wxStaticText* lblSolarSystemName = new wxStaticText(this, wxID_ANY, "System: ", wxDefaultPosition, wxSize(40, 19));
	m_SolarSystemName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 24), wxTE_READONLY);

	wxButton* m_btnClear = new wxButton(this, wxID_ANY, "x", wxDefaultPosition, wxSize(24, 24));
	m_btnClear->Bind(wxEVT_BUTTON, &SolarSystemPanel::OnClear, this);

	wxButton* m_btnSelect = new wxButton(this, wxID_ANY, "...", wxDefaultPosition, wxSize(24, 24));
	m_btnSelect->Bind(wxEVT_BUTTON, &SolarSystemPanel::OnSelect, this);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxHORIZONTAL);
	base_sizer->Add(lblSolarSystemName, 0, wxALL, 5);
	base_sizer->Add(m_SolarSystemName);
	base_sizer->Add(m_btnClear);
	base_sizer->Add(m_btnSelect);
	this->SetSizer(base_sizer);
}

void EVE::Industry::SolarSystemPanel::OnClear(wxCommandEvent& event)
{
	m_SolarSystem = SolarSystemRecord();
	m_SolarSystemName->Clear();
}

void EVE::Industry::SolarSystemPanel::OnSelect(wxCommandEvent& event)
{
	const std::uint32_t regionID = m_RegionPanel ? dynamic_cast<RegionPanel*>(m_RegionPanel)->get().id() : 0;
	std::unique_ptr<FormSelectSolarSystem> dialog = std::make_unique<FormSelectSolarSystem>(this, regionID);

	if (dialog->ShowModal() == wxID_OK)
	{
		m_SolarSystem = dialog->get();
		m_SolarSystemName->SetValue(m_SolarSystem.name());
	}
}
