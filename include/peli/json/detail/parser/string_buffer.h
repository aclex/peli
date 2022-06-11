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

#ifndef PELI_DETAIL_PARSER_STRING_BUFFER_H
#define PELI_DETAIL_PARSER_STRING_BUFFER_H

#include <algorithm>
#include <iterator>
#include <string>
#include <cstdint>

#include <peli/except.h>

namespace peli::json::detail::parser
{
	/** \brief Input adapter for arbitrary character sequence */
	template<typename Ch> class char_buffer
	{
	public:
		using char_type = Ch;

		char_buffer(const char_type* const p, const std::size_t size = std::basic_string<Ch>::npos) noexcept :
			m_ptr(p),
			m_size(size),
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
			auto to { m_counter + count };

			if (m_size != std::basic_string<Ch>::npos)
				to = std::min(to, m_size);

			return std::distance(s, std::copy(m_ptr + m_counter, m_ptr + to, s));
		}

		char_type getc() const noexcept
		{
			return m_ptr[m_counter];
		}

		char_type nextc() noexcept
		{
			if (m_size != std::basic_string<Ch>::npos && m_counter >= m_size)
				return eof();

			const auto n{bumpc()};
			if (n == eof())
				return n;

			return getc();
		}

		char_type bumpc() noexcept
		{
			if (m_size != std::basic_string<Ch>::npos && m_counter >= m_size)
				return eof();

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
		std::size_t m_size;
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

#ifdef CXX_STD_17
	template<typename Ch> class string_view_buffer : public char_buffer<Ch>
	{
	public:
		explicit string_view_buffer(const std::basic_string_view<Ch> sv) :
			char_buffer<Ch>(sv.data(), sv.size())
		{

		}
	};
#endif
}

#endif // PELI_DETAIL_PARSER_STRING_BUFFER_H
