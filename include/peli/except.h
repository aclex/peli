/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014-2019  Alexey Chernov <4ernov@gmail.com>
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

#ifndef PELI_EXCEPT_H
#define PELI_EXCEPT_H

#include <stdexcept>

namespace peli
{
	class parse_error : public std::exception
	{
	public:
		parse_error() noexcept { }
		parse_error(const std::string& what_arg) : m_what(what_arg) { }

		const char* what() const noexcept override
		{
			return m_what.c_str();
		}

	private:
		const std::string m_what;
	};
}

#endif // PELI_EXCEPT_H
