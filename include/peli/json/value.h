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
		class value : public peli::variant_type
		<
			bool,
			json::number,
			std::string, std::wstring,
			json::array,
			json::object, json::wobject
		>
		{
		public:
			using variant_type = peli::variant_type
			<
			bool,
			json::number,
			std::string, std::wstring,
			json::array,
			json::object, json::wobject
			>;

			using variant_type::variant_type;

			bool null() const noexcept
			{
				return peli::is_empty(*this);
			}
		};

		template<typename T> inline value make_value()
		{
			return value(T());
		}
	}
}

#include <peli/json/value.tcc>

#endif // PELI_JSON_VALUE_H
