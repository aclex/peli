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

#ifndef PELI_DETAIL_PRINTER_VALUE_H
#define PELI_DETAIL_PRINTER_VALUE_H

#include <stdexcept>

#include <peli/json/object.h>
#include <peli/json/array.h>
#include <peli/json/number.h>

namespace peli
{
	namespace detail
	{
		namespace printer
		{
			class tray
			{
			public:
				virtual void put(const peli::json::object& obj) = 0;
				virtual void put(const peli::json::array& arr) = 0;
				virtual void put(const std::string& str) = 0;
				virtual void put(json::number n) = 0;
				virtual void put(bool b) = 0;
				virtual void put() = 0;
			};
		}
	}
}

#endif // PELI_DETAIL_PRINTER_VALUE_H
