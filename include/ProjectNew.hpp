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

#ifndef _EVEINDUSTRY_PROJECTNEW_HPP_
#define _EVEINDUSTRY_PROJECTNEW_HPP_

#include <memory>
#include <string>

#include "FormProjectName.hpp"

namespace EVE::Industry
{

	[[nodiscard]] inline std::string getNewProjectName()
	{
		std::unique_ptr<FormProjectName> dialog = std::make_unique<FormProjectName>(nullptr);

		if (dialog->ShowModal() == wxID_OK)
		{
			return dialog->get();
		}

		return {};
	}

}

#endif // _EVEINDUSTRY_PROJECTNEW_HPP_