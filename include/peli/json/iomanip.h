/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014  Alexey Chernov <4ernov@gmail.com>
 *
 * Peli is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PELI_JSON_IOMANIP_H
#define PELI_JSON_IOMANIP_H

#include <ostream>

#include "peli/json/detail/printer/util.h"

namespace peli
{
	namespace json
	{
		/** \brief Stream manipulator enabling pretty printing of [JSON](https://json.org).
		 *
		 * Pretty printing in Peli includes:
		 * - tab-indented text with tab level according to the document hierarchy
		 * - spaces after opening square and curly brace and before closing one, if array or object
		 * contains one element (one space between braces in case of empty structures)
		 * - new lines after opening square and curly brace and before closing one, if array or object contains more, than one element
		 * - new lines before objects and arrays
		 * - spaces after commas, before and after colons
		 *
		 */
		template<typename Ch> std::basic_ostream<Ch>& pretty(std::basic_ostream<Ch>& os)
		{
			os.iword(detail::printer::flag_storage_index()) |= detail::printer::flag::pretty;
			return os;
		}

		/** \brief Stream manipulator disabling pretty printing of [JSON](https://json.org).
		 */
		template<typename Ch> std::basic_ostream<Ch>& nopretty(std::basic_ostream<Ch>& os)
		{
			os.iword(detail::printer::flag_storage_index()) &= !detail::printer::flag::pretty;
			return os;
		}
	}
}

#endif // PELI_JSON_IOMANIP_H
