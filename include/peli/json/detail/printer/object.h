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

#include "peli/json/detail/printer/string.h"
#include "peli/json/detail/printer/stream_routines.h"

#include "peli/json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief `head` specialization for [JSON](https://json.org) object.
				 * \see `head`
				 */
				template<typename Ch> struct head<json::basic_object<Ch>>
				{
					template<typename StreamCh> static void print(std::basic_ostream<StreamCh>& os, const json::basic_object<Ch>& obj)
					{
						using namespace special_chars;

						put_structure_newline(os);

						os.rdbuf()->sputc(left_curly);

						if (!obj.empty())
							put_newline(os);
						else
							put_space(os);

						++(tab_level(os));

						for (auto it = obj.cbegin(); it != obj.cend(); ++it)
						{
							put_tab_spacing(os);
							printer::head<std::basic_string<Ch>>::print(os, it->first);

							put_space(os);

							os.rdbuf()->sputc(colon);

							set_needs_structure_period(os, true);
							os << it->second;
							set_needs_structure_period(os, false);

							if (it != --obj.cend())
								os.rdbuf()->sputc(comma);

							put_newline(os);
						}

						--(tab_level(os));

						put_tab_spacing(os);

						os.rdbuf()->sputc(right_curly);
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_OBJECT_H
