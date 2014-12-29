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

#ifndef PELI_DETAIL_VARIANT_VALUE_VALUE_HOLDER_TEMPLATE_H
#define PELI_DETAIL_VARIANT_VALUE_VALUE_HOLDER_TEMPLATE_H

#include <type_traits>

#include <peli/detail/variant_value/value_holder.h>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			template<typename T> class value_holder_template : public value_holder
			{
			public:
				explicit value_holder_template(const T& v) : m_value(v) { }

				template<typename U,
				typename Unref = typename std::remove_reference<U>::type,
				typename V = typename std::enable_if<std::is_same<Unref, T>::value, U>::type>
				V variant_as()
				{
					return m_value;
				}

				template<typename U,
				typename Unref = typename std::remove_reference<U>::type,
				typename V = typename std::enable_if<std::is_same<Unref, T>::value, U>::type>
				V variant_as() const
				{
					return m_value;
				}

				const std::type_info& type_info() const override
				{
					return typeid(T);
				}

			private:
				T m_value;
			};
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_VALUE_HOLDER_TEMPLATE_H
