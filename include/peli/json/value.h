/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014-2022  Alexey Chernov <4ernov@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
		 * \tparam Ch character type.
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

		/** \brief Prints the content of the specified value to string.
		 *
		 * \tparam Ch character type.
		 * \param v value to print.
		 * \param pretty flag to enable pretty printing.
		 *
		 * \return string containing textual content of the specified value.
		 *
		 * \sa peli::json::pretty()
		 */
		template<typename Ch> std::basic_string<Ch> to_string(const basic_value<Ch>& v, const bool pretty = false);
	}
}

#include <peli/json/value.tcc>

#endif // PELI_JSON_VALUE_H
