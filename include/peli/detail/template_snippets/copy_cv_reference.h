/*
 * `copy_cv_reference` solution taken from Stack Overflow answer by Daniel Frey:
 * https://stackoverflow.com/a/31173086/4297846
 */

#ifndef TYPE_TRAITS_COPY_CV_REFERENCE_H
#define TYPE_TRAITS_COPY_CV_REFERENCE_H

#include <type_traits>

/** \brief Contains some snippets and helpers for template programming. */
namespace template_snippets
{
	/** \brief Copies cv-qualifiers and referenceness of one type to another.
	 *
	 * Cv-qualifiers and referenceness of type `T` is copied to type `U`.
	 * This implementation is taken from
	 * [Stack Overflow answer by Daniel Frey](https://stackoverflow.com/a/31173086/4297846).
	 *
	 * \tparam T source type (to copy from).
	 * \tparam U target type (to copy to).
	 */
	template<typename T,typename U>
	struct copy_cv_reference
	{
	private:
		using R = std::remove_reference_t<T>;
		using U1 = std::conditional_t<std::is_const<R>::value, std::add_const_t<U>, U>;
		using U2 = std::conditional_t<std::is_volatile<R>::value, std::add_volatile_t<U1>, U1>;
		using U3 = std::conditional_t<std::is_lvalue_reference<T>::value, std::add_lvalue_reference_t<U2>, U2>;
		using U4 = std::conditional_t<std::is_rvalue_reference<T>::value, std::add_rvalue_reference_t<U3>, U3>;
	public:
		/** \brief Resulting type. */
		using type = U4;
	};

	/** \brief Helper alias to reach the result of `copy_cv_reference` faster. */
	template<typename T,typename U>
	using copy_cv_reference_t = typename copy_cv_reference<T,U>::type;
}

#endif // TYPE_TRAITS_COPY_CV_REFERENCE_H
