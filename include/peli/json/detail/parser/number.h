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

#ifndef PELI_DETAIL_PARSER_NUMBER_H
#define PELI_DETAIL_PARSER_NUMBER_H

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <limits>
#include <array>

#ifdef USE_FLOAXIE
#include "floaxie/atof.h"
#endif

#include "peli/except.h"

#include "peli/json/number.h"

#include "peli/json/detail/parser/parser.h"
#include "peli/json/detail/parser/stream_routines.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				/** \brief `parser` specialization for [JSON](https://json.org) number.
				 * \see `parser`
				 */
				template<> class parser<peli::json::number>
				{
					static constexpr const std::size_t s_buf_size = 128;
					template<typename Ch> using buffer_type = std::array<Ch, s_buf_size>;

					template<class InputBuffer, std::size_t N, std::size_t Offset = 0>
					static std::pair<double, std::size_t>
					peek_and_try_convert(InputBuffer& buf, std::array<typename InputBuffer::char_type, N>& num_buf)
					{
						using char_type = typename InputBuffer::char_type;

						double result;

						const auto chars_read { buf.getn(num_buf.data() + Offset, N - 1 - Offset) };
						num_buf[Offset + chars_read] = 0;

						char_type* rest;

#ifdef USE_FLOAXIE
						const auto& conv_result { floaxie::atof<double>(num_buf.data(), &rest) };

						if (conv_result.status != floaxie::conversion_status::success)
							throw parse_error("Number representation parsing failed.");

						result = conv_result.value;
#else
						result = convert<char_type>(num_buf.data(), &rest);
#endif
						const auto chars_parsed { rest - num_buf.data() };

						if (static_cast<std::size_t>(chars_parsed) >= s_buf_size - 1)
							throw parse_error("Number representation is too long to be parsed.");

						return { result, chars_parsed };
					}

#ifndef USE_FLOAXIE
					template<typename Ch> static double convert(const Ch* const s, Ch** rest);
#endif

				public:
					template<class InputBuffer>
					static peli::json::number parse(InputBuffer& buf)
					{
						buffer_type<typename InputBuffer::char_type> num_buf;

						const auto curr_pos { buf.pos() };

						const auto& peek_result { peek_and_try_convert(buf, num_buf) };
						const auto conv_result { peek_result.first };
						const auto chars_parsed { peek_result.second };

						buf.set_pos(curr_pos + chars_parsed);

						return conv_result;
					}
				};

#ifndef USE_FLOAXIE
				template<> double parser<peli::json::number>::convert(const char* const s, char** rest)
				{
					return std::strtod(s, rest);
				}

				template<> double parser<peli::json::number>::convert(const wchar_t* const s, wchar_t** rest)
				{
					return std::wcstod(s, rest);
				}
#endif
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_NUMBER_H
