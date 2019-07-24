#ifndef PELI_DETAIL_VALUE_BASICS_H
#define PELI_DETAIL_VALUE_BASICS_H

#ifdef INTERNAL_VARIANT
#include <peli/detail/variant/variant.h>
#else
#include <variant>
#endif

#include <peli/detail/template_snippets/copy_cv_reference.h>

namespace peli
{
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

	template<typename T, class Variant>
	constexpr decltype(auto) get(Variant&& v)
	{
#ifdef INTERNAL_VARIANT
		namespace ns = detail::variant;
#else
		namespace ns = std;
#endif
		// slicing is considered harmless here
		return ns::get<T>(std::forward<Variant>(v));
	}

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
