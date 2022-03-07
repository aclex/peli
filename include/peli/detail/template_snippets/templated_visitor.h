/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014-2022  Alexey Chernov <4ernov@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * unfolder class is based on overloaded pattern by Dave Abrahams
 * (https://gist.github.com/3779345) distributed under the Boost
 * Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef PELI_DETAIL_TEMPLATE_SNIPPETS_TEMPLATED_VISITOR_H
#define PELI_DETAIL_TEMPLATE_SNIPPETS_TEMPLATED_VISITOR_H

#include <type_traits>
#include <cassert>

namespace peli
{
	namespace detail
	{
		/** \brief Contains some snippets and helpers for template programming. */
		namespace template_snippets
		{
			/** \brief Contains recursive templates to construct visitor for a number of types.
			 *
			 * Creates a family of classes with each containing a method receiving a value of
			 * one type of the set and then recursively inheriting all these classes to
			 * construct one with all these function methods as one overloaded method
			 * function.
			 */
			namespace templated_visitor
			{
				/** \brief Recursive unfolder template.
				 *
				 * Note, that this is not necessary in C++17 due to
				 * [enhanced functionality of `using` keyword](https://en.cppreference.com/w/cpp/language/using_declaration).
				 *
				 * \tparam AtomicVisitor template of visitor part implementation.
				 * It is expected to contain a code (with possible specialization)
				 * processing values of all possible types in the pack.
				 * \tparam As types to make visitor for. In other words, a set
				 * of types, which values the resulting visitor should process.
				 */
				template<template<typename...> class AtomicVisitor, typename... As> struct unfolder;

				/** \brief Specialization of main recursive unfolder definition.
				 *
				 * Please, note, that in C++14 method name (`visit` here) is
				 * needed for this recursive trick inevitably, so it's not possible to
				 * make any universal snippet.
				 *
				 */
				template<template<typename...> class AtomicVisitor, typename A1, typename... As> struct unfolder<AtomicVisitor, A1, As...> :
						AtomicVisitor<A1>, unfolder<AtomicVisitor, As...>
				{
					/** \brief Reference to unfolder for futher unfolding. */
					typedef unfolder type;

					using AtomicVisitor<A1>::visit;
					using unfolder<AtomicVisitor, As...>::type::visit;
				};

				/** \brief Terminal state of the template recursion. */
				template<template<typename...> class AtomicVisitor, typename A> struct unfolder<AtomicVisitor, A> : AtomicVisitor<A>
				{
					/** \brief Reference to unfolder, just for consistency. */
					typedef unfolder type;

					using AtomicVisitor<A>::visit;
				};

				/** \brief Abstract type to create a visitor part. */
				template<typename Arg> class abstract_visitor
				{
				public:
					/** \brief Visiting function. */
					virtual void visit(Arg arg) = 0;
				};

				/** Type erasure template to convert dynamic call to static one. */
				template<class RealVisitor> class visitor_holder
				{
				protected:
					/** \brief Default constructor. Result holds no visitor. */
					visitor_holder() : m_visitor(nullptr) { assert(false); }
					/** \brief Constructor initializing the value with pointer to real visitor. */
					visitor_holder(RealVisitor& v) : m_visitor(&v) { }
					/** \brief Stored real visitor accessor function. */
					RealVisitor& real_visitor() { return *m_visitor; }

				private:
					RealVisitor* const m_visitor;
				};

				/** \brief Wrapper of real visitor to apply it as dynamic visitor.
				 *
				 * It is needed to apply the passed visitor object to our dynamic
				 * hierarchy in the variant, since there's no virtual function templates.
				 *
				 * \tparam RealVisitor type of actual visitor.
				 * \tparam DynamicVisitor type of dynamic visitor to dispatch calls.
				 * \tparam Arg actually one of alternative types for which this part
				 * is instantiated.
				 *
				 */
				template<class RealVisitor, class DynamicVisitor, typename Arg> class visitor_element :
					virtual public DynamicVisitor, virtual public visitor_holder<RealVisitor>
				{
				public:
					/** \brief Default constructor. */
					visitor_element() { }
					/** \brief Just redirects a call to the real visitor stored. */
					void visit(Arg a) override { this->real_visitor()(a); };
					using DynamicVisitor::visit;
				};

				/** \brief Finally a template, that put it all together.
				 *
				 * \tparam RealVisitor type of actual visitor.
				 * \tparam DynamicVisitor type of dynamic visitor to dispatch calls.
				 * \tparam Args all the types planned to be processed.
				 */
				template<class RealVisitor, class DynamicVisitor, typename... Args> class visitor_wrapper
				{
				public:
					/** \brief Visitor element type. */
					template<class Arg> using element_type = visitor_element<RealVisitor, DynamicVisitor, Arg>;

					/** \brief The result type. */
					class type : public unfolder<element_type, Args...>
					{
					public:
						/** \brief Constructs the wrapper ready to apply around the real visitor. */
						type(RealVisitor& v) : visitor_holder<RealVisitor>(v) { }
					};
				};
			}
		}
	}
}

#endif // PELI_DETAIL_TEMPLATED_VISITOR_H
