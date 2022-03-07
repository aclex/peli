/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014-2022  Alexey Chernov <4ernov@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
