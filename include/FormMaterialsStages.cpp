#include "FormMaterialsStages.hpp"
#include "ListLayout_AvailableMaterials.hpp"
#include "wxVirtualListCtrl.hpp"

using vListCtrl = wxVirtualListCtrl<EVE::Industry::MaterialProject>;

EVE::Industry::FormMaterialsStages::FormMaterialsStages(std::vector<MaterialProject>&& materials)
	: wxDialog(nullptr, wxID_ANY, "materials for stages", wxDefaultPosition, wxSize(1024, 800))
{
	createControls();
	m_Materials.update(std::move(materials));
	updateList();
}

void EVE::Industry::FormMaterialsStages::updateList()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	_list->refreshAfterUpdate();
}

void EVE::Industry::FormMaterialsStages::refreshList()
{
	m_VirtualList->Refresh();
}

void EVE::Industry::FormMaterialsStages::updateImages()
{
	auto _list = dynamic_cast<vListCtrl*>(m_VirtualList);
	m_Materials.setImages(_list);
}

void EVE::Industry::FormMaterialsStages::createControls()
{
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);

	wxPanel* _btnPanel1 = new wxPanel(mainPanel);

	wxButton* btnCopyName = new wxButton(_btnPanel1, wxID_ANY, "copy name");
	btnCopyName->Bind(wxEVT_BUTTON, &FormMaterialsStages::OnCopyName, this);

	wxButton* btnCopyQuantity = new wxButton(_btnPanel1, wxID_ANY, "copy quantity");
	btnCopyQuantity->Bind(wxEVT_BUTTON, &FormMaterialsStages::OnCopyQuantity, this);

	wxBoxSizer* _btnPanel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	_btnPanel1Sizer->Add(btnCopyName, 0, wxLeft | wxBottom | wxTop, 5);
	_btnPanel1Sizer->Add(btnCopyQuantity, 0, wxLeft | wxBottom | wxTop, 5);
	_btnPanel1->SetSizer(_btnPanel1Sizer);

	m_VirtualList = new vListCtrl(
		mainPanel,
		std::make_unique<ListLayoutAvailableMaterials>(),
		&m_Materials.get(),
		wxDefaultPosition,
		wxSize(200, 200));

	std::function<void()> updateImageMethod = std::bind(&FormMaterialsStages::updateImages, this);

	m_Materials.addUpdater(std::make_unique<ImagesUpdater>(updateImageMethod));

	wxBoxSizer* mainPanelSizer = new wxBoxSizer(wxVERTICAL);
	mainPanelSizer->Add(_btnPanel1, 0, wxLEFT | wxTOP, 5);
	mainPanelSizer->Add(m_VirtualList, 1, wxEXPAND | wxALL, 5);
	mainPanel->SetSizer(mainPanelSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mainPanel, 1, wxEXPAND);
	this->SetSizer(mainSizer);
}

void EVE::Industry::FormMaterialsStages::OnCopyName(wxCommandEvent& event)
{
	dynamic_cast<vListCtrl*>(m_VirtualList)->copyToClipboardSelected({ 0 });
}

void EVE::Industry::FormMaterialsStages::OnCopyQuantity(wxCommandEvent& event)
{
	dynamic_cast<vListCtrl*>(m_VirtualList)->copyToClipboardSelected({ 2 });
}
