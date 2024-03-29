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

#ifndef PELI_DETAIL_PARSER_UTF_H
#define PELI_DETAIL_PARSER_UTF_H

#include <string>
#include <cstdint>

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				/** \brief UTF-related constants and functions. */
				namespace utf
				{
					/** \brief Several internal details */
					namespace detail
					{
						// Unicode constants
						// Leading (high) surrogates: 0xd800 - 0xdbff
						constexpr const uint16_t LEAD_SURROGATE_MIN  = 0xd800u;
						constexpr const uint16_t LEAD_SURROGATE_MAX  = 0xdbffu;
						// Trailing (low) surrogates: 0xdc00 - 0xdfff
						constexpr const uint16_t TRAIL_SURROGATE_MIN = 0xdc00u;
						constexpr const uint16_t TRAIL_SURROGATE_MAX = 0xdfffu;
						constexpr const uint16_t LEAD_OFFSET         = LEAD_SURROGATE_MIN - (0x10000 >> 10);
						constexpr const uint32_t SURROGATE_OFFSET    = 0x10000u - (LEAD_SURROGATE_MIN << 10) - TRAIL_SURROGATE_MIN;

						// Maximum valid value for a Unicode code point
						constexpr const uint32_t CODE_POINT_MAX      = 0x0010ffffu;
					}

					constexpr bool is_lead_surrogate(std::uint_fast16_t cp) noexcept
					{
						return (cp >= detail::LEAD_SURROGATE_MIN && cp <= detail::LEAD_SURROGATE_MAX);
					}

					constexpr bool is_trail_surrogate(std::uint_fast16_t cp) noexcept
					{
						return (cp >= detail::TRAIL_SURROGATE_MIN && cp <= detail::TRAIL_SURROGATE_MAX);
					}

					template <typename u16>
					constexpr bool is_surrogate(u16 cp) noexcept
					{
						return (cp >= detail::LEAD_SURROGATE_MIN && cp <= detail::TRAIL_SURROGATE_MAX);
					}

					template <typename u32>
					constexpr bool is_code_point_valid(u32 cp) noexcept
					{
						return (cp <= detail::CODE_POINT_MAX && !is_surrogate(cp));
					}

					namespace detail
					{
						/** \brief Converts one wider character to [`std::string`](https://en.cppreference.com/w/cpp/string/basic_string). */
						template<typename UtfCp> std::basic_string<char> wide_to_char(UtfCp cp)
						{
							std::basic_string<char> result;

							if (!is_code_point_valid(cp))
								throw std::invalid_argument("Invalid codepoint found.");

							if (cp < 0x80)               // one octet
							{
								result += cp;
							}
							else if (cp < 0x800)         // two octets
							{
								result += (cp >> 6)            | 0xc0;
								result += (cp & 0x3f)          | 0x80;
							}
							else if (cp < 0x10000)       // three octets
							{
								result += (cp >> 12)           | 0xe0;
								result += ((cp >> 6) & 0x3f)   | 0x80;
								result += (cp & 0x3f)          | 0x80;
							}
							else                                // four octets
							{
								result += (cp >> 18)           | 0xf0;
								result += ((cp >> 12) & 0x3f)  | 0x80;
								result += ((cp >> 6) & 0x3f)   | 0x80;
								result += (cp & 0x3f)          | 0x80;
							}

							return result;
						}

						/** \brief Converts surrogate pair to one full-length character. */
						inline std::uint_fast32_t surrogate_to_wide(std::uint16_t leading_surrogate, std::uint16_t trailing_surrogate)
						{
							// Take care of surrogate pairs first
							if (!is_lead_surrogate(leading_surrogate) || !is_trail_surrogate(trailing_surrogate))
								throw std::invalid_argument("Invalid surrogate pair found.");

							return (leading_surrogate << 10) + trailing_surrogate + SURROGATE_OFFSET;
						}

						/** \brief Converts `wchar_t` of implementation-defined length to [`std::basic_string`](https://en.cppreference.com/w/cpp/string/basic_string) of the given character type. */
						template<typename Ch, std::enable_if_t<sizeof(Ch) == 2, bool> = false>
						inline std::basic_string<Ch> wide_convert(std::uint_fast16_t leading_surrogate, std::uint_fast16_t trailing_surrogate)
						{
							return std::basic_string<Ch> { static_cast<Ch>(leading_surrogate), static_cast<Ch>(trailing_surrogate) };
						}

						template<typename Ch, std::enable_if_t<sizeof(Ch) == 4, bool> = false>
						inline std::basic_string<Ch> wide_convert(std::uint_fast16_t leading_surrogate, std::uint_fast16_t trailing_surrogate)
						{
							return std::basic_string<Ch> { static_cast<Ch>(surrogate_to_wide(leading_surrogate, trailing_surrogate)) };
						}
					}

					/** \brief Converts one 16-bit character to [`std::basic_string`](https://en.cppreference.com/w/cpp/string/basic_string) of the specified character type. */
					template<typename Ch> inline std::basic_string<Ch> convert(std::uint_fast16_t cp)
					{
						return std::basic_string<Ch> { static_cast<Ch>(cp) };
					}

					template<> inline std::basic_string<char> convert(std::uint_fast16_t cp)
					{
						return detail::wide_to_char(cp);
					}

					/** \brief Converts a split surrogate pair to [`std::basic_string`](https://en.cppreference.com/w/cpp/string/basic_string) of the specified character type. */
					template<typename Ch> inline std::basic_string<Ch> convert(std::uint_fast16_t leading_surrogate, std::uint_fast16_t trailing_surrogate)
					{
						return detail::wide_convert<Ch>(leading_surrogate, trailing_surrogate);
					}

					template<> inline std::basic_string<char> convert(uint_fast16_t leading_surrogate, uint_fast16_t trailing_surrogate)
					{
						return detail::wide_to_char(detail::surrogate_to_wide(leading_surrogate, trailing_surrogate));
					}
				}
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_UTF_H
