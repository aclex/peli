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
 * using_unfolder class is based on overloaded pattern by Dave Abrahams
 * (https://gist.github.com/3779345) distributed under the Boost
 * Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#ifndef PELI_DETAIL_TEMPLATE_SNIPPETS_TEMPLATED_VISITOR_H
#define PELI_DETAIL_TEMPLATE_SNIPPETS_TEMPLATED_VISITOR_H

#include <type_traits>

namespace peli
{
	namespace detail
	{
		namespace template_snippets
		{
			namespace templated_visitor
			{
				template<typename Arg> struct object_argument_visitor
				{
					virtual void visit(const Arg&) { }
				};

				template<typename Arg> struct value_argument_visitor
				{
					virtual void visit(Arg) { }
				};

				template<typename Arg> using argument_visitor =
						typename std::conditional<std::is_fundamental<Arg>::value,
							value_argument_visitor<Arg>, object_argument_visitor<Arg>>::type;

				template<template<typename...> class AtomicVisitor, typename... As> struct using_unfolder;

				template<template<typename...> class AtomicVisitor, typename A1, typename... As> struct using_unfolder<AtomicVisitor, A1, As...> :
						AtomicVisitor<A1>, using_unfolder<AtomicVisitor, As...>
				{
						typedef using_unfolder type;

						using AtomicVisitor<A1>::visit;
						using using_unfolder<AtomicVisitor, As...>::type::visit;
				};

				template<template<typename...> class AtomicVisitor, typename A> struct using_unfolder<AtomicVisitor, A> : AtomicVisitor<A>
				{
						typedef using_unfolder type;

						using AtomicVisitor<A>::visit;
				};

				template<typename... Ts> using visitor = using_unfolder<argument_visitor, Ts...>;
			}
		}
	}
}

#endif // PELI_DETAIL_TEMPLATED_VISITOR_H
