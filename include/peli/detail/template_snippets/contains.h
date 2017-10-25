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

#ifndef PELI_DETAIL_TEMPLATE_SNIPPETS_CONTAINS_H
#define PELI_DETAIL_TEMPLATE_SNIPPETS_CONTAINS_H

namespace peli
{
	namespace detail
	{
		namespace template_snippets
		{
			template<typename Tp, typename... List> struct contains;

			template<typename Tp, typename Head, typename... Rest> struct contains<Tp, Head, Rest...>
				: std::conditional<std::is_same<Tp, Head>::value, std::true_type, contains<Tp, Rest...>>::type
			{

			};

			template<typename Tp> struct contains<Tp> : std::false_type { };

			template<typename Tp, typename... Args> struct pack_holds;

			template<typename Tp, template<typename...> class Cont, typename... Types> struct pack_holds<Tp, Cont<Types...>> : contains<Tp, Types...> {};
		}
	}
}

#endif // PELI_DETAIL_TEMPLATE_SNIPPETS_CONTAINS_H
