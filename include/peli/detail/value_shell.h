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
#include <memory>

#include <peli/object.h>
#include <peli/array.h>
#include <peli/bad_value_cast.h>

#include <peli/detail/type_traits.h>

namespace peli
{
	namespace detail
	{
		template <class VariantValueFactory> class value_shell
		{
			typedef typename VariantValueFactory::variant_value_type variant_value_type;

		public:
			value_shell() : m_variant_value(nullptr) { }
			explicit value_shell(const object& obj) : m_variant_value(VariantValueFactory::create<object>(obj)) { }
			explicit value_shell(const array& arr) : m_variant_value(VariantValueFactory::create<array>(arr)) { }
			explicit value_shell(const std::string& str) : m_variant_value(VariantValueFactory::create<std::string>(str)) { }
			explicit value_shell(bool b) : m_variant_value(VariantValueFactory::create<bool>(b)) { }
			explicit value_shell(int i) : m_variant_value(VariantValueFactory::create<int>(i)) { }

			template<typename T> friend T value_cast(const value_shell& v)
			{
				if (!v.m_variant_value)
					throw bad_value_cast(type_tag<T>::tag::name, "null");

				return v.m_variant_value->as<T>();
			}

			value_shell& operator[](const std::string& key)
			{
				return m_variant_value->as<object&>()[key];
			}

			const value_shell& operator[](const std::string& key) const
			{
				return m_variant_value->as<const object&>().at(key);
			}

			value_shell& operator[](std::size_t key)
			{
				return m_variant_value->as<array&>()[key];
			}

			const value_shell& operator[](std::size_t key) const
			{
				return m_variant_value->as<const array&>()[key];
			}

		private:
			std::shared_ptr<variant_value_type> m_variant_value;
		};
	}
}

#endif // PELI_DETAIL_VALUE_SHELL_H
