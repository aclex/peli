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

#ifndef PELI_DETAIL_VARIANT_VALUE_VALUE_HOLDER_H
#define PELI_DETAIL_VARIANT_VALUE_VALUE_HOLDER_H

#include <typeinfo>

namespace peli
{
	namespace detail
	{
		namespace printer
		{
			class tray;
		}

		namespace variant_value
		{
			class value_holder
			{
			public:
				virtual value_holder* clone() const = 0;
				virtual void print(printer::tray* t) const = 0;
				virtual const std::type_info& type_info() const noexcept = 0;
				virtual bool equals(const value_holder& rhs) const noexcept = 0;
				virtual ~value_holder() noexcept { }
			};
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_VALUE_HOLDER_H
