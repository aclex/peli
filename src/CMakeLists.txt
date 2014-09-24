set(PELI_SOURCES
	bad_value_cast.cpp
)

add_subdirectory(detail)

add_library(peli SHARED ${PELI_SOURCES}
	$<TARGET_OBJECTS:peli_detail>
)

set_target_properties(peli PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
install(TARGETS peli LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
