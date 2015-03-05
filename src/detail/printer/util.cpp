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

#include "detail/printer/util.h"

#include <ios>

using namespace peli::detail::printer;

using namespace std;

int peli::detail::printer::flag_storage_index()
{
	static int i = ios_base::xalloc();
	return i;
}

int peli::detail::printer::tab_level_storage_index()
{
	static int i = ios_base::xalloc();
	return i;
}

bool flag::get(const long& flag_word, long flag)
{
	return flag_word & flag;
}

void flag::set(long& flag_word, long flag)
{
	flag_word |= flag;
}

void flag::unset(long& flag_word, long flag)
{
	flag_word &= ~flag;
}

