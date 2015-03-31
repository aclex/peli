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

#ifndef PELI_DETAIL_PRINTER_PRINTER_H
#define PELI_DETAIL_PRINTER_PRINTER_H

#include <ostream>
#include <stdexcept>
#include <type_traits>

#include "peli/detail/printer/tray.h"

#include "json/detail/printer/object.h"
#include "json/detail/printer/string.h"
#include "json/detail/printer/array.h"
#include "json/detail/printer/number.h"
#include "json/detail/printer/boolean.h"
#include "json/detail/printer/null.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				template<typename Ch> class throwing_printer
				{
				public:
					template <typename ChType,
						class = typename std::enable_if<!std::is_same<ChType, Ch>::value>::type>
					void print(const peli::json::basic_object<ChType>&)
					{
						throw std::invalid_argument("Incompatible character types of stream and stored value");
					}

					template<typename ChType,
						class = typename std::enable_if<!std::is_same<ChType, Ch>::value>::type>
					void print(const std::basic_string<ChType>&)
					{
						throw std::invalid_argument("Incompatible character types of stream and stored value");
					}
				};

				template<typename Ch> class basic_printer : public throwing_printer<Ch>
				{
				public:
					basic_printer(std::basic_ostream<Ch>& os) : m_os(os) { }

					using throwing_printer<Ch>::print;
					template<typename U> void print(const U& v)
					{
						printer::head<U>::print(m_os, v);
					}

					void print()
					{
						printer::head<void>::print(m_os);
					}

				private:
					std::basic_ostream<Ch>& m_os;
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_PRINTER_H
