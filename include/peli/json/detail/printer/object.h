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
					template<class Visitor> static void print(Visitor& v, const json::basic_object<typename Visitor::char_type>& obj)
					{
						using namespace special_chars;

						using char_type = typename Visitor::char_type;

						put_structure_newline(v);

						v.putc(left_curly);

						if (!obj.empty())
							put_newline(v);
						else
							put_space(v);

						v.increase_tab_level();

						for (auto it = obj.cbegin(); it != obj.cend(); ++it)
						{
							put_tab_spacing(v);
							printer::head<std::basic_string<char_type>>::print(v, it->first);

							put_space(v);

							v.putc(colon);

							v.set_need_structure_period(true);
							peli::visit(v, it->second);
							v.set_need_structure_period(false);

							if (it != --obj.cend())
								v.putc(comma);

							put_newline(v);
						}

						v.decrease_tab_level();

						put_tab_spacing(v);

						v.putc(right_curly);
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_OBJECT_H
