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

#ifndef PELI_DETAIL_VARIANT_VALUE_COMPONENT_H
#define PELI_DETAIL_VARIANT_VALUE_COMPONENT_H

#include <peli/detail/type_traits.h>
#include <peli/bad_value_cast.h>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			template<typename T> class component
			{
			public:
				virtual T variant_as(typename type_tag<T>::tag::type tag) const
				{
					throw bad_value_cast(type_tag<T>::tag::name, "unknown");
				}

				virtual T& variant_as(typename type_tag<T>::tag::ref_type tag)
				{
					throw bad_value_cast(type_tag<T>::tag::name, "unknown");
				}

				virtual const T& variant_as(typename type_tag<T>::tag::cref_type tag) const
				{
					throw bad_value_cast(type_tag<T>::tag::name, "unknown");
				}
			};
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_COMPONENT_H
