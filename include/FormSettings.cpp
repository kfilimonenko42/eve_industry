#include "FormSettings.hpp"

EVE::APPSETTINGS::FormSettings::FormSettings(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, "Settings")
{
	createControls();
}

void EVE::APPSETTINGS::FormSettings::createControls()
{
	m_ListBook = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxSize(600,400), wxLB_LEFT);
	addMainPage();

	wxPanel* m_btnPanel = new wxPanel(this, wxID_ANY);
	wxButton* m_btn_Ok = new wxButton(m_btnPanel, wxID_ANY, "OK", wxDefaultPosition, wxDefaultSize);
	m_btn_Ok->Bind(wxEVT_BUTTON, &FormSettings::OnOk, this);
	wxButton* m_btn_Cancel = new wxButton(m_btnPanel, wxID_ANY, "Cancel", wxDefaultPosition, wxDefaultSize);
	m_btn_Cancel->Bind(wxEVT_BUTTON, &FormSettings::OnCancel, this);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	btn_sizer->Add(m_btn_Ok);
	btn_sizer->AddStretchSpacer();
	btn_sizer->Add(m_btn_Cancel);
	m_btnPanel->SetSizer(btn_sizer);

	wxBoxSizer* base_sizer = new wxBoxSizer(wxVERTICAL);
	base_sizer->Add(m_ListBook, 1, wxEXPAND | wxALL, 5);
	base_sizer->Add(m_btnPanel, 0, wxALIGN_RIGHT | wxALL, 5);

	this->SetSizerAndFit(base_sizer);
}

void EVE::APPSETTINGS::FormSettings::addMainPage()
{
	const auto& _settings = Settings::Instance();

	wxWindow* mainPage = new wxWindow(m_ListBook, wxID_ANY);

	wxGridSizer* sizer = new wxGridSizer(0, 2, wxSize(0,0));

	wxStaticText* lblAssetsLocalization = new wxStaticText(mainPage, wxID_ANY, "Assets Localization (need restart):");
	for (const auto& _elem : LocalizationList)
	{
		m_arrAssetsLocalization.Add(_elem.second);
	}
	const std::string keyLoc = stringFromEnum(LocalizationList, _settings.locTag());
	const auto indexLoc = m_arrAssetsLocalization.Index(keyLoc);
	m_cAssetsLocalization = new wxChoice(mainPage, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_arrAssetsLocalization);
	m_cAssetsLocalization->SetSelection(indexLoc);

	sizer->Add(lblAssetsLocalization);
	sizer->Add(m_cAssetsLocalization);

	m_ListBook->AddPage(mainPage, "Main");
	mainPage->SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void EVE::APPSETTINGS::FormSettings::OnOk(wxCommandEvent& event)
{
	formOk();
}

void EVE::APPSETTINGS::FormSettings::OnCancel(wxCommandEvent& event)
{
	formCancel();
}

void EVE::APPSETTINGS::FormSettings::formOk()
{
	auto& _settings = Settings::Instance();

	const auto indexLoc = m_cAssetsLocalization->GetSelection();
	std::string locTag;
	enumFromString(LocalizationList, m_arrAssetsLocalization[indexLoc].ToStdString(), locTag);
	_settings.setLocTag(locTag);

	_settings.save();

	EndModal(wxID_OK);
}

void EVE::APPSETTINGS::FormSettings::formCancel()
{
	EndModal(wxID_CLOSE);
}
