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

#ifndef PELI_DETAIL_VARIANT_VALUE_VALUE_H
#define PELI_DETAIL_VARIANT_VALUE_VALUE_H

#include <stdexcept>
#include <type_traits>

#include <peli/json/object.h>
#include <peli/json/array.h>

#include <peli/detail/variant_value/component.h>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			template<typename... Types> class value : private component<Types>...
			{
			public:
				template <typename T> typename type_tag<T>::type::return_type as()
				{
					return variant_as(type_tag<T>::type::value);
				}

				template <typename T, typename V = typename std::enable_if<std::is_const<T>::value, T>::type>
				typename type_tag<V>::type::return_type as() const
				{
					return variant_as(type_tag<V>::type::value);
				}
			};

			typedef value<json::object, json::array, std::string, bool, long double> json_internal_value;
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_VALUE_H
