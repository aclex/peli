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

#ifndef PELI_DETAIL_PARSER_UTF_H
#define PELI_DETAIL_PARSER_UTF_H

#include <string>
#include <cstdint>

namespace peli
{
	namespace detail
	{
		namespace parser
		{
			namespace utf
			{
				bool is_lead_surrogate(std::uint_fast16_t cp);
				bool is_trail_surrogate(std::uint_fast16_t cp);

				template<typename Ch> std::basic_string<Ch> convert(std::uint_fast16_t cp)
				{
					return std::basic_string<Ch> { static_cast<Ch>(cp) };
				}

				template<typename Ch> std::basic_string<Ch> convert(std::uint_fast16_t leading_surrogate, std::uint_fast16_t trailing_surrogate);

				template<> std::basic_string<char> convert(std::uint_fast16_t cp);
				template<> std::basic_string<char> convert(std::uint_fast16_t leading_surrogate, std::uint_fast16_t trailing_surrogate);

				template<> std::basic_string<wchar_t> convert(std::uint_fast16_t leading_surrogate, std::uint_fast16_t trailing_surrogate);

				template<> std::basic_string<char16_t> convert(std::uint_fast16_t leading_surrogate, std::uint_fast16_t trailing_surrogate);

				template<> std::basic_string<char32_t> convert(std::uint_fast16_t leading_surrogate, std::uint_fast16_t trailing_surrogate);
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_UTF_H
