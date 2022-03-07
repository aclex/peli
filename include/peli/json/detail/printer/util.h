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

#ifndef PELI_DETAIL_PRINTER_UTIL_H
#define PELI_DETAIL_PRINTER_UTIL_H

#include <ios>

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief Returns index for flag storage in stream register. */
				inline int flag_storage_index()
				{
					static int i { std::ios_base::xalloc() };
					return i;
				}

				/** \brief Flags used in printing. */
				namespace flag
				{
					/** \brief Pretty printing switch. */
					const long pretty = 0x01;
					/** \brief Structure newline switch */
					const long structure_newline = 0x02;

					/** \brief Gets the flag value.
					 *
					 * \param flag_word stream register word to read.
					 * \param flag index of flag to read.
					 *
					 * \return Current flag status.
					 *
					 */
					constexpr bool get(const long& flag_word, long flag) { return flag_word & flag; }

					/** \brief Sets the flag value.
					 *
					 * \param flag_word stream register word to read.
					 * \param flag index of flag to read.
					 *
					 */
					inline void set(long& flag_word, long flag) { flag_word |= flag; }

					/** \brief Resets the flag value.
					 *
					 * \param flag_word stream register word to read.
					 * \param flag index of flag to read.
					 *
					 */
					inline void unset(long& flag_word, long flag) { flag_word &= ~flag; }
				}
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_UTIL_H
