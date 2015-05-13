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

#include <string>
#include <type_traits>

#include <peli/detail/variant_value/inline.h>

#include <peli/json/object.h>
#include <peli/json/array.h>
#include <peli/json/number.h>

namespace peli
{
	namespace json
	{
		class value;
		template<typename T> value make_value();

		class value
		{
			struct deduction_helper
			{
				array operator()(array);
				number operator()(number);
				bool operator()(bool);

				template<typename Ch> basic_object<Ch> operator()(basic_object<Ch>);
				template<typename Ch> std::basic_string<Ch> operator()(std::basic_string<Ch>);

				template<typename U,
				class = typename std::enable_if<std::is_convertible<array, U>::value>::type>
				array operator()(U);

				template<typename U,
				class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
				number operator()(U);

				template<typename U, typename Ch,
				class = typename std::enable_if<std::is_convertible<basic_object<Ch>, U>::value>::type>
				basic_object<Ch> operator()(U);

				template<typename U, typename Ch,
				class = typename std::enable_if<std::is_convertible<std::basic_string<Ch>, U>::value>::type>
				std::basic_string<Ch> operator()(U);
			};

			typedef detail::variant_value::inline_variant::variant
			<
				bool,
				json::number,
				std::string, std::wstring,
				json::array,
				json::object, json::wobject
			>
			variant_type;

			typedef deduction_helper deduction_helper_type;

		public:
			value() = default;

			template<typename Ch> explicit value(const peli::json::basic_object<Ch>& obj) : m_variant(obj) { }
			template<typename Ch> explicit value(peli::json::basic_object<Ch>&& obj) noexcept : m_variant(std::move(obj)) { }
			explicit value(const peli::json::array& arr) : m_variant(arr) { }
			explicit value(peli::json::array&& arr) noexcept : m_variant(std::move(arr)) { }
			template<typename Ch> explicit value(const std::basic_string<Ch>& str) : m_variant(str) { }
			template<typename Ch> explicit value(std::basic_string<Ch>&& str) noexcept : m_variant(std::move(str)) { }
			template<typename Ch> explicit value(const Ch* str) : value(std::basic_string<Ch>(str)) { }
			explicit value(bool b) : m_variant(b) { }
			explicit value(json::number i) : m_variant(i) { }

			template<typename U,
			class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
			explicit value(U i) : value(static_cast<json::number>(i)) { }

			bool null() const noexcept
			{
				return !m_variant.valid();
			}

			bool operator==(const value& rhs) const noexcept
			{
				return m_variant == rhs.m_variant;
			}

			bool operator!=(const value& rhs) const noexcept
			{
				return m_variant != rhs.m_variant;
			}

			template<typename T,
			typename DeductedType = typename std::result_of<deduction_helper_type(T)>::type>
			explicit operator T() const
			{
				return static_cast<T>(m_variant.cast<DeductedType>());
			}

			template<typename T,
			typename DeductedType = typename std::result_of<deduction_helper_type(T)>::type>
			explicit operator const T&() const
			{
				return static_cast<const T&>(m_variant.cast<const DeductedType&>());
			}

			template<typename T,
			typename DeductedType = typename std::result_of<deduction_helper_type(T)>::type,
			class = typename std::enable_if<std::is_same<T, DeductedType>::value>::type>
			explicit operator T&()
			{
				return m_variant.cast<T&>();
			}

			friend std::ostream& operator<<(std::ostream& os, const value& v);
			friend std::wostream& operator<<(std::wostream& os, const value& v);

			template<typename T> friend inline value make_value()
			{
				return value(T());
			}

		private:
			variant_type m_variant;
		};

		std::istream& operator>>(std::istream& is, value& v);
		std::wistream& operator>>(std::wistream& is, value& v);

		std::ostream& operator<<(std::ostream& os, const value& v);
		std::wostream& operator<<(std::wostream& os, const value& v);
	}
}

#endif // PELI_JSON_VALUE_H
