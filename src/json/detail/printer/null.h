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

#ifndef PELI_DETAIL_PRINTER_NULL_H
#define PELI_DETAIL_PRINTER_NULL_H

#include <array>

#ifndef INTERNAL_VARIANT
#include <variant>
#endif

#include "json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				template<> struct head<void>
				{
				public:
					template<typename Ch> static void print(std::basic_ostream<Ch>& os)
					{
						using namespace special_chars;

						put_structure_space(os);

						static std::array<Ch, 4> null_str {{ n, u, l, l }};

						os.rdbuf()->sputn(null_str.data(), null_str.size());
					}
				};

#ifndef INTERNAL_VARIANT
				template<> class head<std::monostate> : public head<void>
				{
				public:
					template<typename Ch> static void print(std::basic_ostream<Ch>& os, const std::monostate&)
					{
						head<void>::print(os);
					}
				};
#endif
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_NULL_H
