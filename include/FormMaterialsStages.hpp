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

#ifndef _EVEINDUSTRY_FORMMATERIALSSTAGES_HPP_
#define _EVEINDUSTRY_FORMMATERIALSSTAGES_HPP_

#include <string>
#include <format>
#include <vector>
#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>

#include "ListDataWrapper.hpp"
#include "MaterialProject.hpp"

namespace EVE::Industry
{

	class FormMaterialsStages : public wxDialog
	{
	public:
		explicit FormMaterialsStages(std::vector<MaterialProject>&& materials);

		void updateList();
		void refreshList();
		void updateImages();

	private:
		void createControls();

		void OnCopyName(wxCommandEvent& event);
		void OnCopyQuantity(wxCommandEvent& event);

	private:
		wxListCtrl* m_VirtualList{};
		ListDataWrapper<MaterialProject> m_Materials;
	};

} // namespace EVE::Industry

#endif // _EVEINDUSTRY_FORMMATERIALSSTAGES_HPP_