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
					 * \tparam Ch character type of the output stream.
					 */
					template<typename Ch> static void print(std::basic_ostream<Ch>&, const T&)
					{
						static_assert(fake_dependency<T>::value, "Type is not supported for printing");
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_HEAD_H
