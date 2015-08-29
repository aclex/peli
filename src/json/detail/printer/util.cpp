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

#include "json/detail/printer/util.h"

#include <ios>

using namespace peli::json::detail::printer;

using namespace std;

int peli::json::detail::printer::flag_storage_index()
{
	static int i = ios_base::xalloc();
	return i;
}

int peli::json::detail::printer::tab_level_storage_index()
{
	static int i = ios_base::xalloc();
	return i;
}
