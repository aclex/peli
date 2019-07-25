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
#include <cassert>
#include <iostream>

#include "peli/json/value.h"
#include "peli/json/iomanip.h"

using namespace std;

using namespace peli;

void check_boolean()
{
	const string str1 = "[true,false,true,true]";
	const wstring str2 = L"[true,false,true,true]";

	ostringstream os1;
	wostringstream os2;

	json::array ch1 { json::value(true), json::value(false), json::value(true), json::value(true) };
	json::value v1(ch1);
	json::warray ch2 { json::wvalue(true), json::wvalue(false), json::wvalue(true), json::wvalue(true) };
	json::wvalue v2(ch2);

	os1 << v1;
	os2 << v2;

	assert(os1.str() == str1);
	assert(os2.str() == str2);

	os1.clear();
	os1.seekp(0);
	os2.clear();
	os2.seekp(0);
}

int main(int, char**)
{
	check_boolean();

	return 0;
}
