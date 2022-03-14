include(NewTest)

include(ApplyStrictCompileOptions)

apply_strict_compile_options_to_this_directory()

new_test(variant_default_ctor.cpp peli)
new_test(variant_copy_ctor.cpp peli)
new_test(variant_move_ctor.cpp peli)
new_test(variant_expl_ctor_object.cpp peli)
new_test(variant_expl_ctor_array.cpp peli)
new_test(variant_expl_ctor_number.cpp peli)
new_test(variant_expl_ctor_boolean.cpp peli)
new_test(variant_expl_ctor_string.cpp peli)

new_test(variant_copy_assign.cpp peli)
new_test(variant_move_assign.cpp peli)

new_test(make_value_object.cpp peli)
new_test(make_value_array.cpp peli)
new_test(make_value_number.cpp peli)
new_test(make_value_string.cpp peli)
new_test(make_value_boolean.cpp peli)

new_test(variant_cast_to_value.cpp peli)
new_test(variant_cast_const_to_value.cpp peli)
new_test(variant_cast_to_cref.cpp peli)
new_test(variant_cast_to_ref.cpp peli)
new_test(variant_cast_const_to_cref.cpp peli)
new_compilation_fail_test(variant_cast_const_to_ref.cpp peli)

new_test(value_api_test.cpp peli)

new_test(value_istream.cpp peli)
new_test(value_ostream.cpp peli)
new_test(value_ostream_manip.cpp peli)
new_test(value_char_input.cpp peli)
new_test(value_string_input.cpp peli)
new_test(value_string_output.cpp peli)

new_test(json_parser_object.cpp peli)
new_test(json_parser_array.cpp peli)
new_test(json_parser_null.cpp peli)
new_test(json_parser_string.cpp peli)
new_test(json_parser_number.cpp peli)
new_test(json_parser_boolean.cpp peli)

new_test(json_printer_object.cpp peli)
new_test(json_printer_array.cpp peli)
new_test(json_printer_null.cpp peli)
new_test(json_printer_boolean.cpp peli)
new_test(json_printer_number.cpp peli)
new_test(json_printer_string.cpp peli)

new_test(json_find.cpp peli)
