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

#ifndef PELI_DETAIL_TEMPLATE_SNIPPETS_TYPE_LIST_H
#define PELI_DETAIL_TEMPLATE_SNIPPETS_TYPE_LIST_H

#include <type_traits>

namespace peli
{
	namespace detail
	{
		namespace template_snippets
		{
			template<typename... Ts> struct type_list { };

			template<typename TypeList, typename Op, std::size_t Index=0> struct index_of { };
			template<typename TypeList, std::size_t Op, std::size_t Index=0> struct type_at { };

			template<typename A1, typename... As, typename Op, std::size_t Index>
				struct index_of<type_list<A1, As...>, Op, Index> :
					std::conditional<std::is_same<A1, Op>::value, std::integral_constant<std::size_t, Index>, index_of<type_list<As...>, Op, Index + 1>>::type
			{

			};

			template<typename A1, typename Op, std::size_t Index>
				struct index_of<type_list<A1>, Op, Index> :
					std::conditional<std::is_same<A1, Op>::value, std::integral_constant<std::size_t, Index>, std::false_type>::type
			{
				static_assert(std::is_same<A1, Op>::value, "Type was not found in the list");
			};

			template<typename A1, typename... As, std::size_t Op, std::size_t Index>
				struct type_at<type_list<A1, As...>, Op, Index> :
					std::conditional<Op == Index, A1, typename type_at<type_list<As...>, Op, Index + 1>::type>
			{

			};

			template<typename A1, std::size_t Op, std::size_t Index>
				struct type_at<type_list<A1>, Op, Index> :
					std::conditional<Op == Index, A1, std::false_type>
			{
				static_assert(Op != Index, "Type at index was not found in the list");
			};
		}
	}
}

#endif // PELI_DETAIL_TEMPLATE_SNIPPETS_TYPE_LIST_H
