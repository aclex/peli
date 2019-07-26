/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2019  Alexey Chernov <4ernov@gmail.com>
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

#ifndef PELI_TEST_EXCEPTION_CHECK_H
#define PELI_TEST_EXCEPTION_CHECK_H

#include <sstream>

#include "peli/json/value.h"

using namespace std;

using namespace peli;

namespace peli
{
	namespace test
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
}

#endif // PELI_TEST_EXCEPTION_CHECK_H