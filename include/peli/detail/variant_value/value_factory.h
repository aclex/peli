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

#ifndef PELI_DETAIL_VARIANT_VALUE_VALUE_FACTORY_H
#define PELI_DETAIL_VARIANT_VALUE_VALUE_FACTORY_H

#include <istream>
#include <stdexcept>

#include <peli/detail/variant_value/value_holder_template.h>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			class value_factory
			{
				template<typename T> using template_holder_type = value_holder_template<T>;

			public:
				typedef value_holder value_type;

				static value_type* clone(const value_type* v)
				{
					return v->clone();
				}

				static bool equal(const value_type* lhs, const value_type* rhs)
				{
					if (lhs->type_info() != rhs->type_info())
						return false;

					return lhs->equals(*rhs);
				}

				template<typename T> static value_type* create()
				{
					return new template_holder_type<T>();
				}

				template<typename T> static value_type* create(const T& op)
				{
					return new template_holder_type<T>(op);
				}

				template<typename U> static U cast(const value_type* v)
				{
					return call_cast<U>(v);
				}

				template<typename U> static U cast(value_type* v)
				{
					return call_cast<U>(v);
				}

				static value_type* parse(std::istream& is);
				static value_type* parse(std::wistream& is);

				static void print(std::ostream& os, const value_type* v);
				static void print(std::wostream& os, const value_type* v);

			private:
				template<typename U, typename ValueTypePtr> static U call_cast(ValueTypePtr* v)
				{
					typedef typename std::decay<U>::type decayed_u;

					if (!v)
						throw std::invalid_argument("Value is not initialized");

					if (typeid(decayed_u) != v->type_info())
						throw std::bad_cast();

					typedef typename std::conditional<std::is_const<ValueTypePtr>::value,
							const template_holder_type<decayed_u>*, template_holder_type<decayed_u>*>::type holder_type;

					return static_cast<holder_type>(v)->template variant_as<U>();
				}
			};
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_VALUE_FACTORY_H
