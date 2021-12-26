#ifndef PELI_JSON_DETAIL_PRINTER_VISITOR_H
#define PELI_JSON_DETAIL_PRINTER_VISITOR_H

#include <ostream>

#include "peli/json/detail/printer/head.h"
#include "peli/json/detail/printer/string.h"
#include "peli/json/detail/printer/boolean.h"
#include "peli/json/detail/printer/null.h"
#include "peli/json/detail/printer/number.h"
#include "peli/json/detail/printer/array.h"
#include "peli/json/detail/printer/object.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief Printing visitor.
				 *
				 * Memorizes a reference to stream and prints values
				 * while visiting them.
				 *
				 */
				template<typename Ch> class visitor
				{
				public:
					using char_type = Ch;

					/** \brief Binds the visitor to stream. */
					visitor(std::basic_ostream<Ch>& os) :
						m_os(os),
						m_tab_level(),
						m_precision(os.precision()),
						m_structure_period(),
						m_pretty(flag::get(os.iword(flag_storage_index()), flag::pretty))
					{

					}

					void push_precision(const std::size_t p) noexcept
					{
						m_precision = m_os.precision();
						m_os.precision(p);
					}

					void pop_precision() noexcept
					{
						m_os.precision(m_precision);
					}

					bool pretty() const noexcept
					{
						return m_pretty;
					}

					std::size_t tab_level() const noexcept
					{
						return m_tab_level;
					}
					
					void increase_tab_level() noexcept
					{
						++m_tab_level;
					}

					void decrease_tab_level() noexcept
					{
						--m_tab_level;
					}

					bool need_structure_period() const noexcept
					{
						return m_structure_period;
					}

					void set_need_structure_period(const bool v) noexcept
					{
						m_structure_period = v;
					}

					void putc(const Ch c)
					{
						m_os.rdbuf()->sputc(c);
					}

					std::size_t putn(const Ch* s, const std::size_t size)
					{
						return static_cast<std::size_t>(m_os.rdbuf()->sputn(s, size));
					}

					/** \brief Prints [JSON](https://json.org) representation of the value. */
					template<typename Arg> void operator()(Arg a)
					{
						printer::head<Arg>::print(*this, a);
					}

					/** \brief Prints [JSON](https://json.org) representation of null entity. */
					void operator()()
					{
						printer::head<void>::print(*this);
					}

				private:
					std::basic_ostream<Ch>& m_os;
					std::size_t m_tab_level;
					std::size_t m_precision;
					bool m_structure_period;
					const bool m_pretty;
				};
			}
		}
	}
}

#endif // PELI_JSON_DETAIL_PRINTER_VISITOR_H
