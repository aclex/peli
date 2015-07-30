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

						buf.fill(0);

						extract(rdbuf, buf);

						auto ret = convert(buf);

						if (errno == ERANGE)
							throw std::invalid_argument(std::strerror(errno));

						return ret;
					}

				private:
					template<typename Ch>
					static void extract(std::basic_streambuf<Ch>* rdbuf, buffer_type<Ch>& buf)
					{
						typename std::basic_streambuf<Ch>::int_type c = rdbuf->sgetc();

						auto it = std::begin(buf), stop = std::end(buf) - 1;
						while(!is_value_delimiter(c) && it < stop)
						{
							(*it++) = c;
							c = rdbuf->snextc();
						}
					}

					static peli::json::number convert(const buffer_type<char>& buf)
					{
						return std::strtold(buf.data(), nullptr);
					}

					static peli::json::number convert(const buffer_type<wchar_t>& buf)
					{
						return std::wcstold(buf.data(), nullptr);
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_NUMBER_H
