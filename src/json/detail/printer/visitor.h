#ifndef PELI_JSON_DETAIL_PRINTER_VISITOR_H
#define PELI_JSON_DETAIL_PRINTER_VISITOR_H

#include <ostream>

#include "json/detail/printer/head.h"
#include "json/detail/printer/string.h"
#include "json/detail/printer/boolean.h"
#include "json/detail/printer/null.h"
#include "json/detail/printer/number.h"
#include "json/detail/printer/array.h"
#include "json/detail/printer/object.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				template<typename Ch> class visitor
				{
				public:
					visitor(std::basic_ostream<Ch>& os) : m_os(os) { }
					template<typename Arg> void visit(Arg a)
					{
						printer::head<Arg>::print(m_os, a);
					}

					void visit()
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
