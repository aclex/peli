set (PELI_DETAIL_SOURCES
	type_traits.cpp
)

add_subdirectory(variant_value)

add_library(peli_detail OBJECT ${PELI_DETAIL_SOURCES})

add_subdirectory(parser)
