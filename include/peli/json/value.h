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

#include <string>
#include <type_traits>

#include <peli/value_basics.h>

#include <peli/json/object.h>
#include <peli/json/array.h>
#include <peli/json/number.h>

namespace peli
{
	namespace json
	{
		template<typename Ch> class basic_value : public peli::variant_type
		<
			bool,
			json::number,
			std::basic_string<Ch>,
			json::basic_array<Ch>,
			json::basic_object<Ch>
		>
		{
		public:
			using variant_type = peli::variant_type
			<
				bool,
				json::number,
				std::basic_string<Ch>,
				json::basic_array<Ch>,
				json::basic_object<Ch>
			>;

			using variant_type::variant_type;

			bool null() const noexcept
			{
				return peli::is_empty(*this);
			}
		};

		typedef basic_value<char> value;
		typedef basic_value<wchar_t> wvalue;

		template<typename T, class ValueType = value> inline ValueType make_value()
		{
			return ValueType(T());
		}
	}
}

#include <peli/json/value.tcc>

#endif // PELI_JSON_VALUE_H
