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

int main(int, char**)
{
	const string test_json = "{ \"привет\" : \"мир\" }";
	std::istringstream istr(test_json);
	json::value v;
	istr >> v;

	const auto& obj = get<json::object>(v);

	for (const auto& p : obj)
	{
		const auto& str = get<string>(p.second);
		cout << "проверка: " << p.first << " : " << str << endl;
	}

	return 0;
}
