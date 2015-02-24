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

#include "detail/parser/parser.h"

#include "peli/json/number.h"

#include "detail/parser/stream_routines.h"

namespace peli
{
	namespace detail
	{
		namespace parser
		{
			template<> class parser<peli::json::number>
			{
			public:
				template<typename Ch, typename Alloc>
				static peli::json::number parse(std::basic_istream<Ch, Alloc>& is)
				{
					const auto& buf = get_value(is);

					auto ret = convert(buf);

					if (errno)
						throw std::invalid_argument("");

					return ret;
				}

			private:
				static peli::json::number convert(const std::string& str)
				{
					return std::strtold(str.c_str(), nullptr);
				}

				static peli::json::number convert(const std::wstring& str)
				{
					return std::wcstold(str.c_str(), nullptr);
				}
			};
		}
	}
}

#endif // PELI_DETAIL_PARSER_NUMBER_H
