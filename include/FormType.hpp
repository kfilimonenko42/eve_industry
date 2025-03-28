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

#ifndef _EVEINDUSTRY_FORMTYPE_HPP_
#define _EVEINDUSTRY_FORMTYPE_HPP_

#include <string>
#include <format>
#include <wx/wx.h>
#include <wx/minifram.h>
#include <wx/imagpng.h>
#include <wx/notebook.h>

#include "TypeRecord.hpp"

namespace EVE::Industry
{

	class FormType : public wxMiniFrame
	{
	public:
		FormType(const TypeRecord& type, wxWindow* parent);
		~FormType() override = default;

		FormType(const FormType& tmp) = delete;
		FormType& operator=(const FormType& tmp) = delete;
		FormType(FormType&& tmp) = delete;
		FormType& operator=(FormType&& tmp) = delete;

	private:
		void createControls();

	private:
		TypeRecord m_Type;
		wxPanel* m_MainPanel{};
		wxPanel* m_HeaderPanel{};
		wxNotebook* m_baseNotebook{};

		wxWindow* m_PageHeader{};
		wxWindow* m_PageDescription{};
		wxWindow* m_PageIndustry{};
		wxWindow* m_PagePISchema{};
	};

}

#endif // _EVEINDUSTRY_FORMTYPE_HPP_