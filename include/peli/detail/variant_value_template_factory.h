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

#ifndef PELI_DETAIL_VARIANT_VALUE_TEMPLATE_FACTORY_H
#define PELI_DETAIL_VARIANT_VALUE_TEMPLATE_FACTORY_H

#include <memory>

#include <peli/detail/variant_value_template.h>

namespace peli
{
	namespace detail
	{
		struct variant_value_template_factory
		{
			typedef variant_value variant_value_type;

			template <typename T> std::shared_ptr<variant_value_type> create(const T& op)
			{
				return std::make_shared<variant_value_template<T>>(op);
			}
		};
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_TEMPLATE_FACTORY_H
