project(peli)

cmake_minimum_required(VERSION 3.3)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/common/Modules/")

include(GitVersion)
include(AddUninstallTarget)
include(GNUInstallDirs)
include(GeneratePcFile)
include(VersionRoutines)
include(PrefixSuffix)

git_version(PROJECT_VERSION)
three_part_version_to_vars(${PROJECT_VERSION} PROJECT_VERSION_MAJOR PROJECT_VERSION_MINOR PROJECT_VERSION_PATCH)

set(USE_INTERNAL_VARIANT FALSE CACHE STRING "Force using the internal `variant` implementation, rather than `std::variant`, even if it's available.")

if ("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES AND NOT USE_INTERNAL_VARIANT)
	set(CMAKE_CXX_STANDARD 17)
	message("Using C++17's `std::variant`")
else()
	message("Using internal `variant`")
	set(CMAKE_CXX_STANDARD 14)
	add_definitions("-DINTERNAL_VARIANT")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	add_definitions(-Wall)
	add_definitions(-Wextra)
	add_definitions(-Wpedantic)
	add_definitions(-Werror)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_definitions(-Wall)
	add_definitions(-Wextra)
	add_definitions(-pedantic)
	add_definitions(-Werror)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	add_definitions("/W4 /wd4244 /wd4805 /wd4389 /WX")
endif ()

include_directories(include)

add_subdirectory(src)
add_subdirectory(example)

if (BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif (BUILD_TESTS)
