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

#ifndef PELI_DETAIL_TYPE_TRAITS_H
#define PELI_DETAIL_TYPE_TRAITS_H

#include <map>
#include <string>
#include <vector>
#include <type_traits>

namespace peli
{
	class value_shell;

	namespace detail
	{
		template <typename Ret> struct type_traits
		{
			const static type_traits value;
			typedef Ret return_type;
		};

		template<typename T, typename Ret> struct tag
		{
		private:
			typedef typename std::decay<Ret>::type cleared_type;

		public:
			typedef type_traits<cleared_type> type;
			typedef type_traits<cleared_type&> ref_type;
			typedef type_traits<const cleared_type&> cref_type;
		};

		struct object_type_tag : tag<object_type_tag, std::map<std::string, value_shell>> { static constexpr char name[] = "object"; };
		struct array_type_tag : tag<array_type_tag, std::vector<value_shell>> { static constexpr char name[] = "array"; };
		struct number_type_tag : tag<number_type_tag, int> { static constexpr char name[] = "number"; };
		struct real_type_tag : tag<real_type_tag, double> { static constexpr char name[] = "number"; };
		struct string_type_tag : tag<string_type_tag, std::string> { static constexpr char name[] = "string"; };
		struct boolean_type_tag : tag<boolean_type_tag, bool> { static constexpr char name[] = "boolean"; };

		template<typename T> struct type_tag;

		template<> struct type_tag<object_type_tag::type::return_type>
		{
			typedef object_type_tag tag;
			typedef typename object_type_tag::type type;
		};

		template<> struct type_tag<object_type_tag::ref_type::return_type>
		{
			typedef object_type_tag tag;
			typedef typename object_type_tag::ref_type type;
		};

		template<> struct type_tag<object_type_tag::cref_type::return_type>
		{
			typedef object_type_tag tag;
			typedef typename object_type_tag::cref_type type;
		};

		template<> struct type_tag<array_type_tag::type::return_type>
		{
			typedef array_type_tag tag;
			typedef typename array_type_tag::type type;
		};

		template<> struct type_tag<array_type_tag::ref_type::return_type>
		{
			typedef array_type_tag tag;
			typedef typename array_type_tag::ref_type type;
		};

		template<> struct type_tag<array_type_tag::cref_type::return_type>
		{
			typedef array_type_tag tag;
			typedef typename array_type_tag::cref_type type;
		};

		template<> struct type_tag<number_type_tag::type::return_type>
		{
			typedef number_type_tag tag;
			typedef typename number_type_tag::type type;
		};

		template<> struct type_tag<number_type_tag::ref_type::return_type>
		{
			typedef number_type_tag tag;
			typedef typename number_type_tag::ref_type type;
		};

		template<> struct type_tag<number_type_tag::cref_type::return_type>
		{
			typedef number_type_tag tag;
			typedef typename number_type_tag::cref_type type;
		};

		template<> struct type_tag<real_type_tag::type::return_type>
		{
			typedef real_type_tag tag;
			typedef typename real_type_tag::type type;
		};

		template<> struct type_tag<real_type_tag::ref_type::return_type>
		{
			typedef real_type_tag tag;
			typedef typename real_type_tag::ref_type type;
		};

		template<> struct type_tag<real_type_tag::cref_type::return_type>
		{
			typedef real_type_tag tag;
			typedef typename real_type_tag::cref_type type;
		};

		template<> struct type_tag<string_type_tag::type::return_type>
		{
			typedef string_type_tag tag;
			typedef string_type_tag::type type;
		};

		template<> struct type_tag<string_type_tag::ref_type::return_type>
		{
			typedef string_type_tag tag;
			typedef string_type_tag::ref_type type;
		};

		template<> struct type_tag<string_type_tag::cref_type::return_type>
		{
			typedef string_type_tag tag;
			typedef string_type_tag::cref_type type;
		};

		template<> struct type_tag<boolean_type_tag::type::return_type>
		{
			typedef boolean_type_tag tag;
			typedef boolean_type_tag::type type;
		};

		template<> struct type_tag<boolean_type_tag::ref_type::return_type>
		{
			typedef boolean_type_tag tag;
			typedef boolean_type_tag::ref_type type;
		};

		template<> struct type_tag<boolean_type_tag::cref_type::return_type>
		{
			typedef boolean_type_tag tag;
			typedef boolean_type_tag::cref_type type;
		};
	}
}

#endif // PELI_DETAIL_TYPE_TRAITS_H
