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

#include <stdexcept>
#include <iostream>

#include "json/detail/printer/stream_routines.h"

#include "json/detail/printer/object.h"
#include "json/detail/printer/string.h"
#include "json/detail/printer/array.h"
// #include "json/detail/printer/number.h"
#include "json/detail/printer/boolean.h"
#include "json/detail/printer/null.h"

template<typename Ch, typename Visitor> peli::json::detail::printer::typewriter<Ch, Visitor>::typewriter(std::basic_ostream<Ch>& os) :
	rdbuf(os.rdbuf()),
	pretty(is_pretty_printing(os)),
	tab_level(0),
	need_structure_newline(false)
{
	if (!typename std::basic_ostream<Ch>::sentry(os))
	{
		throw std::invalid_argument("");
	}
}

template<typename Ch, typename Visitor> template<typename U> void peli::json::detail::printer::typewriter<Ch, Visitor>::print(const U& v)
{
	printer::head<U>::print(this, v);
}

template<typename Ch, typename Visitor> void peli::json::detail::printer::typewriter<Ch, Visitor>::print()
{
	printer::head<void>::print(this);
}

template<typename Ch, typename Visitor> void peli::json::detail::printer::typewriter<Ch, Visitor>::print(const json::value& v)
{
	static_cast<Visitor*>(this)->visit(v);
}
