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

namespace
{
	template<class ExceptionType> bool has_thrown_on(const string& text)
	{
		bool thrown { };

		istringstream is(text);
		json::value v;

		try
		{
			is >> v;
		}
		catch (const ExceptionType&)
		{
			thrown = true;
		}

		return thrown;
	}
}

int check_boolean()
{
	const string str1 = "   [\n\ttrue, false, true, true   ]\r\n  ";
	const wstring str2 = L"[  \r\ttrue, false, true, true   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& arr1(get<json::array>(v1));
	const json::warray& arr2(get<json::warray>(v2));
	json::array ch1 { json::value(true), json::value(false), json::value(true), json::value(true) };
	json::warray ch2 { json::wvalue(true), json::wvalue(false), json::wvalue(true), json::wvalue(true) };

	if (arr1 != ch1)
		return 1;

	if (arr2 != ch2)
		return 2;

	return 0;
}

int check_typos()
{
	if (!has_thrown_on<invalid_argument>("tee"))
		return 3;

	if (!has_thrown_on<invalid_argument>("tree"))
		return 4;

	if (!has_thrown_on<invalid_argument>("truu"))
		return 5;

	if (!has_thrown_on<invalid_argument>("filse"))
		return 6;

	if (!has_thrown_on<invalid_argument>("faasl"))
		return 7;

	if (!has_thrown_on<invalid_argument>("falce"))
		return 8;

	if (!has_thrown_on<invalid_argument>("falsa"))
		return 9;

	return 0;
}

int main(int, char**)
{
	if (auto r = check_boolean())
	{
		return r;
	}

	if (auto r = check_typos())
	{
		return r;
	}

	return 0;
}
