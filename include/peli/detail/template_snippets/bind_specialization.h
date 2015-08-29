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

#ifndef PELI_DETAIL_TEMPLATE_SNIPPETS_BIND_SPECIALIZATION_H
#define PELI_DETAIL_TEMPLATE_SNIPPETS_BIND_SPECIALIZATION_H

namespace peli
{
	namespace detail
	{
		namespace template_snippets
		{
			template<template<typename...> class Type, typename... PersistentArgs> struct bind_specialization
			{
				template<typename... Args> using type = Type<PersistentArgs..., Args...>;
			};
		}
	}
}

#endif // PELI_DETAIL_TEMPLATE_SNIPPETS_EXTRACT_PARTIAL_SPEC_H
