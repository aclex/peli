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

#ifndef PELI_DETAIL_VARIANT_VALUE_H
#define PELI_DETAIL_VARIANT_VALUE_H

#include <stdexcept>
#include <type_traits>

#include <peli/object.h>
#include <peli/array.h>

#include "type_traits.h"

namespace peli
{
	namespace detail
	{
		class variant_value
		{
		public:
			template <typename T> typename type_tag<T>::type::return_type as()
			{
				return variant_as(type_tag<T>::type::value);
			}

			template <typename T, typename V = typename std::enable_if<std::is_const<T>::value, T>::type> typename type_tag<V>::type::return_type as() const
			{
				return variant_as(type_tag<V>::type::value);
			}

		private:
			virtual object variant_as(typename object_type_tag::type tag) const;
			virtual object& variant_as(typename object_type_tag::ref_type tag);
			virtual const object& variant_as(typename object_type_tag::cref_type tag) const;

			virtual array variant_as(typename array_type_tag::type tag) const;
			virtual array& variant_as(typename array_type_tag::ref_type tag);
			virtual const array& variant_as(typename array_type_tag::cref_type tag) const;

			virtual int variant_as(typename number_type_tag::type tag) const;
			virtual int& variant_as(typename number_type_tag::ref_type tag) const;
			virtual const int& variant_as(typename number_type_tag::cref_type tag) const;

			virtual double variant_as(typename real_type_tag::type tag) const;
			virtual double& variant_as(typename real_type_tag::ref_type tag) const;
			virtual const double& variant_as(typename real_type_tag::cref_type tag) const;

			virtual bool variant_as(typename boolean_type_tag::type tag) const;
			virtual bool& variant_as(typename boolean_type_tag::ref_type tag) const;
			virtual const bool& variant_as(typename boolean_type_tag::cref_type tag) const;

			virtual std::string variant_as(typename string_type_tag::type tag) const;
			virtual std::string& variant_as(typename string_type_tag::ref_type tag) const;
			virtual const std::string& variant_as(typename string_type_tag::cref_type tag) const;

			virtual std::string type_name() const;

			void bad_as(const std::string& requested_type_name) const;
		};
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_H
