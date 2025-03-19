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

#ifndef _ILISTCTRLLAYOUT_HPP_
#define _ILISTCTRLLAYOUT_HPP_

#include <vector>
#include <string>
#include <utility>
#include <map>
#include <locale>
#include <cstdint>
#include <memory>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/event.h>
#include <wx/clipbrd.h>
#include <wx/menu.h>

#include "AppraisalContainer.hpp"
#include "BitmapContainer.hpp"

class IListCtrlLayout
{
public:
    virtual ~IListCtrlLayout() = default;

    virtual void createColumns(wxListCtrl* list) = 0;
    virtual std::string getItemText(int owner_id, void* container, const long index, const long column) = 0;
    virtual int getItemImage(void* container, const long index, const std::map<std::uint32_t, std::size_t>& vIdsIcons) = 0;
    virtual void copyToClipboard(void* container, const std::vector<long>& lines, const std::vector<long>& columns) = 0;
    virtual void deleteSelectedListItems(void* container, std::vector<long>& lines) = 0;
    virtual void activateListItem(void* container, const long index, wxWindow* parent) = 0;
};

#endif // _ILISTCTRLLAYOUT_HPP_