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
	json::number isample(42);

	json::value iv(isample);
	int i(get<json::number>(iv));

	if (isample != i)
		return -1;

	json::value cv(isample);
	char c(get<json::number>(cv));

	if (isample != c)
		return -2;

	json::value ucv(isample);
	unsigned char uc(get<json::number>(ucv));

	if (isample != uc)
		return -3;

	json::value scv(isample);
	signed char sc(get<json::number>(cv));

	if (isample != sc)
		return -4;

	json::value wcv(isample);
	wchar_t wc(get<json::number>(wcv));

	if (isample != wc)
		return -5;

	json::value shiv(isample);
	short shi(get<json::number>(shiv));

	if (isample != shi)
		return -6;

	json::value ushiv(isample);
	unsigned short ushi(get<json::number>(ushiv));

	if (isample != ushi)
		return -7;

	json::value uiv(isample);
	unsigned int ui(get<json::number>(uiv));

	if (isample != ui)
		return -8;

	json::value liv(isample);
	long li(get<json::number>(liv));

	if (isample != li)
		return -9;

	json::value uliv(isample);
	unsigned long uli(get<json::number>(uliv));

	if (static_cast<unsigned int>(isample) != uli)
		return -10;

	json::number dsample(512.5);

	json::value dv(dsample);
	double d(get<json::number>(dv));

	if (dsample != d)
		return -11;

	json::number fsample(42.0f);

	json::value fv(fsample);
	float f(get<json::number>(fv));

	if (fsample != f)
		return -12;

	int fi(get<json::number>(fv));

	if (isample != fi)
		return -13;

	return 0;
}
