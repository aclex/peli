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
#include <typeindex>
#include <type_traits>
#include <utility>
#include <memory>
#include <cstring>

namespace peli
{
	namespace detail
	{
		namespace variant_value
		{
			namespace inline_variant
			{
				template<typename T> inline T safe_cast(void* ptr)
				{
					return static_cast<T>(ptr);
				}

				template<typename T> inline T safe_cast(const void* ptr)
				{
					return static_cast<T>(ptr);
				}

				template<typename Tp, typename... List> struct contains;

				template<typename Tp, typename Head, typename... Rest> struct contains<Tp, Head, Rest...>
					: std::conditional<std::is_same<Tp, Head>::value, std::true_type, contains<Tp, Rest...>>::type
				{

				};

				template<typename Tp> struct contains<Tp> : std::false_type { };

				template<typename T, bool is_trivial = std::is_trivial<T>::value> struct helper_operations;

				template<typename T> struct helper_operations<T, false>
				{
					template<typename... Args> inline static void create(void* dest, Args&&... args)
					{
						*safe_cast<T**>(dest) = new T(std::forward<Args>(args)...);
					}

					inline static void copy(const void* src, void* dest)
					{
						*safe_cast<T**>(dest) = new T(**safe_cast<T* const *>(src));
					}

					inline static void move(void* src, void* dest) noexcept
					{
						std::memcpy(dest, src, sizeof(T*));
					}

					inline static bool equals(const void* lhs, const void* rhs)
					{
						return **safe_cast<T* const *>(lhs) == **safe_cast<T* const *>(rhs);
					}

					template<typename U,
					typename = typename std::enable_if<!std::is_const<U>::value>::type,
					typename = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
					inline static U cast(void* data) noexcept
					{
						using decayed_u = typename std::decay<U>::type;
						return **safe_cast<decayed_u**>(data);
					}

					template<typename U,
					typename = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
					inline static U cast(const void* data) noexcept
					{
						using decayed_u = typename std::decay<U>::type;
						return **safe_cast<decayed_u* const *>(data);
					}


					template<typename Visitor> inline static void accept(const void* src, Visitor* v)
					{
						v->visit(**safe_cast<T* const *>(src));
					}

					template<typename Visitor> inline static void accept(void* src, Visitor* v)
					{
						v->visit(**safe_cast<T**>(src));
					}

					inline static void destroy(void* ptr) noexcept
					{
						delete *safe_cast<T**>(ptr);
					}
				};

				template<typename T> struct helper_operations<T, true>
				{
					template<typename... Args> inline static void create(void* dest, Args&&... args)
					{
						new (dest) T(std::forward<Args>(args)...);
					}

					inline static void copy(const void* src, void* dest) noexcept
					{
						std::memcpy(dest, src, sizeof(T));
					}

					inline static void move(const void* src, void* dest) noexcept
					{
						helper_operations::copy(src, dest);
					}

					inline static bool equals(const void* lhs, const void* rhs) noexcept
					{
						return *safe_cast<const T*>(lhs) == *safe_cast<const T*>(rhs);
					}

					template<typename U,
					typename = typename std::enable_if<!std::is_const<U>::value>::type,
					typename = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
					inline static U cast(void* data) noexcept
					{
						using decayed_u = typename std::decay<U>::type;
						return *safe_cast<decayed_u*>(data);
					}

					template<typename U,
					typename = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
					inline static U cast(const void* data) noexcept
					{
						using decayed_u = typename std::decay<U>::type;
						return *safe_cast<const decayed_u*>(data);
					}

					template<typename Visitor> inline static void accept(const void* src, Visitor* v)
					{
						v->visit(*safe_cast<const T*>(src));
					}

					template<typename Visitor> inline static void accept(void* src, Visitor* v)
					{
						v->visit(*safe_cast<T*>(src));
					}

					inline static void destroy(void*) noexcept
					{

					}
				};

				const std::type_index void_type_index(typeid(void));

				template<typename... Ts> struct variant_helper;

				template<typename F, typename... Ts> struct variant_helper<F, Ts...> : private helper_operations<F>
				{
					template<typename T, typename... Args,
					typename std::enable_if<std::is_same<T, F>::value, int>::type = 0>
					inline static void create(void* dest, Args&&... args)
					{
						helper_operations<F>::create(dest, std::forward<Args>(args)...);
					}

					template<typename T, typename... Args,
					typename std::enable_if<!std::is_same<T, F>::value, int>::type = 0>
					inline static void create(void* dest, Args&&... args)
					{
						variant_helper<Ts...>::template create<T>(dest, std::forward<Args>(args)...);
					}

					inline static void copy(const std::type_index& tag, const void* src, void* dest)
					{
						if (tag == void_type_index)
							return;

						if (tag == std::type_index(typeid(F)))
						{
							helper_operations<F>::copy(src, dest);
						}
						else
						{
							variant_helper<Ts...>::copy(tag, src, dest);
						}
					}

					inline static void move(const std::type_index& tag, void* src, void* dest) noexcept
					{
						if (tag == void_type_index)
							return;

						if (tag == std::type_index(typeid(F)))
						{
							helper_operations<F>::move(src, dest);
						}
						else
						{
							variant_helper<Ts...>::move(tag, src, dest);
						}
					}

					inline static bool equals(const std::type_index& tag, const void* lhs, const void* rhs)
					{
						if (tag == void_type_index)
							return true;

						if (tag == std::type_index(typeid(F)))
						{
							return helper_operations<F>::equals(lhs, rhs);
						}
						else
						{
							return variant_helper<Ts...>::equals(tag, lhs, rhs);
						}
					}

					template<typename Visitor> inline static void accept(const std::type_index& tag, void* src, Visitor* v)
					{
						if (tag == void_type_index)
							return;

						if (tag == std::type_index(typeid(F)))
						{
							helper_operations<F>::accept(src, v);
						}
						else
						{
							variant_helper<Ts...>::accept(tag, src, v);
						}
					}

					template<typename Visitor> inline static void accept(const std::type_index& tag, const void* src, Visitor* v)
					{
						if (tag == void_type_index)
							return;

						if (tag == std::type_index(typeid(F)))
						{
							helper_operations<F>::accept(src, v);
						}
						else
						{
							variant_helper<Ts...>::accept(tag, src, v);
						}
					}

					inline static void destroy(const std::type_index& tag, void* data)
					{
						if (tag == void_type_index)
							return;

						if (tag == std::type_index(typeid(F)))
						{
							helper_operations<F>::destroy(data);
						}
						else
						{
							variant_helper<Ts...>::destroy(tag, data);
						}
					}
				};

				template<> struct variant_helper<>
				{
					template<typename T, typename... Args> inline static void create(void* dest, Args&&... args) { }
					inline static void copy(const std::type_index& tag, const void* src, void* dest) { }
					inline static void move(const std::type_index& tag, void* src, void* dest) { }
					inline static bool equals(const std::type_index& tag, const void* lhs, const void* rhs) { }
					template<typename Visitor> inline static void accept(const std::type_index& tag, void* src, Visitor* v) { }
					template<typename Visitor> inline static void accept(const std::type_index& tag, const void* src, Visitor* v) { }
					inline static void destroy(const std::type_index& tag, void* data) { }
				};

				template<typename... Ts> class variant
				{
					template<typename T> using value_or_ptr = typename std::conditional<std::is_trivial<T>::value, T, T*>::type;

					using data_t = typename std::aligned_union<0, value_or_ptr<Ts>...>::type;
					using helper_t = variant_helper<Ts...>;

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

					variant() noexcept : m_type_index(void_type_index) { }
					variant(const variant& v) : m_type_index(v.m_type_index)
					{
						helper_t::copy(v.m_type_index, &v.m_data, &m_data);
					}

					variant(variant&& v) noexcept : m_type_index(void_type_index)
					{
						helper_t::move(v.m_type_index, &v.m_data, &m_data);
						std::swap(m_type_index, v.m_type_index);
					}

					template<typename T,
					class = typename std::enable_if<(sizeof(T) > sizeof(T*))>::type>
					explicit variant(const T& v) : m_type_index(std::type_index(typeid(T)))
					{
						static_type_check<T>();

						helper_t::template create<T>(&m_data, v);
					}

					template<typename T,
					class = typename std::enable_if<(sizeof(T) > sizeof(T*))>::type>
					explicit variant(T&& v) noexcept : m_type_index(std::type_index(typeid(T)))
					{
						static_type_check<T>();

						helper_t::template create<T>(&m_data, std::move(v));
					}

					template<typename T,
					class = typename std::enable_if<(sizeof(T) <= sizeof(T*))>::type>
					explicit variant(T v) noexcept : m_type_index(std::type_index(typeid(T)))
					{
						static_type_check<T>();

						helper_t::template create<T>(&m_data, v);
					}

					variant& operator=(const variant& v)
					{
						helper_t::destroy(m_type_index, &m_data);

						helper_t::copy(v.m_type_index, &v.m_data, &m_data);

						m_type_index = v.m_type_index;

						return *this;
					}

					variant& operator=(variant&& v) noexcept
					{
						helper_t::destroy(m_type_index, &m_data);
						m_type_index = void_type_index;

						helper_t::move(v.m_type_index, &v.m_data, &m_data);

						std::swap(m_type_index, v.m_type_index);

						return *this;
					}

					constexpr bool valid() const noexcept
					{
						return m_type_index != void_type_index;
					}

					bool operator==(const variant& rhs) const noexcept
					{
						if (m_type_index != rhs.m_type_index)
							return false;

						if (&m_data == &(rhs.m_data))
							return true;

						return helper_t::equals(m_type_index, &m_data, &rhs.m_data);
					}

					bool operator!=(const variant& rhs) const noexcept
					{
						return !operator==(rhs);
					}

					template<typename T> T cast() const
					{
						static_type_check<T>();

						if (!valid())
							throw std::invalid_argument("");

						runtime_type_check<T>();

						return helper_operations<typename std::decay<T>::type>::template cast<T>(&m_data);
					}

					template<typename T> T cast()
					{
						static_type_check<T>();

						if (!valid())
							throw std::invalid_argument("");

						runtime_type_check<T>();

						return helper_operations<typename std::decay<T>::type>::template cast<T>(&m_data);
					}

					void accept(visitor* v)
					{
						helper_t::accept(m_type_index, &m_data, v);
					}

					void accept(visitor* v) const
					{
						helper_t::accept(m_type_index, &m_data, v);
					}

					~variant() noexcept
					{
						helper_t::destroy(m_type_index, &m_data);
					}

				private:
					template<typename T> void static_type_check() const
					{
						static_assert(contains<typename std::decay<T>::type, Ts...>::value, "Type is not supported by this variant specialization");
					}

					template<typename T> void runtime_type_check() const
					{
						if (!valid())
							throw std::invalid_argument("Not initialized.");

						if (std::type_index(typeid(typename std::decay<T>::type)) != m_type_index)
							throw std::bad_cast();
					}

					std::type_index m_type_index;
					data_t m_data;
				};
			}
		}
	}
}

#endif // PELI_DETAIL_VARIANT_VALUE_INLINE_H
