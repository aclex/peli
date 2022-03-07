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
