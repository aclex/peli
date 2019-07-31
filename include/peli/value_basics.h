/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014-2019  Alexey Chernov <4ernov@gmail.com>
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

#ifndef PELI_DETAIL_VALUE_BASICS_H
#define PELI_DETAIL_VALUE_BASICS_H

#ifdef INTERNAL_VARIANT
#include <peli/detail/variant/variant.h>
#else
#include <variant>
#endif

#include <peli/detail/template_snippets/copy_cv_reference.h>

/** \brief Peli types and functions.
 *
 * This namespace contains an alias of variant type used for
 * programming interaction with language constructions and
 * some supplementary types and functions (e.g. exceptions).
 */
namespace peli
{
	/** \brief Alias of variant type used.
	 *
	 * Underlying variant type can be either `std::variant`
	 * (by default, if C++17 support is available in the compiler)
	 * or internal variant implementation.
	 *
	 * \tparam Types the types that may be stored in this variant.
	 * All types must be (possibly cv-qualified) non-array object
	 * types.
	 *
	 * \see `peli::detail::variant`
	 * \see [std::variant](https://en.cppreference.com/w/cpp/utility/variant)
	 */
	template<typename... Types> using variant_type =
#ifdef INTERNAL_VARIANT
	detail::variant::variant
	<
#else
	std::variant
	<
		std::monostate,
#endif
		Types...
	>;

	/** \brief Wrapper for `visit` function.
	 *
	 * Used here mainly as it's not always possible to use types
	 * derived from `std::variant` with `std::visit` directly.
	 * Otherwise it's just a redirection.
	 *
	 * \tparam Visitor visitor type.
	 * \tparam Variant variant type.
	 *
	 * \p vis visitor object.
	 * \p v variant object.
	 *
	 * \return whatever visitor's `operator()` returns.
	 *
	 * \sa [std::visit](https://en.cppreference.com/w/cpp/utility/variant/visit)
	 *
	 */
	template<class Visitor, class Variant>
	constexpr decltype(auto) visit(Visitor&& vis, Variant&& v)
	{
#ifdef INTERNAL_VARIANT
		namespace ns = peli::detail::variant;
#else
		namespace ns = std;
#endif
		using variant_type = template_snippets::copy_cv_reference_t
		<
			Variant,
			typename std::decay_t<Variant>::variant_type
		>;

		// slicing is considered harmless here
		return ns::visit(vis, std::forward<std::remove_reference_t<variant_type>>(static_cast<variant_type>(v)));
	}

	/** \brief Checks if variant value is currently in empty state.
	 *
	 * Empty state meant as `std::monostate` holding in
	 * `std::variant` or invalid state of internal variant.
	 *
	 * \tparam Ts types of variant type passed.
	 *
	 * \p v variant object to check.
	 *
	 * \see [std::monostate](https://en.cppreference.com/w/cpp/utility/variant/monostate)
	 * \see [std::variant](https://en.cppreference.com/w/cpp/utility/variant)
	 */
	template<typename... Ts>
	bool is_empty(const variant_type<Ts...>& v) noexcept
	{
#ifdef INTERNAL_VARIANT
		return !v.valid();
#else
		return !v.index();
#endif
	}
}

#endif // PELI_DETAIL_VALUE_BASICS_H
