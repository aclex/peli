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

#include "json/detail/printer/util.h"
#include "json/detail/printer/string.h"
#include "json/detail/printer/stream_routines.h"

#include "json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				template<typename Ch> struct head<json::basic_object<Ch>> : pretty_head<head, json::basic_object<Ch>>, object_formatter
				{
					template<typename Typewriter,
					typename std::enable_if<std::is_same<typename Typewriter::char_type, Ch>::value, int>::type c = 0>
					static void bounce(Typewriter* tw, const json::basic_object<Ch>& obj)
					{
						using namespace special_chars;

						put_tab_spacing(tw);

						tw->rdbuf->sputc(left_curly);

						if (!obj.empty())
							put_newline(tw);
						else
							put_space(tw);

						++(tw->tab_level);

						for (auto it = obj.cbegin(); it != obj.cend(); ++it)
						{
							put_tab_spacing(tw);

							printer::head<std::basic_string<Ch>>::print(tw, it->first);

							put_space(tw);

							tw->rdbuf->sputc(colon);

							set_structure_newline(tw, true);
							tw->print(it->second);
							set_structure_newline(tw, false);

							if (it != --obj.cend())
								tw->rdbuf->sputc(comma);

							put_newline(tw);
						}

						--(tw->tab_level);

						put_tab_spacing(tw);

						tw->rdbuf->sputc(right_curly);
					}

					template<typename Typewriter,
					typename std::enable_if<!std::is_same<typename Typewriter::char_type, Ch>::value, int>::type c = 0>
					static void bounce(Typewriter*, const json::basic_object<Ch>&)
					{
						throw std::invalid_argument("Incompatible character types.");
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_OBJECT_H
