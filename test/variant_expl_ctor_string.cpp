/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014-2022  Alexey Chernov <4ernov@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

	json::wvalue wv(wsample);
	std::wstring& wstr(get<std::wstring>(wv));

	if (wsample != wstr)
		return -2;

	return 0;
}
