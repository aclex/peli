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

#ifndef PELI_JSON_ARRAY_H
#define PELI_JSON_ARRAY_H

#include <vector>

namespace peli
{
	namespace json
	{
		template<typename Ch> class basic_value;

		/** \brief [JSON](http://json.org/) array representation template.
		 *
		 * Just an alias of
		 * [`std::vector`](https://en.cppreference.com/w/cpp/container/vector)
		 * of `basic_value`. Depends on the character type used for the value
		 * hierarchy.
		 *
		 * \tparam Ch character type.
		 */
		template<typename Ch> using basic_array = std::vector<basic_value<Ch>>;

		/** \brief `basic_array` specialization for `char`. */
		typedef basic_array<char> array;
		/** \brief `basic_array` specialization for `wchar_t`. */
		typedef basic_array<wchar_t> warray;
	}
}

#endif // PELI_JSON_ARRAY_H
