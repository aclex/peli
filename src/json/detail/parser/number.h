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
#include <iostream>
#include <array>

#include "peli/json/number.h"

#include "json/detail/parser/parser.h"

#include "json/detail/parser/stream_routines.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				template<> class parser<peli::json::number>
				{
					static constexpr const std::size_t s_buf_size = std::numeric_limits<json::number>::max_digits10 + 1;
					template<typename Ch> using buffer_type = std::array<Ch, s_buf_size>;

				public:
					template<typename Ch>
					static peli::json::number parse(std::basic_streambuf<Ch>* rdbuf)
					{
						static buffer_type<Ch> buf;

						typename std::basic_streambuf<Ch>::pos_type curr_pos = rdbuf->pubseekoff(0, std::ios_base::cur, std::ios_base::in);
						auto chars_read = rdbuf->sgetn(buf.data(), s_buf_size - 1);
						buf[chars_read] = 0;

						Ch* rest;

						json::number ret = convert(buf.data(), &rest);

						if (errno == ERANGE)
							throw std::invalid_argument(std::strerror(errno));

						auto chars_parsed = rest - buf.data();

						rdbuf->pubseekpos(curr_pos + chars_parsed, std::ios_base::in);

						return ret;
					}

				private:
					static peli::json::number convert(const char* buf, char** rest)
					{
						return std::strtold(buf, rest);
					}

					static peli::json::number convert(const wchar_t* buf, wchar_t** rest)
					{
						return std::wcstold(buf, rest);
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_NUMBER_H
