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
