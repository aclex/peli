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

#ifndef PELI_DETAIL_PRINTER_BOOLEAN_H
#define PELI_DETAIL_PRINTER_BOOLEAN_H

#include <array>
#include <ostream>

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
