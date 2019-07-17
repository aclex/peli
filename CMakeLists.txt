cmake_minimum_required(VERSION 3.13)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/common/Modules/")

include(GitVersion)
include(AddUninstallTarget)
include(GNUInstallDirs)
include(GeneratePcFile)
include(VersionRoutines)
include(PrefixSuffix)

git_version(PROJECT_VERSION)

project(peli
VERSION ${PROJECT_VERSION}
DESCRIPTION "Peli JSON interaction library"
HOMEPAGE_URL "https://github.com/aclex/peli"
LANGUAGES CXX
)

set(USE_INTERNAL_VARIANT FALSE CACHE STRING "Force using the internal `variant` implementation, rather than `std::variant`, even if it's available.")

add_library(peli INTERFACE)
target_include_directories(peli INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

if ("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES AND NOT USE_INTERNAL_VARIANT)
	set(CMAKE_CXX_STANDARD 17)
	target_compile_features(peli INTERFACE cxx_std_17)
	message("Using C++17's `std::variant`")
else()
	message("Using internal `variant`")
	target_compile_features(peli INTERFACE cxx_std_14)
	target_compile_definitions("-DINTERNAL_VARIANT")
endif()

#set_target_properties(peli PROPERTIES CXX_STANDARD_REQUIRED ON)
#set_target_properties(peli PROPERTIES CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	target_compile_options(peli INTERFACE -Wall -Wextra -Wpedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	target_compile_options(peli INTERFACE -Wall -Wextra -pedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(peli INTERFACE /W4 /wd4244 /wd4805 /wd4389 /WX)
endif ()

set(CONF_INCLUDE_DIRS "${CMAKE_INSTALL_INCLUDEDIR}")
configure_file(${PROJECT_SOURCE_DIR}/cmake/peli-config.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/peli-config.cmake" @ONLY)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/peli DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS peli EXPORT peli-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT peli-targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/peli)
install(FILES ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/peli-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/peli)

if (BUILD_EXAMPLES)
	add_subdirectory(example)
endif (BUILD_EXAMPLES)

if (BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif (BUILD_TESTS)
