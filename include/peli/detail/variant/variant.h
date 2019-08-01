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
 *
 * Variant implementation was inspired by article "Implementing a variant type
 * from scratch in C++" by Tibor Djurica Potpara
 * (https://www.ojdip.net/2013/10/implementing-a-variant-type-in-cpp/) and
 * corresponding example implementation.
 *
 */

#ifndef PELI_DETAIL_VARIANT_VARIANT_H
#define PELI_DETAIL_VARIANT_VARIANT_H

#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>

#include <peli/detail/template_snippets/check_in_pack.h>
#include <peli/detail/template_snippets/templated_visitor.h>

namespace peli
{
	/** \brief Various implementation details.
	 */
	namespace detail
	{
		/** \brief A no-op function to perform 'through `void*`' conversion hint.
		 *
		 * Performs implicit conversion to `void*` on argument initialization and
		 * `static_cast` conversion to the target type in its body.
		 *
		 * \tparam T target type of conversion.
		 *
		 * \param ptr pointer to convert.
		 *
		 * \return pointer to object of type `T`.
		 *
		 */
		template<typename T> constexpr T safe_cast(void* ptr)
		{
			return static_cast<T>(ptr);
		}

		/** \brief `safe_cast` version for pointers to const. */
		template<typename T> constexpr T safe_cast(const void* ptr)
		{
			return static_cast<T>(ptr);
		}

		/** \brief Internal implementation of variant type.
		 *
		 * Provides
		 * [`std::aligned_storage`](https://en.cppreference.com/w/cpp/types/aligned_storage)-based
		 * implementation of variant type for use as programming
		 * representation of different language entity objects. The interface
		 * especially written to be closer to
		 * [`std::variant`](https://en.cppreference.com/w/cpp/utility/variant)
		 * as much, as possible.
		 *
		 * \tparam Ts the types that may be stored in the variant.
		 *
		 * \see [`std::aligned_storage`](https://en.cppreference.com/w/cpp/types/aligned_storage)
		 * \see [`std::variant`](https://en.cppreference.com/w/cpp/utility/variant)
		 */
		template<typename... Ts> class variant
		{
		private:
			/** \brief Visitor type to support static visiting.
			 *
			 * Used to convert static visiting interface to dynamic
			 * visiting in the implementation.
			 *
			 * \see `templated_visitor`
			 */
			class dynamic_visitor : public template_snippets::templated_visitor::unfolder<template_snippets::templated_visitor::abstract_visitor, Ts...> { };

			/** \brief Alias for `dynamic_visitor`-based visitor type.
			 *
			 * Actually creates a type of concrete visitor.
			 *
			 * \tparam RealVisitor type of concrete visitor passed
			 * to `visit()` as a parameter.
			 *
			 * \see `dynamic_visitor`
			 */
			template<class RealVisitor> using visitor_wrapper = typename template_snippets::templated_visitor::visitor_wrapper<RealVisitor, dynamic_visitor, Ts...>::type;

			/** \brief Abstract interface to value holder.
			 *
			 * Implements vtable-based generics approach. Hides
			 * actual type behind the virtual interface.
			 *
			 */
			class value_holder
			{
			public:
				/** \brief Places value at the specified address and calls copy constructor. */
				virtual void placement_copy(void*) const = 0;
				/** \brief Places value at the specified address and calls move constructor. */
				virtual void placement_move(void*) noexcept = 0;
				/** \brief Accepts a visitor. */
				virtual void accept(dynamic_visitor*) = 0;
				/** \brief Accepts a visitor (const version). */
				virtual void accept(dynamic_visitor*) const = 0;
				/** \brief Obtains [std::type_info](https://en.cppreference.com/w/cpp/types/type_info) of the actual type. */
				virtual const std::type_info& type_info() const noexcept = 0;
				/** \brief Equality check of the value stored. */
				virtual bool equals(const value_holder&) const noexcept = 0;
				virtual ~value_holder() noexcept { }
			};

			/** \brief Class template of concrete value holder.
			 *
			 * Actually holds the value of certain type (one of the
			 * alternative types specified for the `variant`).
			 *
			 * \tparam T type to store.
			 *
			 * \see `value_holder`
			 *
			 */
			template<typename T> class value_holder_template : public value_holder
			{
			public:
				/** \brief Deduction guide structure.
				 *
				 * Helps to perform argument-based overload-like deduction
				 * related to the type of the held value. Used mainly in
				 * initializations.
				 */
				struct deducer
				{
					/** \brief Deduction guiding function, without definition. */
					static T apply(T) noexcept;
				};

				value_holder_template() = default;
				value_holder_template(const value_holder_template&) = default;
				value_holder_template(value_holder_template&& v) = default;

				/** \brief Explicit conversion constructor. */
				template<typename U>
				explicit value_holder_template(U&& v) noexcept(noexcept(T(v))) : m_value(v) { }

				void placement_copy(void* dest) const noexcept(std::is_nothrow_copy_constructible<T>::value) override
				{
					new (dest) value_holder_template(*this);
				}

				void placement_move(void* dest) noexcept(std::is_nothrow_move_constructible<T>::value) override
				{
					new (dest) value_holder_template(std::move(*this));
				}

				constexpr const T& value() const& noexcept
				{
					return m_value;
				}

				constexpr T& value() & noexcept
				{
					return m_value;
				}

				constexpr T&& value() && noexcept
				{
					return m_value;
				}

				bool equals(const value_holder& rhs) const noexcept override
				{
					return m_value == static_cast<const value_holder_template&>(rhs).m_value;
				}

				void accept(dynamic_visitor* v) override
				{
					v->visit(m_value);
				}

				void accept(dynamic_visitor* v) const override
				{
					v->visit(m_value);
				}

				const std::type_info& type_info() const noexcept override
				{
					return typeid(T);
				}

			private:
				T m_value;
			};

			/** \brief Head template for recursive deducer type.
			 *
			 * Template recursion needed to inherit member functions of
			 * the same name from all the base classes in case of
			 * multiple inheritance from unfolded types (not needed since C++17).
			 *
			 */
			template<typename... As> struct common_deducer;

			template<typename A1, typename... As> struct common_deducer<A1, As...> :
				value_holder_template<A1>::deducer, common_deducer<As...>
			{
				typedef common_deducer type;

				using value_holder_template<A1>::deducer::apply;
				using common_deducer<As...>::type::apply;
			};

			template<typename A> struct common_deducer<A> : value_holder_template<A>::deducer
			{
				typedef typename value_holder_template<A>::deducer type;

				using value_holder_template<A>::deducer::apply;
			};

			template<typename T> using proper_value_holder = value_holder_template<T>;

			using data_t = std::aligned_union_t<0, proper_value_holder<std::decay_t<Ts>>...>;

		public:
			/** \brief Default constructor.
			 *
			 * Constructs an empty variant value.
			 *
			 */
			variant() noexcept : m_valid(false) { }

			/** \brief Copy constructor. */
			variant(const variant& v) : m_valid(v.m_valid)
			{
				if (v.m_valid)
					v.holder()->placement_copy(&m_data);
			}
			/** \brief Move constructor. */
			variant(variant&& v) noexcept : m_valid(v.m_valid)
			{
				if (v.m_valid)
					v.holder()->placement_move(&m_data);
			}

			/** \brief Explicit initializing constructor.
			 *
			 *  Initializes the variant with something convertible to one
			 * of its alternative types. Deduction guide is used to detect
			 * the right alternative type to hold the converted value.
			 *
			 * \tparam U type of input value. If it wouldn't appear to be
			 * convertible to any of the alternative types, compilation
			 * fails.
			 *
			 */
			template
			<
				typename U,
				typename DeducedType = decltype(common_deducer<Ts...>::apply(std::declval<U>()))
			>
			variant(U&& v) noexcept(noexcept(proper_value_holder<DeducedType>(std::forward<std::remove_reference_t<U>>(v)))) : m_valid(true)
			{
				static_type_check<U>();

				new (&m_data) proper_value_holder<DeducedType>(std::forward<std::remove_reference_t<U>>(v));
			}

			/** \brief Copy assignment */
			variant& operator=(const variant& v)
			{
				if (m_valid)
					holder()->~value_holder();

				if (v.m_valid)
					v.holder()->placement_copy(&m_data);

				m_valid = v.m_valid;

				return *this;
			}
			/** \brief Move assignment */
			variant& operator=(variant&& v) noexcept
			{
				if (m_valid)
					holder()->~value_holder();

				if (v.m_valid)
				{
					v.holder()->placement_move(&m_data);
				}

				m_valid = v.m_valid;

				return *this;
			}

			/** \brief Conversion assignment.
			 *
			 * Assigns a variant holding the value converted from the input parameter.
			 * If there's no conversion, compilation fails.
			 *
			 * \tparam U type of input value. If it wouldn't appear to be
			 * convertible to any of the alternative types, compilation
			 * fails.
			 *
			 * \param v value to convert and assign.
			 *
			 * \see `variant(U&& v)`
			 */
			template<typename U>
			variant& operator=(U&& v) noexcept(noexcept(variant(std::forward<U>(v))))
			{
				return this->operator=(variant(std::forward<U>(v)));
			}

			/** \brief Checks if the variant is valid (i.e. holds some value). */
			constexpr bool valid() const noexcept
			{
				return m_valid;
			}

			/** \brief Equality operator for variants of the same type.
			 *
			 * The rules are the following:
			 * - two invalid variants are equal
			 * - two variants with the same data stored are equal
			 * - otherwise they are not equal
			 */
			bool operator==(const variant& rhs) const noexcept
			{
				if (m_valid != rhs.m_valid)
					return false;

				if (!m_valid)
					return true;

				if (&m_data == &(rhs.m_data))
					return true;

				if (holder()->type_info() != rhs.holder()->type_info())
					return false;

				return holder()->equals(*rhs.holder());
			}

			/** \brief Inequality operator. */
			bool operator!=(const variant& rhs) const noexcept
			{
				return !operator==(rhs);
			}

			/** \brief Accepts visitor of an arbitrary type.
			 *
			 * \tparam Visitor type of the visitor object to accept.
			 *
			 * \param v visitor object to accept.
			 *
			 */
			template<class Visitor> void accept(Visitor v)
			{
				typedef visitor_wrapper<Visitor> wrapper;
				wrapper w(v);

				if (m_valid)
					holder()->accept(&w);
				else
					v();
			}
			/** \brief Accepts visitor of an arbitrary type, const version.
			 *
			 * \see `accept(Visitor v)`
			 */
			template<class Visitor> void accept(Visitor v) const
			{
				typedef visitor_wrapper<Visitor> wrapper;
				wrapper w(v);

				if (m_valid)
					holder()->accept(&w);
				else
					v();
			}

			~variant() noexcept
			{
				if (m_valid)
					holder()->~value_holder();
			}

		private:
			/** \brief Extracts a value of given type from the variant.
			 *
			 * All the necessary compile-time and run-time checks are
			 * performed. Throws
			 * [std::bad_cast](https://en.cppreference.com/w/cpp/types/bad_cast)
			 * if the variant is empty or value of another alternative type
			 * is currently held.
			 *
			 * \tparam T type, which value should be extracted.
			 *
			 * \param v variant object to query.
			 *
			 */
			template<typename T> friend T& get(variant& v)
			{
				v.template static_type_check<T>();
				v.template runtime_type_check<T>();

				return v.template holder<T>()->value();
			}

			template<typename T> friend const T& get(const variant& v)
			{
				v.template static_type_check<T>();
				v.template runtime_type_check<T>();

				return v.template holder<T>()->value();
			}

			template<typename T> friend T&& get(variant&& v)
			{
				v.template static_type_check<T>();
				v.template runtime_type_check<T>();

				return v.template holder<T>()->value();
			}

			template<typename T> friend const T&& get(const variant&& v)
			{
				v.template static_type_check<T>();
				v.template runtime_type_check<T>();

				return v.template holder<T>()->value();
			}

			/** \brief Simple trait structure to check the construction in compile time. */
			template<typename U> struct try_construct_from
			{
				template<typename F> using type = std::is_constructible<F, U>;
			};

			/** \brief Compile-time check of the type.
			 *
			 * Checks if the specified type could ever be held in this
			 * variant value. Leads to compilation failure if failed.
			 *
			 * \tparam U type to check.
			 *
			 */
			template<typename U> constexpr void static_type_check() const
			{
				static_assert(
					::template_snippets::check_any_in_pack
					<
						try_construct_from<U>::template type,
						Ts...
					>::value,
					"Type is not supported by this variant specialization");
			}

			/** \brief Runtime check of the type.
			 *
			 * Checks if value of the given type is currently held
			 * in the variant. Throws
			 * [std::bad_cast](https://en.cppreference.com/w/cpp/types/bad_cast)
			 * if failed.
			 *
			 * \tparam T type to check.
			 */
			template<typename T> void runtime_type_check() const
			{
				if (!m_valid)
					throw std::invalid_argument("Not initialized.");

				if (typeid(std::decay_t<T>) != holder()->type_info())
					throw std::bad_cast();
			}

			/** \brief Polymorphic access to storage.
			 *
			 * Helps to access
			 * [`std::aligned_storage`](https://en.cppreference.com/w/cpp/types/aligned_storage)-based
			 * as `value_holder` polymorphic object.
			 */
			constexpr const value_holder* holder() const
			{
				return safe_cast<const value_holder*>(&m_data);
			}

			inline value_holder* holder()
			{
				return safe_cast<value_holder*>(&m_data);
			}

			template<typename T,
			typename DecayedT = std::decay_t<T>>
			constexpr const proper_value_holder<DecayedT>* holder() const
			{
				return safe_cast<const proper_value_holder<DecayedT>*>(&m_data);
			}

			template<typename T,
			typename DecayedT = std::decay_t<T>>
			inline proper_value_holder<DecayedT>* holder()
			{
				return safe_cast<proper_value_holder<DecayedT>*>(&m_data);
			}

			bool m_valid;
			data_t m_data;
		};

		/** \brief Template for easy applying the visitor to variant value. */
		template
		<
			typename Visitor,
			typename Variant
		>
		void visit(Visitor&& vis, Variant&& v)
		{
			v.accept(vis);
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VARIANT_H
