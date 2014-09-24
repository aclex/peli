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

#include <typeinfo>
#include <string>

namespace peli
{
	class bad_value_cast : public std::bad_cast
	{
	public:
		bad_value_cast(const std::string& requested_type_name, const std::string& actual_type_name);
		std::string requested_type_name() const;
		std::string actual_type_name() const;
		const char* what() const throw() override;

	private:
		const std::string m_requested_type_name, m_actual_type_name;
		std::string m_msg;
	};
}
