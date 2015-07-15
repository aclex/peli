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
 * using_unfolder class is based on overloaded pattern by Dave Abrahams
 * (https://gist.github.com/3779345) distributed under the Boost
 * Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#ifndef PELI_DETAIL_VARIANT_VARIANT_H
#define PELI_DETAIL_VARIANT_VARIANT_H

#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>

#include <peli/detail/template_snippets/contains.h>
#include <peli/detail/template_snippets/templated_visitor.h>

namespace peli
{
	namespace detail
	{
		namespace variant
		{
			namespace internal
			{
				template<typename T> constexpr T safe_cast(void* ptr)
				{
					return static_cast<T>(ptr);
				}

				template<typename T> constexpr T safe_cast(const void* ptr)
				{
					return static_cast<T>(ptr);
				}
			}

			template<typename... Ts> class variant
			{
			public:
				struct visitor : template_snippets::templated_visitor::visitor<Ts...> { };

			private:
				class value_holder
				{
				public:
					virtual void placement_copy(void* dest) const = 0;
					virtual void placement_move(void* dest) noexcept = 0;
					virtual void accept(visitor* v) = 0;
					virtual void accept(visitor* v) const = 0;
					virtual const std::type_info& type_info() const noexcept = 0;
					virtual bool equals(const value_holder& rhs) const noexcept = 0;
					virtual ~value_holder() noexcept { }
				};

				template<typename T> class value_holder_template : public value_holder
				{
				public:
					value_holder_template() = default;
					value_holder_template(const value_holder_template& v) = default;

					value_holder_template(value_holder_template&& v) noexcept
					{
						using std::swap;
						swap(m_value, v.m_value);
					}

					void placement_copy(void* dest) const noexcept(std::is_nothrow_copy_constructible<value_holder_template>::value) override
					{
						new (dest) value_holder_template(*this);
					}

					void placement_move(void* dest) noexcept override
					{
						new (dest) value_holder_template(std::move(*this));
					}

					constexpr const T& value() const noexcept
					{
						return m_value;
					}

					inline T& value() noexcept // constexpr in C++14
					{
						return m_value;
					}

					bool equals(const value_holder& rhs) const noexcept override
					{
						return m_value == static_cast<const value_holder_template&>(rhs).m_value;
					}

					void accept(visitor* v) override
					{
						v->visit(m_value);
					}

					void accept(visitor* v) const override
					{
						v->visit(m_value);
					}

					const std::type_info& type_info() const noexcept override
					{
						return typeid(T);
					}

				protected:
					template<typename U,
					bool Cond = std::is_trivial<U>::value,
					typename std::enable_if<Cond, int>::type = 0>
					explicit value_holder_template(U v) noexcept : m_value(v) { }

					template<typename U,
					bool Cond = !std::is_trivial<typename std::decay<U>::type>::value,
					typename std::enable_if<Cond, int>::type = 0>
					explicit value_holder_template(const U& v) noexcept(std::is_nothrow_copy_constructible<U>::value) : m_value(v) { }

					template<typename U,
					bool Cond = !std::is_trivial<typename std::decay<U>::type>::value,
					typename std::enable_if<Cond, int>::type = 0>
					explicit value_holder_template(U&& v) noexcept
					{
						using std::swap;
						swap(this->m_value, v);
					}

				private:
					T m_value;
				};

				template<typename T> class trivial_value_holder : public value_holder_template<T>
				{
				public:
					using value_holder_template<T>::value_holder_template;
					explicit trivial_value_holder(T v) : value_holder_template<T>(v) { }
				};

				template<class T> class complex_value_holder : public value_holder_template<T>
				{
				public:
					using value_holder_template<T>::value_holder_template;
					explicit complex_value_holder(const T& v) : value_holder_template<T>(v) { }
					explicit complex_value_holder(T&& v) noexcept : value_holder_template<T>(std::move(v)) { }
				};

				template<typename T> using proper_value_holder =
					typename std::conditional<std::is_trivial<T>::value, trivial_value_holder<T>, complex_value_holder<T>>::type;

				using data_t = typename std::aligned_union<0, proper_value_holder<typename std::decay<Ts>::type>...>::type;

			public:
				variant() noexcept : m_valid(false) { }
				variant(const variant& v) : m_valid(v.m_valid)
				{
					if (v.m_valid)
						v.holder()->placement_copy(&m_data);
				}

				variant(variant&& v) noexcept : m_valid(v.m_valid)
				{
					if (v.m_valid)
						v.holder()->placement_move(&m_data);
				}

				template<typename U,
				bool Cond = std::is_trivial<U>::value,
				typename std::enable_if<Cond, int>::type = 0>
				explicit variant(U v) noexcept : m_valid(true)
				{
					static_type_check<U>();

					new (&m_data) proper_value_holder<U>(v);
				}

				template<typename U,
				typename DecayedU = typename std::decay<U>::type,
				bool Cond = !std::is_trivial<DecayedU>::value,
				typename std::enable_if<Cond, int>::type = 0>
				explicit variant(U&& v) noexcept(noexcept(proper_value_holder<DecayedU>(v))) : m_valid(true)
				{
					static_type_check<U>();

					new (&m_data) proper_value_holder<DecayedU>(std::forward<U>(v));
				}

				variant& operator=(const variant& v)
				{
					if (m_valid)
						holder()->~value_holder();

					if (v.m_valid)
						v.holder()->placement_copy(&m_data);

					m_valid = v.m_valid;

					return *this;
				}

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

				constexpr bool valid() const noexcept
				{
					return m_valid;
				}

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

				bool operator!=(const variant& rhs) const noexcept
				{
					return !operator==(rhs);
				}

				template<typename T> T cast() const
				{
					static_type_check<T>();
					runtime_type_check<T>();

					return holder<T>()->value();
				}

				template<typename T> T cast()
				{
					static_type_check<T>();
					runtime_type_check<T>();

					return holder<T>()->value();
				}

				void accept(visitor* v)
				{
					if (m_valid)
						holder()->accept(v);
				}

				void accept(visitor* v) const
				{
					if (m_valid)
						holder()->accept(v);
				}

				~variant() noexcept
				{
					if (m_valid)
						holder()->~value_holder();
				}

			private:
				template<typename T> constexpr void static_type_check() const
				{
					static_assert(template_snippets::contains<typename std::decay<T>::type, Ts...>::value,
							"Type is not supported by this variant specialization");
				}

				template<typename T> void runtime_type_check() const
				{
					if (!m_valid)
						throw std::invalid_argument("Not initialized.");

					if (typeid(typename std::decay<T>::type) != holder()->type_info())
						throw std::bad_cast();
				}

				constexpr const value_holder* holder() const
				{
					return internal::safe_cast<const value_holder*>(&m_data);
				}

				inline value_holder* holder()
				{
					return internal::safe_cast<value_holder*>(&m_data);
				}

				template<typename T,
				typename DecayedT = typename std::decay<T>::type>
				constexpr const proper_value_holder<DecayedT>* holder() const
				{
					return internal::safe_cast<const proper_value_holder<DecayedT>*>(&m_data);
				}

				template<typename T,
				typename DecayedT = typename std::decay<T>::type>
				inline proper_value_holder<DecayedT>* holder()
				{
					return internal::safe_cast<proper_value_holder<DecayedT>*>(&m_data);
				}

				bool m_valid;
				data_t m_data;
			};
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VARIANT_H