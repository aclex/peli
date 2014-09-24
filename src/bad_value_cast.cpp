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

#include "peli/bad_value_cast.h"

using namespace std;

using namespace peli;

bad_value_cast::bad_value_cast(const std::string& requested_type_name, const std::string& actual_type_name) :
	m_requested_type_name(requested_type_name),
	m_actual_type_name(actual_type_name)
{
	m_msg = string("Can't perform value cast: type ") + m_requested_type_name + " was requested, but actual type is " + m_actual_type_name + '.';
}

string bad_value_cast::requested_type_name() const
{
	return m_requested_type_name;
}

string bad_value_cast::actual_type_name() const
{
	return m_actual_type_name;
}

const char* bad_value_cast::what() const throw()
{
    return m_msg.c_str();
}
