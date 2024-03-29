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

#include <string>

#ifdef CXX_STD_17
#include <string_view>
#endif

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
		return detail::find(&v, ptr);
	}

	/** \brief Finds a sub-element matching the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) within the specified const value.
	 *
	 * \tparam Ch character type.
	 * \param v constant reference value to evaluate the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901).
	 * \param ptr [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) string (unlike mentioned in RFC and as any normal C/C++ string, it can't contain null characters).
	 *
	 * \return constant pointer to the found value, if there's one, null pointer otherwise.
	 */
	template<typename Ch> const basic_value<Ch>* find(const basic_value<Ch>& v, const std::basic_string<Ch>& ptr)
	{
		return detail::find(&v, ptr);
	}

#ifdef CXX_STD_17
	/** \brief Finds a sub-element matching the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) within the specified value.
	 *
	 * \tparam Ch character type.
	 * \param v reference value to evaluate the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901).
	 * \param ptr [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) string (unlike mentioned in RFC and as any normal C/C++ string, it can't contain null characters).
	 *
	 * \return pointer to the found value, if there's one, null pointer otherwise.
	 */
	template<typename Ch> basic_value<Ch>* find(basic_value<Ch>& v, const std::basic_string_view<Ch> ptr)
	{
		return detail::find(&v, ptr);
	}

	/** \brief Finds a sub-element matching the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) within the specified const value.
	 *
	 * \tparam Ch character type.
	 * \param v constant reference value to evaluate the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901).
	 * \param ptr [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) string (unlike mentioned in RFC and as any normal C/C++ string, it can't contain null characters).
	 *
	 * \return constant pointer to the found value, if there's one, null pointer otherwise.
	 */
	template<typename Ch> const basic_value<Ch>* find(const basic_value<Ch>& v, const std::basic_string_view<Ch> ptr)
	{
		return detail::find(&v, ptr);
	}

#endif

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

	/** \brief Finds a sub-element matching the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) and the specified type within the constant value.
	 *
	 * \tparam T expected type after conversion.
	 * \tparam Ch character type.
	 * \param v constant reference value to evaluate the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901).
	 * \param ptr [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) string (unlike mentioned in RFC and as any normal C/C++ string, it can't contain null characters).
	 *
	 * \return constant pointer to the found value of the specified type, if there's one, null pointer otherwise.
	 */
	template<typename T, typename Ch> const T* find_of(const basic_value<Ch>& v, const std::basic_string<Ch>& ptr)
	{
		return std::get_if<T>(find(v, ptr));
	}

#ifdef CXX_STD_17
	/** \brief Finds a sub-element matching the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) and the specified type within the value.
	 *
	 * \tparam T expected type after conversion.
	 * \tparam Ch character type.
	 * \param v reference value to evaluate the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901).
	 * \param ptr [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) string_view (unlike mentioned in RFC and as any normal C/C++ string, it can't contain null characters).
	 *
	 * \return pointer to the found value of the specified type, if there's one, null pointer otherwise.
	 */
	template<typename T, typename Ch> T* find_of(basic_value<Ch>& v, const std::basic_string_view<Ch> ptr)
	{
		return std::get_if<T>(find(v, ptr));
	}

	/** \brief Finds a sub-element matching the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) and the specified type within the constant value.
	 *
	 * \tparam T expected type after conversion.
	 * \tparam Ch character type.
	 * \param v constant reference value to evaluate the [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901).
	 * \param ptr [JSON Pointer](https://www.rfc-editor.org/rfc/rfc6901) string_view (unlike mentioned in RFC and as any normal C/C++ string, it can't contain null characters).
	 *
	 * \return constant pointer to the found value of the specified type, if there's one, null pointer otherwise.
	 */
	template<typename T, typename Ch> const T* find_of(const basic_value<Ch>& v, const std::basic_string_view<Ch> ptr)
	{
		return std::get_if<T>(find(v, ptr));
	}

#endif

#endif
}

#endif // PELI_JSON_FIND_H
