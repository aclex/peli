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

#include "peli/json/iomanip.h"

#include "detail/printer/util.h"

using namespace peli::json;
using namespace peli::detail::printer;

using namespace std;

namespace
{
	template<typename Ch> void pretty_template(basic_ostream<Ch>& os)
	{
		os.iword(flag_storage_index()) |= flag::pretty;
	}

	template<typename Ch> void nopretty_template(basic_ostream<Ch>& os)
	{
		os.iword(flag_storage_index()) &= !flag::pretty;
	}
}

ostream& peli::json::pretty(ostream& os)
{
	pretty_template(os);
	return os;
}

wostream& peli::json::pretty(wostream& os)
{
	pretty_template(os);
	return os;
}

ostream& peli::json::nopretty(ostream& os)
{
	nopretty_template(os);
	return os;
}

wostream& peli::json::nopretty(wostream& os)
{
	nopretty_template(os);
	return os;
}
