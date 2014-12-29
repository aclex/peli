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
			struct value_factory
			{
			private:
				template<typename T> using template_holder_type = value_holder_template<T>;

			public:
				typedef value_holder value_type;

				static value_type* clone(const value_type* v)
				{
					return v->clone();
				}

				template<typename T> static value_type* create(const T& op)
				{
					return new template_holder_type<T>(op);
				}

				template <typename U> static U cast(const value_type* v)
				{
					if (!v)
						throw std::invalid_argument("Value is not initialized");

					if (typeid(U) != v->type_info())
						throw std::runtime_error("Bad cast");

					return static_cast<const template_holder_type<U>*>(v)->template variant_as<U>();
				}

				template <typename U> static U cast(value_type* v)
				{
					if (!v)
						throw std::invalid_argument("Value is not initialized");

					if (typeid(U) != v->type_info())
						throw std::runtime_error("Bad cast");

					return static_cast<template_holder_type<U>*>(v)->template variant_as<U>();
				}

				static value_type* parse(std::istream& is);
				static value_type* parse(std::wistream& is);
			};
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_VALUE_FACTORY_H
