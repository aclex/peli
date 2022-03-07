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
