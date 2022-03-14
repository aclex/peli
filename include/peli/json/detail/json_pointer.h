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

#ifndef PELI_JSON_DETAIL_JSON_POINTER_H
#define PELI_JSON_DETAIL_JSON_POINTER_H

namespace peli::json::detail
{
	template<typename Ch> void replace_escape_seq(std::basic_string<Ch>& s, const Ch* seq, const Ch* c)
	{
		for (auto pos = s.find(seq); pos != std::basic_string<Ch>::npos; pos = s.find(seq, pos))
		{
			s.replace(pos, 2, c);
			pos += 1;
		}
	}
}

#endif // PELI_JSON_DETAIL_JSON_POINTER_H
