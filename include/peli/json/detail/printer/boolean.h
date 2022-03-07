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

#ifndef PELI_DETAIL_PRINTER_BOOLEAN_H
#define PELI_DETAIL_PRINTER_BOOLEAN_H

#include <array>

#include "peli/json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief `head` specialization for [JSON](https://json.org) boolean value.
				 * \see `head`
				 */
				template<> struct head<bool>
				{
				public:
					template<class Visitor> static void print(Visitor& v, bool b)
					{
						using namespace special_chars;

						using char_type = typename Visitor::char_type;

						put_structure_space(v);

						static constexpr std::array<char_type, 4> true_str {{ t, r, u, e }};
						static constexpr std::array<char_type, 5> false_str {{ f, a, l, s, e }};

						if (b)
							put(v, true_str);
						else
							put(v, false_str);
					}

				private:
					template<class Visitor, std::size_t N> static void put(Visitor& v, const std::array<typename Visitor::char_type, N>& str)
					{
						v.putn(str.data(), str.size());
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_BOOLEAN_H
