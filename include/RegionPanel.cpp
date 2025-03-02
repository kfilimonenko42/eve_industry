#include "RegionPanel.hpp"
#include "FormSelectRegion.hpp"

EVE::Industry::RegionPanel::RegionPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	createControls();
}

const EVE::Industry::BaseRecord& EVE::Industry::RegionPanel::get() const
{
	return m_Region;
}

void EVE::Industry::RegionPanel::createControls()
{
	wxStaticText* lblRegionName = new wxStaticText(this, wxID_ANY, "Region: ", wxDefaultPosition, wxSize(40, 19));
	m_RegionName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 24), wxTE_READONLY);

	wxButton* m_btnClear = new wxButton(this, wxID_ANY, "x", wxDefaultPosition, wxSize(24, 24));
	m_btnClear->Bind(wxEVT_BUTTON, &RegionPanel::OnClear, this);

	wxButton* m_btnSelect = new wxButton(this, wxID_ANY, "...", wxDefaultPosition, wxSize(24, 24));
	m_btnSelect->Bind(wxEVT_BUTTON, &RegionPanel::OnSelect, this);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxHORIZONTAL);
	base_sizer->Add(lblRegionName, 0, wxALL, 5);
	base_sizer->Add(m_RegionName);
	base_sizer->Add(m_btnClear);
	base_sizer->Add(m_btnSelect);
	this->SetSizer(base_sizer);
}

void EVE::Industry::RegionPanel::OnClear(wxCommandEvent& event)
{
	m_Region = BaseRecord();
	m_RegionName->Clear();
}

void EVE::Industry::RegionPanel::OnSelect(wxCommandEvent& event)
{
	std::unique_ptr<FormSelectRegion> dialog = std::make_unique<FormSelectRegion>(this);

	if (dialog->ShowModal() == wxID_OK)
	{
		m_Region = dialog->get();
		m_RegionName->SetValue(m_Region.name());
	}
}
