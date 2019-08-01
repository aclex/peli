/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2019  Alexey Chernov <4ernov@gmail.com>
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

#ifndef PELI_DETAIL_TEMPLATE_SNIPPETS_CHECK_IN_PACK_H
#define PELI_DETAIL_TEMPLATE_SNIPPETS_CHECK_IN_PACK_H

namespace template_snippets
{
	/** \brief Checks if the predicate is true for any of the types in the pack.
	 *
	 * Another C++17 feature workaround, for checking the value of
	 * predicate on all the types in the list. Returns true, if the
	 * predicate succeeds for any of the types.
	 *
	 * \tparam Pred predicate type to check.
	 * \tparam List types to apply the predicate to.
	 */
	template<template<class> class Pred, typename... List> struct check_any_in_pack;

	template<template<class> class Pred, typename Head, typename... Rest>
	struct check_any_in_pack<Pred, Head, Rest...> :
		std::conditional
		<
			Pred<Head>::value,
			std::true_type,
			check_any_in_pack<Pred, Rest...>
		>::type
	{

	};

	template<template<class> class Pred> struct check_any_in_pack<Pred> : std::false_type { };

	template<template<class> class Pred, typename... List> struct check_all_in_pack;

	/** \brief Checks if the predicate is true for all the types in the pack.
	 *
	 * Another C++17 feature workaround, for checking the value of
	 * predicate on all the types in the list. Returns true, if the
	 * predicate succeeds for all of the types.
	 *
	 * \tparam Pred predicate type to check.
	 * \tparam List types to apply the predicate to.
	 */
	template<template<class> class Pred, typename Head, typename... Rest>
	struct check_all_in_pack<Pred, Head, Rest...> :
		std::conditional
	<
		Pred<Head>::value,
		check_all_in_pack<Pred, Rest...>,
		std::false_type
		>::type
	{

	};

	template<template<class> class Pred> struct check_all_in_pack<Pred> : std::false_type { };
}

#endif // PELI_DETAIL_TEMPLATE_SNIPPETS_CHECK_IN_PACK_H
