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

#ifndef PELI_DETAIL_PRINTER_NULL_H
#define PELI_DETAIL_PRINTER_NULL_H

#include <array>

#ifndef INTERNAL_VARIANT
#include <variant>
#endif

#include "peli/json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief `head` specialization for [JSON](https://json.org) null entity.
				 * \see `head`
				 */
				template<> struct head<void>
				{
				public:
					template<class Visitor> static void print(Visitor& v)
					{
						using namespace special_chars;

						put_structure_space(v);

						static std::array<typename Visitor::char_type, 4> null_str {{ n, u, l, l }};

						v.putn(null_str.data(), null_str.size());
					}
				};

#ifndef INTERNAL_VARIANT
				template<> class head<std::monostate> : public head<void>
				{
				public:
					template<class Visitor> static void print(Visitor& v, const std::monostate&)
					{
						head<void>::print(v);
					}
				};
#endif
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_NULL_H
