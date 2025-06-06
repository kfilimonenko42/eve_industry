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

#ifndef _EVEINDUSTRY_WX_ILISTCTRLLAYOUTMATERIALSBLUEPRINT_HPP_
#define _EVEINDUSTRY_WX_ILISTCTRLLAYOUTMATERIALSBLUEPRINT_HPP_

#include <format>

#include "IListCtrlLayout.hpp"

namespace EVE::Industry
{

	class ListLayoutMaterialsBlueprint : public IListCtrlLayout
	{
	public:
		ListLayoutMaterialsBlueprint() = default;

		void createColumns(wxListCtrl* list) override;
		wxString getItemText(int owner_id, void* container, const long index, const long column) override;
		wxItemAttr* getItemColumnAttr(void* container, const long index, const long column) override;
		int getItemImage(void* container, const long index, const std::map<std::uint32_t, size_t>& vIdsIcons) override;
		void copyToClipboard(void* container, const std::vector<long>& lines, const std::vector<long>& columns) override;
		void deleteSelectedListItems(void* container, std::vector<long>& lines) override;
		void activateListItem(void* container, const long index, wxWindow* parent) override;
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_WX_ILISTCTRLLAYOUTMATERIALSBLUEPRINT_HPP_