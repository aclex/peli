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

#include "peli/json/value.h"

using namespace std;

using namespace peli;

int main(int, char**)
{
	std::string sample;
	sample = "test";

	json::value v(sample);
	std::string& str(get<std::string>(v));

	if (sample != str)
		return -1;

	std::wstring wsample;
	wsample = L"wtest";

	json::value wv(wsample);
	std::wstring& wstr(get<std::wstring>(wv));

	if (wsample != wstr)
		return -2;

	return 0;
}
