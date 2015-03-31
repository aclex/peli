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

#ifndef PELI_DETAIL_VARIANT_VALUE_INLINE_H
#define PELI_DETAIL_VARIANT_VALUE_INLINE_H

#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			namespace inline_variant
			{
				template<typename Tp, typename... List> struct contains;

				template<typename Tp, typename Head, typename... Rest> struct contains<Tp, Head, Rest...>
					: std::conditional<std::is_same<Tp, Head>::value, std::true_type, contains<Tp, Rest...>>::type
				{

				};

				template<typename Tp> struct contains<Tp> : std::false_type { };

				template<typename... Ts> struct variant_helper;

				template<typename T> T safe_cast(void* ptr)
				{
					return static_cast<T>(ptr);
				}

				template<typename T> T safe_cast(const void* ptr)
				{
					return static_cast<T>(ptr);
				}

				template<typename... Ts> class variant
				{
				public:
					template<typename Arg> struct object_argument_visitor
					{
						virtual void visit(const Arg& arg) { }
					};

					template<typename Arg> struct value_argument_visitor
					{
						virtual void visit(Arg arg) { }
					};

					template<typename Arg> using argument_visitor =
							typename std::conditional<std::is_fundamental<Arg>::value,
								value_argument_visitor<Arg>, object_argument_visitor<Arg>>::type;

					template<typename... As> struct using_unfolder;

					template<typename A1, typename... As> struct using_unfolder<A1, As...> : argument_visitor<A1>, using_unfolder<As...>
					{
							typedef using_unfolder type;

							using argument_visitor<A1>::visit;
							using using_unfolder<As...>::type::visit;
					};

					template<typename A> struct using_unfolder<A> : argument_visitor<A>
					{
							typedef using_unfolder type;

							using argument_visitor<A>::visit;
					};

					struct visitor : using_unfolder<Ts...> { };

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

					template<typename T> struct swap_constructible_kernel
					{
						swap_constructible_kernel() = default;
						swap_constructible_kernel(swap_constructible_kernel&& v) noexcept
						{
							using std::swap;
							swap(m_value, v.m_value);
						}

						explicit swap_constructible_kernel(const T& v) : m_value(v) { }

						explicit swap_constructible_kernel(T&& v) noexcept
						{
							using std::swap;
							swap(m_value, v);
						}

					protected:
						T m_value;
					};

					template<typename T> struct move_constructible_kernel
					{
						move_constructible_kernel() = default;
						move_constructible_kernel(move_constructible_kernel&& v) noexcept : m_value(std::move(v.m_value)) { }
						explicit move_constructible_kernel(const T& v) : m_value(v) { }
						explicit move_constructible_kernel(T&& v) noexcept : m_value(std::move(v)) { }

					protected:
						T m_value;
					};

					template<typename T> using value_holder_template_kernel =
						typename std::conditional<noexcept(T(std::declval<T>())), move_constructible_kernel<T>, swap_constructible_kernel<T>>::type;

					template<typename T> class value_holder_template : public value_holder, public value_holder_template_kernel<T>
					{
					public:
						value_holder_template() = default;
// 						value_holder_template(const value_holder_template& v) : m_value(v.m_value) { }
						value_holder_template(const value_holder_template& v) : value_holder_template_kernel<T>(v.m_value) { }
// 						using value_holder_template_kernel<T>::value_holder_template_kernel;
// 						template<class = typename std::enable_if<!noexcept(T(std::move(T())))>::type>
// 						value_holder_template(value_holder_template&& v) noexcept
// 						{
// 							using std::swap;
// 							swap(this->m_value, v.m_value);
// 						}

// 						value_holder_template(value_holder_template&& v) noexcept : value_holder_template_kernel<T>(std::move(v)) { }
						value_holder_template(value_holder_template&& v) = default;

// 						template<class = typename std::enable_if<noexcept(T(std::move(T())))>::type>
// 						value_holder_template(value_holder_template&& v) noexcept : m_value(std::move(v.m_value)) { }

// 						explicit value_holder_template(const T& v) : m_value(v) { }
						explicit value_holder_template(const T& v) : value_holder_template_kernel<T>(v) { }
// 						explicit value_holder_template(T&& v) noexcept
// 						{
// 							using std::swap;
// 							swap(this->m_value, v);
// 						}

						explicit value_holder_template(T&& v) noexcept : value_holder_template_kernel<T>(std::move(v)) { }

						template<typename U,
						typename = typename std::enable_if<!std::is_const<U>::value>::type,
						typename = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
						U variant_as() noexcept
						{
							return this->m_value;
						}

						template<typename U,
						typename = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
						U variant_as() const noexcept
						{
							return this->m_value;
						}

						bool equals(const value_holder& rhs) const noexcept override
						{
							return this->m_value == static_cast<const value_holder_template&>(rhs).m_value;
						}

						void placement_copy(void* dest) const override
						{
							new (dest) value_holder_template(*this);
						}

						void placement_move(void* dest) noexcept override
						{
							new (dest) value_holder_template(std::move(*this));
						}

						void accept(visitor* v) override
						{
							v->visit(this->m_value);
						}

						void accept(visitor* v) const override
						{
							v->visit(this->m_value);
						}

						const std::type_info& type_info() const noexcept override
						{
							return typeid(T);
						}

// 					private:
// 						T m_value;
					};

					using data_t = typename std::aligned_union<0, value_holder_template<typename std::decay<Ts>::type>...>::type;

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

					template<typename T,
					class = typename std::enable_if<(sizeof(T) > sizeof(T*))>::type>
					explicit variant(const T& v)
					{
						static_type_check<T>();

						new (&m_data) value_holder_template<typename std::decay<T>::type>(v);
						m_valid = true;
					}

					template<typename T,
					class = typename std::enable_if<(sizeof(T) > sizeof(T*))>::type>
					explicit variant(T&& v) noexcept
					{
						static_type_check<T>();

						new (&m_data) value_holder_template<typename std::decay<T>::type>(std::move(v));
						m_valid = true;
					}

					template<typename T,
					class = typename std::enable_if<(sizeof(T) <= sizeof(T*))>::type>
					explicit variant(T v) noexcept
					{
						static_type_check<T>();

						new (&m_data) value_holder_template<typename std::decay<T>::type>(std::move(v));
						m_valid = true;
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

					template<typename T, typename... Args> void emplace(Args&&... args)
					{
						static_type_check<T>();

						if (m_valid)
							holder()->~value_holder();

						new (&m_data) value_holder_template<typename std::decay<T>::type>(std::forward<Args>(args)...);
						m_valid = true;
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

						if (!m_valid)
							throw std::invalid_argument("");

						return call_cast<T>();
					}

					template<typename T> T cast()
					{
						static_type_check<T>();

						if (!m_valid)
							throw std::invalid_argument("");

						return call_cast<T>();
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
					template<typename T> void static_type_check() const
					{
						static_assert(contains<typename std::decay<T>::type, Ts...>::value, "Type is not supported by this variant specialization");
					}

					template<typename T> void runtime_type_check() const
					{
						if (!m_valid)
							throw std::invalid_argument("Not initialized.");

						if (typeid(typename std::decay<T>::type) != holder()->type_info())
							throw std::bad_cast();
					}

					template<typename T> T call_cast() const
					{
						runtime_type_check<T>();
						return holder<T>()->template variant_as<T>();
					}

					template<typename T> T call_cast()
					{
						runtime_type_check<T>();

						return holder<T>()->template variant_as<T>();
					}

					const value_holder* holder() const
					{
						return safe_cast<const value_holder*>(&m_data);
					}

					value_holder* holder()
					{
						return safe_cast<value_holder*>(&m_data);
					}

					template<typename T,
					typename DecayedT = typename std::decay<T>::type>
					const value_holder_template<DecayedT>* holder() const
					{
						return safe_cast<const value_holder_template<DecayedT>*>(&m_data);
					}

					template<typename T,
					typename DecayedT = typename std::decay<T>::type>
					value_holder_template<DecayedT>* holder()
					{
						return safe_cast<value_holder_template<DecayedT>*>(&m_data);
					}

					bool m_valid;
					data_t m_data;
				};
			}
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_INLINE_H
