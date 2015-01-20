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

#ifndef PELI_JSON_VALUE_H
#define PELI_JSON_VALUE_H

#include <type_traits>

#include <peli/detail/value_shell.h>
#include <peli/detail/variant_value/value_factory.h>

namespace peli
{
	namespace json
	{
		namespace detail
		{
			struct deduction_helper
			{
				array operator()(array);
				number operator()(number);
				bool operator()(bool);

				template<typename Ch> basic_object<Ch> operator()(basic_object<Ch>);
				template<typename Ch> std::basic_string<Ch> operator()(std::basic_string<Ch>);

				template<typename U,
				class = typename std::enable_if<std::is_convertible<array, U>::value>::type>
				array operator()(U);

				template<typename U,
				class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
				number operator()(U);

				template<typename U, typename Ch,
				class = typename std::enable_if<std::is_convertible<basic_object<Ch>, U>::value>::type>
				basic_object<Ch> operator()(U);

				template<typename U, typename Ch,
				class = typename std::enable_if<std::is_convertible<std::basic_string<Ch>, U>::value>::type>
				std::basic_string<Ch> operator()(U);
			};
		}

		class value;
		template<typename T> value make_value();

		class value : public peli::detail::value_shell<peli::detail::variant_value::value_factory, detail::deduction_helper>
		{
			using peli::detail::value_shell<peli::detail::variant_value::value_factory, detail::deduction_helper>::value_shell;

			template<typename T> friend value make_value()
			{
				value v;
				value::reset<T>(v);
				return v;
			}
		};
	}
}

#endif // PELI_JSON_VALUE_H
