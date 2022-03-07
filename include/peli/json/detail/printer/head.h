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

#ifndef PELI_DETAIL_PRINTER_HEAD_H
#define PELI_DETAIL_PRINTER_HEAD_H

#include "peli/json/detail/printer/stream_routines.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			/** \brief [JSON](https://json.org) printing part. */
			namespace printer
			{
				/** \brief Printing head template.
				 *
				 * Its per-type specializations used to print [JSON](https://json.org) textual
				 * representation of the corresponding type value.
				 *
				 * \tparam T type to print.
				 */
				template<typename T> class head
				{
					/** \brief Fake dependency type to run `static_assert` correctly. */
					template<class> struct fake_dependency : public std::false_type { };

				public:
					/** \brief Printing function.
					 *
					 * Fails to compiled, if called for anything other than
					 * [JSON](https://json.org) type.
					 *
					 * \tparam Visitor visitor type to print with.
					 */
					template<class Visitor> static void print(Visitor&, const T&)
					{
						static_assert(fake_dependency<T>::value, "Type is not supported for printing");
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_HEAD_H
