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

#ifndef PELI_EXCEPT_H
#define PELI_EXCEPT_H

#include <stdexcept>

namespace peli
{
	class parse_error : public std::exception
	{
	public:
		parse_error() noexcept { }
		parse_error(const std::string& what_arg) : m_what(what_arg) { }

		const char* what() const noexcept override
		{
			return m_what.c_str();
		}

	private:
		const std::string m_what;
	};
}

#endif // PELI_EXCEPT_H
