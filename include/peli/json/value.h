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

#include <peli/value_basics.h>

#include <peli/json/object.h>
#include <peli/json/array.h>
#include <peli/json/number.h>

namespace peli
{
	/** \brief Types and functions for [JSON](http://json.org/) interaction. */
	namespace json
	{
		/** [JSON](http://json.org/) value uniform representation.
		 *
		 * In fact it's just a tiny shell around variant type used, and
		 * this is to allow recursive inclusion of variants.
		 *
		 * \tparam Ch character type used.
		 */
		template<typename Ch> class basic_value : public peli::variant_type
		<
			bool,
			json::number,
			std::basic_string<Ch>,
			json::basic_array<Ch>,
			json::basic_object<Ch>
		>
		{
		public:
			/** \brief Underlying variant type. */
			using variant_type = peli::variant_type
			<
				bool,
				json::number,
				std::basic_string<Ch>,
				json::basic_array<Ch>,
				json::basic_object<Ch>
			>;

			using variant_type::variant_type;

			/** \brief Checks if the value is null (as per [JSON](http://json.org/) specification). */
			bool null() const noexcept
			{
				return peli::is_empty(*this);
			}

			/** \brief Parses null-terminated string.
			 *
			 * \param str null-terminated string to parse.
			 */
			static basic_value parse(const Ch* const str);

			/** \brief Parses std::basic_string<>.
			 *
			 * \param str string to parse.
			 */
			static basic_value parse(const std::basic_string<Ch>& str);
		};

		/** \brief `basic_value` specialization for `char`. */
		typedef basic_value<char> value;
		/** \brief `basic_value` specialization for `wchar_t`. */
		typedef basic_value<wchar_t> wvalue;

		/** \brief Small factory method to create uninitialized value of the given type.
		 *
		 * \tparam T type the value to construct of.
		 * \tparam ValueType value type to create (e.g. some character specialization
		 * of `basic_value<>`).
		 */
		template<typename T, class ValueType = value> inline ValueType make_value()
		{
			return ValueType(T());
		}
	}
}

#include <peli/json/value.tcc>

#endif // PELI_JSON_VALUE_H
