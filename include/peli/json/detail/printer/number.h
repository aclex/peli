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

#ifndef PELI_DETAIL_PRINTER_NUMBER_H
#define PELI_DETAIL_PRINTER_NUMBER_H

#include <limits>
#include <stdexcept>
#include <cmath>

#include "peli/json/number.h"

#include "peli/json/detail/printer/stream_routines.h"

#ifdef USE_FLOAXIE
#include <floaxie/ftoa.h>
#endif

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief `head` specialization for [JSON](https://json.org) number.
				 * \see `head`
				 */
				template<> struct head<json::number>
				{
				public:
					template<class Visitor> static void print(Visitor& v, const json::number n)
					{
						if (std::isnan(n))
							throw std::invalid_argument("NaN can't be represented in JSON.");

						if (std::isinf(n))
							throw std::invalid_argument("Infinity can't be represented in JSON.");

						put_structure_space(v);

						using char_type = typename Visitor::char_type;

#ifdef USE_FLOAXIE
						char_type buf[floaxie::max_buffer_size<double>()];
						const auto written_size { floaxie::ftoa(static_cast<double>(n), buf) };

						v.putn(buf, written_size);
#else
						const auto& result { to_string<char_type>(n) };
						v.putn(result.data(), result.size());
#endif
					}
				private:
#ifndef USE_FLOAXIE
					template<typename Ch> static std::basic_string<Ch> to_string(const json::number n);
#endif
				};

#ifndef USE_FLOAXIE
				template<> std::basic_string<char> head<json::number>::to_string(const json::number n)
				{
					return std::to_string(n);
				}

				template<> std::basic_string<wchar_t> head<json::number>::to_string(const json::number n)
				{
					return std::to_wstring(n);
				}
#endif
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_NUMBER_H
