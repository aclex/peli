#include "peli/json/detail/parser/tokenizer.h"
#include "peli/json/detail/printer/visitor.h"

namespace peli
{
	namespace json
	{
		template<typename Ch>
		inline std::basic_istream<Ch>& operator>>(std::basic_istream<Ch>& is, value& v)
		{
			v = peli::json::detail::parser::tokenizer::gentle_stream(is);
			return is;
		}

		template<typename Ch>
		inline std::basic_ostream<Ch>& operator<<(std::basic_ostream<Ch>& os, const value& v)
		{
			peli::json::detail::printer::visitor<Ch> print_visitor(os);

			peli::visit(print_visitor, v);

			return os;
		}
	}
}