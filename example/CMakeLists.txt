include(ApplyStrictCompileOptions)

apply_strict_compile_options_to_this_directory()

add_executable(canada canada.cpp)
target_link_libraries(canada peli)

configure_file(canada.json ${CMAKE_CURRENT_BINARY_DIR}/canada.json COPYONLY)
