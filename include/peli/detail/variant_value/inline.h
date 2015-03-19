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
 */

#ifndef PELI_DETAIL_VARIANT_VALUE_INLINE_H
#define PELI_DETAIL_VARIANT_VALUE_INLINE_H

#include <typeinfo>
#include <type_traits>
#include <memory>

#include <peli/detail/variant_value/value_holder.h>
#include <peli/detail/variant_value/value_holder_template.h>

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
					using data_t = typename std::aligned_union<0, value_holder_template<Ts>...>::type;

				public:
					variant() : m_valid(false) { }
					variant(const variant& v) : m_valid(v.m_valid)
					{
						v.holder()->placement_copy(holder());
					}

					variant(variant&& v) noexcept
					{
						using std::swap;
						swap(m_valid, v.m_valid);
						v.holder()->placement_move(holder());
					}

					template<typename T,
					class = typename std::enable_if<(sizeof(T) > sizeof(T*))>::type>
					explicit variant(const T& v)
					{
						static_type_check<T>();

						new (&m_data) T(v);
						m_valid = true;
					}

					template<typename T,
					class = typename std::enable_if<(sizeof(T) <= sizeof(T*))>::type>
					explicit variant(T v)
					{
						static_type_check<T>();

						new (&m_data) T(std::move(v));
						m_valid = true;
					}

					variant& operator=(variant v)
					{
						using std::swap;
						swap(m_data, v.m_data);
						swap(m_valid, v.m_valid);

						return *this;
					}

					template<typename T, typename... Args> void emplace(Args&&... args)
					{
						static_type_check<T>();

						if (m_valid)
							holder()->~value_holder();

						new (&m_data) T(std::forward<Args>(args)...);
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

						return call_cast<T>();
					}

					template<typename T> T cast()
					{
						static_type_check<T>();

						return call_cast<T>();
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
						if (!valid())
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
