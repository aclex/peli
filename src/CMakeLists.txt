set(PELI_SOURCES
	bad_value_cast.cpp
	iomanip.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-Wall -Wextra -pedantic)

add_subdirectory(json)

add_library(peli SHARED ${PELI_SOURCES}
	$<TARGET_OBJECTS:peli_json>
)

set(CONF_INCLUDE_DIRS "${CMAKE_INSTALL_INCLUDEDIR}")
configure_file(${PROJECT_SOURCE_DIR}/cmake/peli-config.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/peli-config.cmake" @ONLY)

set_target_properties(peli PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/peli DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS peli EXPORT peli-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT peli-targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/peli)
install(FILES ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/peli-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/peli)
