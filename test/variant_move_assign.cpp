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

#include <type_traits>

#include "peli/json/value.h"

using namespace std;

using namespace peli;

int main(int, char**)
{
	json::value v1(json::make_value<json::object>());
	json::object& obj1(get<json::object>(v1));
	obj1["test"] = json::number { 52 };

	json::value v2;

	// not guaranteed in Standard, though passes in GCC and Clang (not in MSVC)
	// static_assert(std::is_nothrow_move_assignable<json::value>::value, "Move assignment isn't noexcept");

	v2 = std::move(v1);

	json::object& obj2(get<json::object>(v2));
	obj2["tost"] = false;

	return 0;
}
