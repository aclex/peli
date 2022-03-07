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

#ifndef PELI_JSON_DETAIL_PRINTER_VISITOR_H
#define PELI_JSON_DETAIL_PRINTER_VISITOR_H

#include <ostream>

#include "peli/json/detail/printer/head.h"
#include "peli/json/detail/printer/string.h"
#include "peli/json/detail/printer/boolean.h"
#include "peli/json/detail/printer/null.h"
#include "peli/json/detail/printer/number.h"
#include "peli/json/detail/printer/array.h"
#include "peli/json/detail/printer/object.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief Printing visitor.
				 *
				 * Holds the necessary properties while printing values,
				 * i.e. provides printing context.
				 *
				 */
				template<class Derived> class visitor
				{
				public:
					visitor(const bool pretty) :
						m_tab_level(),
						m_structure_period(),
						m_pretty(pretty)
					{

					}

					bool pretty() const noexcept
					{
						return m_pretty;
					}

					std::size_t tab_level() const noexcept
					{
						return m_tab_level;
					}
					
					void increase_tab_level() noexcept
					{
						++m_tab_level;
					}

					void decrease_tab_level() noexcept
					{
						--m_tab_level;
					}

					bool need_structure_period() const noexcept
					{
						return m_structure_period;
					}

					void set_need_structure_period(const bool v) noexcept
					{
						m_structure_period = v;
					}

					/** \brief Prints [JSON](https://json.org) representation of the value. */
					template<typename Arg> void operator()(Arg a)
					{
						printer::head<Arg>::print(*static_cast<Derived*>(this), a);
					}

					/** \brief Prints [JSON](https://json.org) representation of null entity. */
					void operator()()
					{
						printer::head<void>::print(*static_cast<Derived*>(this));
					}

				private:
					std::size_t m_tab_level;
					bool m_structure_period;
					const bool m_pretty;
				};

				/** \brief Printing visitor for `std::basic_streambuf<>`.
				 *
				 * Memorizes a reference to stream and prints values
				 * while visiting them.
				 *
				 */
				template<typename Ch> class stream_visitor : public visitor<stream_visitor<Ch>>
				{
				public:
					using char_type = Ch;

					/** \brief Binds the visitor to stream. */
					stream_visitor(std::basic_ostream<Ch>& os) :
						visitor<stream_visitor>(flag::get(os.iword(flag_storage_index()), flag::pretty)),
						m_os(os)
					{

					}

					void putc(const Ch c)
					{
						m_os.rdbuf()->sputc(c);
					}

					std::streamsize putn(const Ch* s, const std::size_t size)
					{
						return m_os.rdbuf()->sputn(s, size);
					}

					using visitor<stream_visitor<Ch>>::operator();

				private:
					std::basic_ostream<Ch>& m_os;
				};

				/** \brief Printing visitor for `std::basic_string<>`.
				 *
				 * Memorizes a reference to string and prints values
				 * while visiting them.
				 *
				 */
				template<typename Ch> class string_visitor : public visitor<string_visitor<Ch>>
				{
				public:
					using char_type = Ch;

					/** \brief Binds the visitor to stream. */
					string_visitor(std::basic_string<Ch>& str, const bool pretty) :
						visitor<string_visitor>(pretty),
						m_str(str)
					{

					}

					void putc(const Ch c)
					{
						m_str += c;
					}

					void putn(const Ch* s, const std::size_t size)
					{
						std::copy(s, s + size, std::back_inserter(m_str));
					}

					using visitor<string_visitor<Ch>>::operator();

				private:
					std::basic_string<Ch>& m_str;
				};
			}
		}
	}
}

#endif // PELI_JSON_DETAIL_PRINTER_VISITOR_H
