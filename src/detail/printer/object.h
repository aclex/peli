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

#ifndef PELI_DETAIL_PRINTER_OBJECT_H
#define PELI_DETAIL_PRINTER_OBJECT_H

#include <ostream>

#include "peli/json/object.h"
#include "peli/json/value.h"
#include "peli/json/iomanip.h"

#include "detail/printer/util.h"
#include "detail/printer/string.h"

namespace peli
{
	namespace detail
	{
		namespace printer
		{
			template<typename Ch> class head<Ch, peli::json::basic_object<Ch>>
			{
			public:
				static void print(std::basic_ostream<Ch>& os, const peli::json::basic_object<Ch>& obj)
				{
					const bool we_are_pretty = os.iword(geti()) & flag::pretty;

					os << s_left_curly;
					if (we_are_pretty)
					{
						os << std::endl;
					}

					for (auto it = obj.cbegin(); it != obj.cend(); ++it)
					{
						if (we_are_pretty)
							os << "\t";

						printer::head<Ch, std::basic_string<Ch>>::print(os, it->first);

						if (we_are_pretty)
							os << " ";

						os << s_colon;

						if (we_are_pretty)
							os << " ";

						os << it->second;

						if (it != --obj.cend())
							os << s_comma;

						if (we_are_pretty)
						{
							os << std::endl;
						}
					}

					os << s_right_curly;
				}

			private:
				static const Ch s_left_curly = 0x7b; // '{'
				static const Ch s_right_curly = 0x7d; // '}'
				static const Ch s_colon = 0x3a; // ':'
				static const Ch s_comma = 0x2c; // ','
			};
		}
	}
}

#endif // PELI_DETAIL_PRINTER_OBJECT_H