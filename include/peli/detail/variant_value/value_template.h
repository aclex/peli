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

#ifndef PELI_DETAIL_VARIANT_VALUE_VALUE_TEMPLATE_H
#define PELI_DETAIL_VARIANT_VALUE_VALUE_TEMPLATE_H

#include <peli/detail/type_traits.h>

#include <peli/detail/variant_value/json.h>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			template <typename T> class value_template : public json_internal_value
			{
				typedef typename type_tag<T>::type inner_type_tag;
				typedef typename type_tag<T>::tag tag;

			public:
				explicit value_template(const T& v) : m_value(v) { }
				T variant_as(inner_type_tag tag) const override
				{
					return m_value;
				}

				T& variant_as(typename type_tag<T>::tag::ref_type tag) override
				{
					return m_value;
				}

				const T& variant_as(typename type_tag<T>::tag::cref_type tag) const override
				{
					return m_value;
				}

			private:
				T m_value;
			};
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_VALUE_TEMPLATE_H
