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
 * unfolder class is based on overloaded pattern by Dave Abrahams
 * (https://gist.github.com/3779345) distributed under the Boost
 * Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#ifndef PELI_DETAIL_TEMPLATE_SNIPPETS_TEMPLATED_VISITOR_H
#define PELI_DETAIL_TEMPLATE_SNIPPETS_TEMPLATED_VISITOR_H

#include <type_traits>
#include <cassert>

namespace peli
{
	namespace detail
	{
		namespace template_snippets
		{
			namespace templated_visitor
			{
				template<template<typename...> class AtomicVisitor, typename... As> struct unfolder;

				template<template<typename...> class AtomicVisitor, typename A1, typename... As> struct unfolder<AtomicVisitor, A1, As...> :
						AtomicVisitor<A1>, unfolder<AtomicVisitor, As...>
				{
					typedef unfolder type;

					using AtomicVisitor<A1>::visit;
					using unfolder<AtomicVisitor, As...>::type::visit;
				};

				template<template<typename...> class AtomicVisitor, typename A> struct unfolder<AtomicVisitor, A> : AtomicVisitor<A>
				{
					typedef unfolder type;

					using AtomicVisitor<A>::visit;
				};

				template<typename Arg> class abstract_visitor
				{
				public:
					virtual void visit(Arg arg) = 0;
				};

				template<class RealVisitor> class visitor_holder
				{
				protected:
					visitor_holder() : m_visitor(nullptr) { assert(false); }
					visitor_holder(RealVisitor& v) : m_visitor(&v) { }
					RealVisitor& real_visitor() { return *m_visitor; }

				private:
					RealVisitor* const m_visitor;
				};

				template<class RealVisitor, class DynamicVisitor, typename Arg> class visitor_element :
					virtual public DynamicVisitor, virtual public visitor_holder<RealVisitor>
				{
				public:
					visitor_element() { }
					void visit(Arg a) override { this->real_visitor().visit(a); };
					using DynamicVisitor::visit;
				};

				template<class RealVisitor, class DynamicVisitor, typename... Args> class visitor_wrapper
				{
				public:
					template<class Arg> using element_type = visitor_element<RealVisitor, DynamicVisitor, Arg>;

					class type : public unfolder<element_type, Args...>
					{
					public:
						type(RealVisitor& v) : visitor_holder<RealVisitor>(v) { }
					};
				};
			}
		}
	}
}

#endif // PELI_DETAIL_TEMPLATED_VISITOR_H
