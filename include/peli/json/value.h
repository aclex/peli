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

#include <peli/detail/value_shell.h>
#include <peli/detail/variant_value/value_factory.h>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			struct value_factory;
		}
	}

	namespace json
	{
		class value : public detail::value_shell<detail::variant_value::value_factory>
		{
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
