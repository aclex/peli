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

#include "floaxie/atof.h"

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
					static constexpr const std::size_t s_big_buf_size = 1024 * 1024;
					template<typename Ch> using buffer_type = std::array<Ch, s_buf_size>;
					template<typename Ch> using big_buffer_type = std::array<Ch, s_big_buf_size>;

					template<typename Ch, std::size_t N, std::size_t Offset = 0>
					static std::pair<floaxie::value_and_status<double>, typename std::basic_streambuf<Ch>::off_type>
					peek_and_try_convert(std::basic_streambuf<Ch>* rdbuf, std::array<Ch, N>& buf)
					{
						auto chars_read = rdbuf->sgetn(buf.data() + Offset, N - 1 - Offset);
						buf[Offset + chars_read] = 0;

						Ch* rest;

						const auto& conv_result = floaxie::atof<double>(buf.data(), &rest);
						typename std::basic_streambuf<Ch>::off_type chars_parsed = rest - buf.data();

						return { conv_result, chars_parsed };
					}

				public:
					template<typename Ch>
					static peli::json::number parse(std::basic_streambuf<Ch>* rdbuf)
					{
						static buffer_type<Ch> buf;

						typename std::basic_streambuf<Ch>::pos_type curr_pos = rdbuf->pubseekoff(0, std::ios_base::cur, std::ios_base::in);

						auto peek_result = peek_and_try_convert(rdbuf, buf);
						auto conv_result = std::move(peek_result.first);
						auto chars_parsed = peek_result.second;

						if (conv_result.status != floaxie::conversion_status::success)
						{
							throw parse_error("Number representation parsing failed.");
						}

						if (static_cast<std::size_t>(chars_parsed) >= s_buf_size - 1)
						{
							big_buffer_type<Ch> big_buf;

							std::copy(begin(buf), end(buf) - 1, begin(big_buf));

							const auto& big_peek_result = peek_and_try_convert<Ch, s_big_buf_size, s_buf_size - 1>(rdbuf, big_buf);
							const auto& big_conv_result = big_peek_result.first;
							const auto big_chars_parsed = big_peek_result.second;

							if (big_conv_result.status != floaxie::conversion_status::success)
							{
								throw parse_error("Number representation parsing failed.");
							}

							if (static_cast<std::size_t>(big_chars_parsed) >= s_big_buf_size - 1)
							{
								throw parse_error("Number representation is too long to be parsed.");
							}

							chars_parsed = big_chars_parsed;
							conv_result = big_conv_result;
						}

						rdbuf->pubseekpos(curr_pos + chars_parsed, std::ios_base::in);

						return conv_result.value;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_NUMBER_H
