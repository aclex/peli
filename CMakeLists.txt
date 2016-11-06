project(peli)

cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/common/Modules/")

include(GitVersion)
include(AddUninstallTarget)
include(GNUInstallDirs)
include(GeneratePcFile)
include(VersionRoutines)
include(PrefixSuffix)

git_version(PROJECT_VERSION)
three_part_version_to_vars(${PROJECT_VERSION} PROJECT_VERSION_MAJOR PROJECT_VERSION_MINOR PROJECT_VERSION_PATCH)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR
	CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_definitions(-std=c++14)

	add_definitions(-Wall)
	add_definitions(-Wextra)
	add_definitions(-Werror)

	add_definitions(-fPIC)
endif ()

include_directories(include)

add_subdirectory(src)
add_subdirectory(example)

if (BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif (BUILD_TESTS)
