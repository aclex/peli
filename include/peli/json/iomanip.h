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
		namespace detail
		{
			template<typename Ch> void pretty_template(std::basic_ostream<Ch>& os)
			{
				os.iword(printer::flag_storage_index()) |= printer::flag::pretty;
			}

			template<typename Ch> void nopretty_template(std::basic_ostream<Ch>& os)
			{
				os.iword(printer::flag_storage_index()) &= !printer::flag::pretty;
			}
		}

		template<typename Ch> std::basic_ostream<Ch>& pretty(std::basic_ostream<Ch>& os)
		{
			detail::pretty_template(os);
			return os;
		}

		template<typename Ch> std::basic_ostream<Ch>& nopretty(std::basic_ostream<Ch>& os)
		{
			detail::nopretty_template(os);
			return os;
		}
	}
}

#endif // PELI_JSON_IOMANIP_H
