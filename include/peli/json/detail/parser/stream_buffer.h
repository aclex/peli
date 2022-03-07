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

#ifndef PELI_DETAIL_PARSER_STREAM_BUFFER_H
#define PELI_DETAIL_PARSER_STREAM_BUFFER_H

#include <istream>

#include <peli/except.h>

namespace peli::json::detail::parser
{
	/** \brief Input adapter for `std::basic_streambuf<>` */
	template<typename Ch> class stream_buffer
	{
	public:
		using char_type = Ch;

		stream_buffer(std::basic_istream<Ch>& is) :
			m_rdbuf(*is.rdbuf()),
			m_line_no()
		{
			if (!typename std::basic_istream<Ch>::sentry(is, true))
			{
				throw parse_error("Can't prepare input stream.");
			}
		}

		typename std::basic_streambuf<Ch>::off_type pos()
		{
			return m_rdbuf.pubseekoff(0, std::ios_base::cur, std::ios_base::in);
		}

		typename std::basic_streambuf<Ch>::pos_type set_pos(const typename std::basic_streambuf<Ch>::pos_type pos)
		{
			return m_rdbuf.pubseekpos(pos, std::ios_base::in);
		}

		std::streamsize getn(Ch* const s, const std::streamsize count)
		{
			return m_rdbuf.sgetn(s, count);
		}

		typename std::basic_streambuf<Ch>::int_type getc()
		{
			return m_rdbuf.sgetc();
		}

		typename std::basic_streambuf<Ch>::int_type nextc()
		{
			return m_rdbuf.snextc();
		}

		typename std::basic_streambuf<Ch>::int_type bumpc()
		{
			return m_rdbuf.sbumpc();
		}

		std::size_t line_no() const noexcept
		{
			return m_line_no;
		}

		void new_line() noexcept
		{
			++m_line_no;
		}

		static typename std::basic_streambuf<Ch>::int_type eof()
		{
			return std::basic_streambuf<Ch>::traits_type::eof();
		}

	private:
		std::basic_streambuf<Ch>& m_rdbuf;
		std::size_t m_line_no;
	};
}

#endif // PELI_DETAIL_PARSER_STREAM_BUFFER_H
