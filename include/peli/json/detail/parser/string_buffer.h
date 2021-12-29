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

#ifndef PELI_DETAIL_PARSER_STRING_BUFFER_H
#define PELI_DETAIL_PARSER_STRING_BUFFER_H

#include <istream>

#include <peli/except.h>

namespace peli::json::detail::parser
{
	/** \brief Input adapter for arbitrary character sequence */
	template<typename Ch> class char_buffer
	{
	public:
		using char_type = Ch;

		char_buffer(const char_type* const p) noexcept :
			m_ptr(p),
			m_counter(),
			m_line_no()
		{

		}

		std::size_t pos() const noexcept
		{
			return m_counter;
		}

		void set_pos(const std::size_t pos) noexcept
		{
			m_counter = pos;
		}

		std::size_t getn(char_type* const s, const std::streamsize count) const
		{
			return std::distance(std::copy(m_ptr + m_counter, m_ptr + m_counter + count, s), s);
		}

		char_type getc() const noexcept
		{
			return m_ptr[m_counter];
		}

		char_type nextc() noexcept
		{
			const auto n{bumpc()};
			if (n == eof())
				return n;

			return getc();
		}

		char_type bumpc() noexcept
		{
			return m_ptr[m_counter++];
		}

		std::size_t line_no() const noexcept
		{
			return m_line_no;
		}

		void new_line() noexcept
		{
			++m_line_no;
		}

		static char_type eof() noexcept
		{
			return 0;
		}

	private:
		const char_type* const m_ptr;
		std::size_t m_counter;
		std::size_t m_line_no;
	};

	template<typename Ch> class string_buffer : public char_buffer<Ch>
	{
	public:
		explicit string_buffer(const std::basic_string<Ch>& str) :
			char_buffer<Ch>(str.data())
		{

		}
	};
}

#endif // PELI_DETAIL_PARSER_STRING_BUFFER_H
