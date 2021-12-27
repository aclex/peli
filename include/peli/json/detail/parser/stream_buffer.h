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
