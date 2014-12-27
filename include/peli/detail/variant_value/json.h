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

#ifndef PELI_DETAIL_VARIANT_VALUE_JSON_H
#define PELI_DETAIL_VARIANT_VALUE_JSON_H

#include <string>

#include <peli/json/object.h>
#include <peli/json/array.h>

#include <peli/detail/variant_value/value.h>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			typedef value<json::object, json::array, std::string, bool, long double> json_internal_value;
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_JSON_H
