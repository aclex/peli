include(ApplyStrictCompileOptions)

apply_strict_compile_options_to_this_directory()

add_executable(canada canada.cpp)
target_link_libraries(canada peli)

configure_file(canada.json ${CMAKE_CURRENT_BINARY_DIR}/canada.json COPYONLY)

add_executable(main main.cpp)
target_link_libraries(main peli)

configure_file(input.json ${CMAKE_CURRENT_BINARY_DIR}/input.json COPYONLY)
