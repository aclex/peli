add_subdirectory(detail)

set(PELI_JSON_SOURCES
	value.cpp
)

prefix(PELI_JSON_DETAIL_SOURCES "detail/")

add_library(peli_json OBJECT ${PELI_JSON_SOURCES} ${PELI_JSON_DETAIL_SOURCES})
