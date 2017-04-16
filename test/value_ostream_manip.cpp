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
#include "peli/json/iomanip.h"

using namespace std;

using namespace peli;

int main(int, char**)
{
	json::value v = json::make_value<json::object>();
	json::object& obj(v);
	obj["привет"] = json::value("мир");
	obj["ты"] = json::value("добр");

	cout << "проверка:" << endl << v << endl;
	cout << "проверка манипуляцией:" << endl << json::pretty << v << endl;
	cout << "повторная проверка:" << endl << json::nopretty << v << endl;

	return 0;
}
