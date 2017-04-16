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

#include <cassert>

#include "peli/json/value.h"

using namespace std;

using namespace peli;

int main(int, char**)
{
	int isample(42);

	json::value iv(isample);
	int i(iv);

	assert(isample == i);

	json::value cv(static_cast<char>(isample));
	char c(cv);

	assert(isample == c);

	json::value ucv(static_cast<unsigned char>(isample));
	unsigned char uc(ucv);

	assert(isample == uc);

	json::value scv(static_cast<signed char>(isample));
	signed char sc(cv);

	assert(isample == sc);

	json::value wcv(static_cast<wchar_t>(isample));
	wchar_t wc(wcv);

	assert(isample == wc);

	json::value shiv(static_cast<short>(isample));
	short shi(shiv);

	assert(isample == shi);

	json::value ushiv(static_cast<unsigned short>(isample));
	unsigned short ushi(ushiv);

	assert(isample == ushi);

	json::value uiv(static_cast<unsigned int>(isample));
	unsigned int ui(uiv);

	assert(static_cast<unsigned int>(isample) == ui);

	json::value liv(static_cast<long>(isample));
	long li(liv);

	assert(isample == li);

	json::value uliv(static_cast<unsigned long>(isample));
	unsigned long uli(uliv);

	assert(static_cast<unsigned int>(isample) == uli);

	double dsample(512.5);

	json::value dv(dsample);
	double d(dv);

	assert(dsample == d);

	float fsample(42.0);

	json::value fv(fsample);
	float f(fv);

	assert(fsample == f);

	int fi(fv);

	assert(isample == fi);

	return 0;
}
