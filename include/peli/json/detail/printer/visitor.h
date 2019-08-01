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
					/** \brief Binds the visitor to stream. */
					visitor(std::basic_ostream<Ch>& os) : m_os(os) { }

					/** \brief Prints [JSON](https://json.org) representation of the value. */
					template<typename Arg> void operator()(Arg a)
					{
						printer::head<Arg>::print(m_os, a);
					}

					/** \brief Prints [JSON](https://json.org) representation of null entity. */
					void operator()()
					{
						printer::head<void>::print(m_os);
					}

				private:
					std::basic_ostream<Ch>& m_os;
				};
			}
		}
	}
}

#endif // PELI_JSON_DETAIL_PRINTER_VISITOR_H
