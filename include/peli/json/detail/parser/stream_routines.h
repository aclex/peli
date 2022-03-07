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

#ifndef PELI_DETAIL_PARSER_STREAM_ROUTINES_H
#define PELI_DETAIL_PARSER_STREAM_ROUTINES_H

#include "peli/json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
					template<typename Ch> inline bool is_whitespace(Ch c)
					{
						switch (c)
						{
						case special_chars::tab:
						case special_chars::lf:
						case special_chars::cr:
						case special_chars::space:
							return true;

						default:
							return false;
						}
					}

					template<typename Ch> inline bool is_newline(Ch c)
					{
						return c == special_chars::lf;
					}

					template<typename Ch> inline bool is_value_delimiter(Ch c)
					{
						if (is_whitespace(c))
							return true;

						switch (c)
						{
						case special_chars::comma:
						case special_chars::right_curly:
						case special_chars::right_square:
							return true;

						default:
							return false;
						}
					}

				template<class InputBuffer> void skip_whitespace(InputBuffer& buf)
				{
					auto c { buf.getc() };
					while(is_whitespace(c))
					{
						if (is_newline(c))
							buf.new_line();

						c = buf.nextc();
					}
				}
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_STREAM_ROUTINES_H
