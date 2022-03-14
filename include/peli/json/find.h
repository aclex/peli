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

#ifndef PELI_JSON_FIND_H
#define PELI_JSON_FIND_H

#include <array>
#include <string>
#include <cstddef>

#ifdef USE_FLOAXIE
#include <floaxie/atof.h>
#else
#include <peli/json/detail/parser/number.h>
#endif

#include <peli/json/array.h>
#include <peli/json/object.h>
#include <peli/json/value.h>

#include <peli/json/detail/json_pointer.h>

namespace peli::json
{
	/** \brief Finds a sub-element matching the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) within the specified value.
	 *
	 * \tparam Ch character type.
	 * \param v reference value to evaluate the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901).
	 * \param ptr [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) string (unlike mentioned in RFC and as any normal C/C++ string, it can't contain null characters).
	 *
	 * \return pointer to the found value, if there's one, null pointer otherwise.
	 */
	template<typename Ch> basic_value<Ch>* find(basic_value<Ch>& v, const std::basic_string<Ch>& ptr)
	{
		if (ptr.empty())
			return &v;

		typename std::basic_string<Ch>::size_type ref_begin { 1 };

		static constexpr std::array<Ch, 3> slash_coded { '~', '1', 0 };
		static constexpr std::array<Ch, 2> slash { '/', 0 };
		static constexpr std::array<Ch, 3> tilda_coded { '~', '0', 0 };
		static constexpr std::array<Ch, 2> tilda { '~', 0 };

		basic_value<Ch>* curr{&v};

		for (auto ref_end = ptr.find('/', ref_begin); ref_begin <= ptr.length(); ref_end = ptr.find('/', ref_begin))
		{
			if (auto* const p { std::get_if<array>(curr) })
			{
				std::size_t index;

				Ch* str_end { };
#ifdef USE_FLOAXIE
				const auto& conv_result { floaxie::atof<double>(&ptr[ref_begin], &str_end) };

				if (conv_result.status != floaxie::conversion_status::success)
					return nullptr;

				index = static_cast<std::size_t>(conv_result.value);
#else
				index = peli::json::detail::parser::convert(&ptr[ref_begin], &str_end);
#endif

				if (index >= p->size())
					return nullptr;

				curr = &(*p)[index];
			}
			else if (auto* const p { std::get_if<basic_object<Ch>>(curr) })
			{
				std::basic_string<Ch> ref { ptr.substr(ref_begin, ref_end - ref_begin) };
				detail::replace_escape_seq(ref, slash_coded.data(), slash.data());
				detail::replace_escape_seq(ref, tilda_coded.data(), tilda.data());

				const auto it { p->find(ref) };

				if (it == std::end(*p))
					return nullptr;

				curr = &it->second;
			}
			else
			{
				return nullptr;
			}

			ref_begin = ref_end != std::basic_string<Ch>::npos ? ref_end + 1 : ref_end;
		}

		return curr;
	}

#ifndef INTERNAL_VARIANT
	/** \brief Finds a sub-element matching the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) and the specified type within the value.
	 *
	 * \tparam T expected type after conversion.
	 * \tparam Ch character type.
	 * \param v reference value to evaluate the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901).
	 * \param ptr [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) string (unlike mentioned in RFC and as any normal C/C++ string, it can't contain null characters).
	 *
	 * \return pointer to the found value of the specified type, if there's one, null pointer otherwise.
	 */
	template<typename T, typename Ch> T* find_of(basic_value<Ch>& v, const std::basic_string<Ch>& ptr)
	{
		return std::get_if<T>(find(v, ptr));
	}
#endif
}

#endif // PELI_JSON_FIND_H
