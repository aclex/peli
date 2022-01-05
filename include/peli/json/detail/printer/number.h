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

#ifndef PELI_DETAIL_PRINTER_NUMBER_H
#define PELI_DETAIL_PRINTER_NUMBER_H

#include <limits>
#include <stdexcept>

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
