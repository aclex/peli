set(PELI_JSON_SOURCES
	value.cpp
	parser.cpp
	printer.cpp
)

add_library(peli_json OBJECT ${PELI_JSON_SOURCES})
