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

#include <sstream>
#include <iostream>

#include "peli/json/value.h"

using namespace std;

using namespace peli;

bool check()
{
	const string str1 = "[null]";
	const wstring str2 = L"[null]";

	ostringstream os1;
	wostringstream os2;

	json::array ch1 { json::value() };
	json::value v1(ch1);
	json::warray ch2 { json::wvalue() };
	json::wvalue v2(ch2);

	os1 << v1;
	os2 << v2;

	if (os1.str() != str1)
		return false;

	if (os2.str() != str2)
		return false;

	return true;
}

int main(int, char**)
{
	if (!check())
		return 1;

	return 0;
}
