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
	int isample(42);

	json::value iv(isample);
	int i(iv);

	if (isample != i)
		return -1;

	json::value cv(static_cast<char>(isample));
	char c(cv);

	if (isample != c)
		return -2;

	json::value ucv(static_cast<unsigned char>(isample));
	unsigned char uc(ucv);

	if (isample != uc)
		return -3;

	json::value scv(static_cast<signed char>(isample));
	signed char sc(cv);

	if (isample != sc)
		return -4;

	json::value wcv(static_cast<wchar_t>(isample));
	wchar_t wc(wcv);

	if (isample != wc)
		return -5;

	json::value shiv(static_cast<short>(isample));
	short shi(shiv);

	if (isample != shi)
		return -6;

	json::value ushiv(static_cast<unsigned short>(isample));
	unsigned short ushi(ushiv);

	if (isample != ushi)
		return -7;

	json::value uiv(static_cast<unsigned int>(isample));
	unsigned int ui(uiv);

	if (static_cast<unsigned int>(isample) != ui)
		return -8;

	json::value liv(static_cast<long>(isample));
	long li(liv);

	if (isample != li)
		return -9;

	json::value uliv(static_cast<unsigned long>(isample));
	unsigned long uli(uliv);

	if (static_cast<unsigned int>(isample) != uli)
		return -10;

	double dsample(512.5);

	json::value dv(dsample);
	double d(dv);

	if (dsample != d)
		return -11;

	float fsample(42.0);

	json::value fv(fsample);
	float f(fv);

	if (fsample != f)
		return -12;

	int fi(fv);

	if (isample != fi)
		return -13;

	return 0;
}
