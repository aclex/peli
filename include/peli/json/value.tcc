#include "peli/json/detail/parser/stream_buffer.h"
#include "peli/json/detail/parser/string_buffer.h"
#include "peli/json/detail/parser/tokenizer.h"
#include "peli/json/detail/printer/visitor.h"

namespace peli
{
	namespace json
	{
		template<typename Ch>
		inline std::basic_istream<Ch>& operator>>(std::basic_istream<Ch>& is, basic_value<Ch>& v)
		{
			peli::json::detail::parser::stream_buffer<Ch> buf { is };
			v = peli::json::detail::parser::tokenizer::tok(buf);

			return is;
		}

		template<typename Ch>
		inline std::basic_ostream<Ch>& operator<<(std::basic_ostream<Ch>& os, const basic_value<Ch>& v)
		{
			peli::json::detail::printer::visitor<Ch> print_visitor(os);

			peli::visit(print_visitor, v);

			return os;
		}

		template<typename Ch>
		basic_value<Ch> basic_value<Ch>::parse(const Ch* const str)
		{
			peli::json::detail::parser::char_buffer<Ch> buf { str };
			return peli::json::detail::parser::tokenizer::tok(buf);
		}

		template<typename Ch>
		basic_value<Ch> basic_value<Ch>::parse(const std::basic_string<Ch>& str)
		{
			peli::json::detail::parser::string_buffer<Ch> buf { str };
			return peli::json::detail::parser::tokenizer::tok(buf);
		}
	}
}
