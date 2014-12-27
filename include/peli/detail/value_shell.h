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

#ifndef PELI_DETAIL_VALUE_SHELL_H
#define PELI_DETAIL_VALUE_SHELL_H

#include <cstddef>
#include <string>

#include <peli/json/object.h>
#include <peli/json/array.h>
#include <peli/bad_value_cast.h>

#include <peli/detail/type_traits.h>

namespace peli
{
	namespace detail
	{
		template <class InternalValueFactory> class value_shell
		{
		public:
			value_shell() : m_internal_value(nullptr) { }
			explicit value_shell(const peli::json::object& obj) : m_internal_value(InternalValueFactory::template create<peli::json::object>(obj)) { }
			explicit value_shell(const peli::json::array& arr) : m_internal_value(InternalValueFactory::template create<peli::json::array>(arr)) { }
			explicit value_shell(const std::string& str) : m_internal_value(InternalValueFactory::template create<std::string>(str)) { }
			explicit value_shell(bool b) : m_internal_value(InternalValueFactory::template create<bool>(b)) { }
			explicit value_shell(int i) : m_internal_value(InternalValueFactory::template create<int>(i)) { }

			bool valid() const
			{
				return m_internal_value->valid();
			}

			template<typename T> explicit operator T()
			{
				if (!m_internal_value)
					throw bad_value_cast(type_tag<T>::tag::name, "null");

				return m_internal_value->template as<T>();
			}

			friend std::istream& operator>>(std::istream& is, value_shell& v)
			{
				delete v.m_internal_value;
				v.m_internal_value = InternalValueFactory::parse(is);
			}

			friend std::wistream& operator>>(std::wistream& is, value_shell& v)
			{
				delete v.m_internal_value;
				v.m_internal_value = InternalValueFactory::parse(is);
			}

			~value_shell() { delete m_internal_value; }

		protected:
			template<typename T> value_shell(type_tag<T>&) : m_internal_value(InternalValueFactory::template create<T>()) { }

		private:
			typename InternalValueFactory::value_type* m_internal_value;
		};
	}
}

#endif // PELI_DETAIL_VALUE_SHELL_H
