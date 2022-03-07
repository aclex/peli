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

#ifndef PELI_TEST_EXCEPTION_CHECK_H
#define PELI_TEST_EXCEPTION_CHECK_H

#include <sstream>

#include "peli/except.h"

#include "peli/json/value.h"

namespace peli
{
	namespace test
	{
		template<class ExceptionType> bool has_thrown_on(const std::string& text)
		{
			bool thrown { };

			std::istringstream is(text);
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

		template<class ExceptionType, typename Ch> bool has_thrown_on(const Ch* text)
		{
			return has_thrown_on<ExceptionType>(std::basic_string<Ch>((text)));
		}

		template<class ExceptionType> bool has_thrown_on(const json::value& v)
		{
			bool thrown { };

			std::ostringstream os;

			try
			{
				os << v;
			}
			catch (const ExceptionType&)
			{
				thrown = true;
			}

			return thrown;
		}

		bool has_null_return(const std::string& text)
		{
			std::istringstream is(text);
			json::value v;

			is >> v;

			return v.null();
		}
	}
}

#endif // PELI_TEST_EXCEPTION_CHECK_H
