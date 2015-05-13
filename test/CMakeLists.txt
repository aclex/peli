include(NewTest)

include_directories(${CMAKE_SOURCE_DIR}/src)

new_test(value_shell_default_ctor.cpp peli)
new_test(value_shell_copy_ctor.cpp peli)
new_test(value_shell_move_ctor.cpp peli)
new_test(value_shell_expl_ctor_object.cpp peli)
new_test(value_shell_expl_ctor_array.cpp peli)
new_test(value_shell_expl_ctor_number.cpp peli)
new_test(value_shell_expl_ctor_boolean.cpp peli)
new_test(value_shell_expl_ctor_string.cpp peli)

new_test(value_shell_copy_assign.cpp peli)
new_test(value_shell_move_assign.cpp peli)

new_test(value_shell_make_value_object.cpp peli)
new_test(value_shell_make_value_array.cpp peli)
new_test(value_shell_make_value_number.cpp peli)
new_test(value_shell_make_value_string.cpp peli)
new_test(value_shell_make_value_boolean.cpp peli)

new_test(value_shell_cast_to_value.cpp peli)
new_test(value_shell_cast_const_to_value.cpp peli)
new_test(value_shell_cast_to_cref.cpp peli)
new_test(value_shell_cast_to_ref.cpp peli)
new_test(value_shell_cast_const_to_cref.cpp peli)
new_compilation_fail_test(value_shell_cast_const_to_ref.cpp peli)

new_test(value_shell_api_test.cpp peli)

new_test(value_istream.cpp peli)
new_test(value_ostream.cpp peli)
new_test(value_ostream_manip.cpp peli)

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
