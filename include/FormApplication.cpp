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

#include "FormApplication.hpp"
#include "ProjectNew.hpp"
#include "IndustryProject_utility.hpp"
#include "FormProject.hpp"
#include "Assets.hpp"
#include "BitmapContainer.hpp"
#include "FormAppraisal.hpp"
#include "FormSettings.hpp"
#include "Version.hpp"
#include "GithubAPI.hpp"

EVE::Industry::FormApplication::FormApplication()
	: wxFrame(nullptr, wxID_ANY, PROJECT_NAME_STRING)
{
	this->Maximize(true);
	this->SetMinSize(this->FromDIP(wxSize(200, 200)));

	wxImage::AddHandler(new wxPNGHandler);

	AppraisalContainer::Instance();
	BitmapContainer::Instance();
	Log::Logger::Instance();

	createControls();
}

void EVE::Industry::FormApplication::loadAssets()
{
	wxBusyInfo wait("Loading assets...");

	Assets::Instance();
}

void EVE::Industry::FormApplication::OnUpdateCurrentPageText()
{
	wxWindow* currentPage = m_MainBook->GetCurrentPage();
	if (currentPage)
	{
		const std::size_t pageIndex = m_MainBook->GetPageIndex(currentPage);

		FormProject* form = dynamic_cast<FormProject*>(currentPage);
		const IndustryProject& project = form->project();
		const std::string _name = project.name() + (project.getModified() ? " *" : "");
		m_MainBook->SetPageText(
			pageIndex, 
			_name);
	}
}

void EVE::Industry::FormApplication::createControls()
{
	createMenuBar();

	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);

	m_MainBook = new wxAuiNotebook(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_BOTTOM);

	wxBoxSizer* formPanel_sizer = new wxBoxSizer(wxVERTICAL);
	formPanel_sizer->Add(m_MainBook, 1, wxEXPAND);
	mainPanel->SetSizer(formPanel_sizer);

	wxBoxSizer* top_sizer = new wxBoxSizer(wxHORIZONTAL);
	top_sizer->SetMinSize(600, 400);
	top_sizer->Add(mainPanel, 1, wxEXPAND);
	this->SetSizerAndFit(top_sizer);
}

void EVE::Industry::FormApplication::createMenuBar()
{
	this->m_MenuBar = new wxMenuBar();

	// File
	wxMenu* fileMenu = new wxMenu();
	auto newProjectBtn = fileMenu->Append(wxID_ANY, "New project");
	auto openProjectBtn = fileMenu->Append(wxID_ANY, "Open project");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_SAVE);
	fileMenu->Append(wxID_SAVEAS);
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT);

	m_MenuBar->Append(fileMenu, "File");

	// View
	wxMenu* viewMenu = new wxMenu();
	auto appraisalBtn = viewMenu->Append(wxID_ANY, "Appraisal");
	viewMenu->AppendSeparator();
	auto settingsBtn = viewMenu->Append(wxID_ANY, "Settings");

	m_MenuBar->Append(viewMenu, "View");

	// "?"
	wxMenu* helpMenu = new wxMenu();
	helpMenu->Append(wxID_ABOUT);

	m_MenuBar->Append(helpMenu, "?");
	
	this->SetMenuBar(m_MenuBar);

	Bind(wxEVT_MENU, &FormApplication::OnNewProject, this, newProjectBtn->GetId());
	Bind(wxEVT_MENU, &FormApplication::OnOpenProject, this, openProjectBtn->GetId());
	Bind(wxEVT_MENU, &FormApplication::OnSaveProject, this, wxID_SAVE);
	Bind(wxEVT_MENU, &FormApplication::OnSaveAsProject, this, wxID_SAVEAS);
	Bind(wxEVT_MENU, &FormApplication::OnQuit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &FormApplication::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &FormApplication::OnAppraisal, this, appraisalBtn->GetId());
	Bind(wxEVT_MENU, &FormApplication::OnSettings, this, settingsBtn->GetId());
}

void EVE::Industry::FormApplication::OnNewProject(wxCommandEvent& e)
{
	std::string _name = getNewProjectName();
	if (_name.empty())
	{
		return;
	}

	wxWindow* newIndustryForm = new FormProject(this, _name);
	FormProject* form = dynamic_cast<FormProject*>(newIndustryForm);
	std::function<void()> updFunc = std::bind(&FormApplication::OnUpdateCurrentPageText, this);
	form->bindFunUpdPage(updFunc);
	m_MainBook->AddPage(newIndustryForm, _name, true);
}

void EVE::Industry::FormApplication::OnOpenProject(wxCommandEvent& e)
{
	wxWindow* newIndustryForm = new FormProject(this);
	FormProject* form = dynamic_cast<FormProject*>(newIndustryForm);
	if (form->load())
	{ 
		std::function<void()> updFunc = std::bind(&FormApplication::OnUpdateCurrentPageText, this);
		form->bindFunUpdPage(updFunc);
		const std::string _name = form->project().name();
		m_MainBook->AddPage(newIndustryForm, _name, true);
	}
	else
	{
		newIndustryForm->Destroy();
	}
}

void EVE::Industry::FormApplication::OnSaveProject(wxCommandEvent& e)
{
	wxWindow* currentPage = m_MainBook->GetCurrentPage();

	if (currentPage)
	{
		FormProject* form = dynamic_cast<FormProject*>(currentPage);
		form->save();
	}
}

void EVE::Industry::FormApplication::OnSaveAsProject(wxCommandEvent& e)
{
	wxWindow* currentPage = m_MainBook->GetCurrentPage();

	if (currentPage)
	{
		FormProject* form = dynamic_cast<FormProject*>(currentPage);
		form->saveAs();
	}
}

void EVE::Industry::FormApplication::OnQuit(wxCommandEvent& e)
{
	this->Close();
}

void EVE::Industry::FormApplication::OnAbout(wxCommandEvent& e)
{
	//=>
	auto response = std::async(GithubAPI::getTheLatestRelease);
	auto result = response.get();
	int git_version{};
	std::string new_release_link;
	if (result.m_Successful)
	{
		try
		{
			nlohmann::json releaseInfo = nlohmann::json::parse(result.m_Result);
			if (releaseInfo.contains("id"))
			{
				releaseInfo.at("id").get_to(git_version);
			}
			if (releaseInfo.contains("html_url"))
			{
				releaseInfo.at("html_url").get_to(new_release_link);
			}
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}
	//<=

	wxAboutDialogInfo aboutInfo;
	aboutInfo.SetName(PROJECT_NAME_STRING);
	aboutInfo.SetVersion(
		std::format("{}\n{}", VERSION_STRING, SDE_DATE_STRING)
	);
	if (git_version > GITHUB_RELEASE_ID)
	{
		aboutInfo.SetDescription("new version available");
		aboutInfo.SetWebSite(new_release_link);
	}
	else
	{
		aboutInfo.SetWebSite(GITHUB_LINK);
	}
	aboutInfo.AddDeveloper("EVE ign: Kirill Dif");
	wxAboutBox(aboutInfo);
}

void EVE::Industry::FormApplication::OnAppraisal(wxCommandEvent& e)
{
	wxWindow* appraisalForm = new FormAppraisal(this);
	m_MainBook->AddPage(appraisalForm, "Appraisal", true);
}

void EVE::Industry::FormApplication::OnSettings(wxCommandEvent& e)
{
	std::unique_ptr<EVE::APPSETTINGS::FormSettings> dialog = std::make_unique<EVE::APPSETTINGS::FormSettings>(this);
	dialog->ShowModal();
}
