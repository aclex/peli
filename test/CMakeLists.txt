include(NewTest)

include_directories(${CMAKE_SOURCE_DIR}/src)

new_test(value_istream.cpp peli)
new_test(value_ostream.cpp peli)
new_test(value_ostream_manip.cpp peli)
