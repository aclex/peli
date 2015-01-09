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

#include <peli/detail/printer/tray.h>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			template<typename T> class value_holder_template : public value_holder
			{
			public:
				value_holder_template() noexcept { }
				value_holder_template(const value_holder_template& v) : m_value(v.m_value) { }
				explicit value_holder_template(const T& v) : m_value(v) { }

				template<typename U,
				typename = typename std::enable_if<!std::is_const<U>::value>::type,
				typename = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
				U variant_as() noexcept
				{
					return m_value;
				}

				template<typename U,
				typename = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
				U variant_as() const noexcept
				{
					return m_value;
				}

				bool operator==(const value_holder_template& rhs) const noexcept
				{
					return m_value == rhs.m_value;
				}

				bool operator!=(const value_holder_template& rhs) const noexcept
				{
					return !operator==(rhs);
				}

				value_holder* clone() const override
				{
					return new value_holder_template(*this);
				}

				void print(printer::tray* t) const override
				{
					t->put(m_value);
				}

				const std::type_info& type_info() const noexcept override
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