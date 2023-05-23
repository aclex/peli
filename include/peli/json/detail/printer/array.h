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

#ifndef PELI_DETAIL_PRINTER_ARRAY_H
#define PELI_DETAIL_PRINTER_ARRAY_H

#include "peli/json/array.h"

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
				/** \brief `head` specialization for [JSON](https://json.org) array.
				 * \see `head`
				 */
				template<typename Ch> struct head<json::basic_array<Ch>>
				{
					template<class Visitor> static void print(Visitor& v, const peli::json::basic_array<typename Visitor::char_type>& arr)
					{
						using namespace special_chars;

						if (!arr.empty())
							put_structure_newline(v);
						else
							put_structure_space(v);

						v.putc(left_square);

						if (!arr.empty())
						{
							put_newline(v);

							v.increase_tab_level();

							for (auto it = arr.cbegin(); it != arr.cend(); ++it)
							{
								put_tab_spacing(v);
								peli::visit(v, *it);

								if (it != --arr.cend())
									v.putc(comma);

								put_newline(v);
							}

							v.decrease_tab_level();

							put_tab_spacing(v);
						}

						v.putc(right_square);
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_ARRAY_H
