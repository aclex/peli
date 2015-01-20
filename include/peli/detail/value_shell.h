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

#include <string>

#include <type_traits>
#include <utility>

#include <peli/json/object.h>
#include <peli/json/array.h>
#include <peli/json/number.h>

namespace peli
{
	namespace detail
	{
		template <class InternalValueFactory, typename DeductionHelper> class value_shell
		{
			typedef DeductionHelper deduction_helper;

		public:
			constexpr value_shell() noexcept : m_internal_value(nullptr) { }
			value_shell(const value_shell& v) : m_internal_value(InternalValueFactory::clone(v.m_internal_value)) { }
			value_shell(value_shell&& v) noexcept
			{
				using std::swap;
				swap(m_internal_value, v.m_internal_value);
				v.m_internal_value = nullptr;
			}

			template<typename Ch> explicit value_shell(const peli::json::basic_object<Ch>& obj) :
				m_internal_value(InternalValueFactory::template create<peli::json::basic_object<Ch>>(obj)) { }

			explicit value_shell(const peli::json::array& arr) : m_internal_value(InternalValueFactory::template create<peli::json::array>(arr)) { }

			template<typename Ch> explicit value_shell(const std::basic_string<Ch>& str) :
				m_internal_value(InternalValueFactory::template create<std::basic_string<Ch>>(str)) { }

			template<typename Ch> explicit value_shell(const Ch* str) : value_shell(std::basic_string<Ch>(str)) { }

			explicit value_shell(bool b) : m_internal_value(InternalValueFactory::template create<bool>(b)) { }
			explicit value_shell(json::number i) : m_internal_value(InternalValueFactory::template create<json::number>(i)) { }

			template<typename U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type> explicit value_shell(U i) :
				value_shell(static_cast<json::number>(i)) { }

			value_shell& operator=(value_shell v) noexcept
			{
				using std::swap;
				swap(m_internal_value, v.m_internal_value);

				return *this;
			}

			constexpr bool null() const noexcept
			{
				return m_internal_value == nullptr;
			}

			bool operator==(const value_shell& rhs) const noexcept
			{
				return InternalValueFactory::equal(m_internal_value, rhs.m_internal_value);
			}

			bool operator!=(const value_shell& rhs) const noexcept
			{
				return !operator==(rhs);
			}

			template<typename T> explicit operator T() const
			{
				typedef typename std::result_of<deduction_helper(T)>::type json_type;
				return static_cast<T>(
					InternalValueFactory::template cast<json_type>(
						static_cast<const typename InternalValueFactory::value_type*>(m_internal_value)));
			}

			template<typename T> explicit operator const T&() const
			{
				typedef typename std::result_of<deduction_helper(T)>::type json_type;
				return static_cast<const T&>(
					InternalValueFactory::template cast<const json_type&>(
						static_cast<const typename InternalValueFactory::value_type*>(m_internal_value)));
			}

			template<typename T,
			class = typename std::enable_if<std::is_same<T, typename std::result_of<deduction_helper(T)>::type>::value>::type>
			explicit operator T&()
			{
				return InternalValueFactory::template cast<T&>(m_internal_value);
			}

			friend std::istream& operator>>(std::istream& is, value_shell& v)
			{
				delete v.m_internal_value;
				v.m_internal_value = InternalValueFactory::parse(is);
				return is;
			}

			friend std::wistream& operator>>(std::wistream& is, value_shell& v)
			{
				delete v.m_internal_value;
				v.m_internal_value = InternalValueFactory::parse(is);
				return is;
			}

			friend std::ostream& operator<<(std::ostream& os, const value_shell& v)
			{
				InternalValueFactory::print(os, v.m_internal_value);
				return os;
			}

			friend std::wostream& operator<<(std::wostream& os, const value_shell& v)
			{
				InternalValueFactory::print(os, v.m_internal_value);
				return os;
			}

			~value_shell() noexcept
			{
				delete m_internal_value;
			}

		protected:
			template<typename T> static void reset(value_shell& v)
			{
				delete v.m_internal_value;
				v.m_internal_value = InternalValueFactory::template create<T>();
			}

		private:
			typename InternalValueFactory::value_type* m_internal_value;
		};
	}
}

#endif // PELI_DETAIL_VALUE_SHELL_H
