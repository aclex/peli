include(NewTest)

include_directories(${CMAKE_SOURCE_DIR}/src)

new_test(value_shell_default_constructor.cpp peli)
new_test(value_shell_make_value_object.cpp peli)
new_test(value_shell_make_value_array.cpp peli)
new_test(value_shell_make_value_number.cpp peli)
new_test(value_shell_make_value_string.cpp peli)
new_test(value_shell_make_value_boolean.cpp peli)

new_test(value_istream.cpp peli)
new_test(value_ostream.cpp peli)
new_test(value_ostream_manip.cpp peli)
