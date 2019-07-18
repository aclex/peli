cmake_minimum_required(VERSION 3.13)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/common/Modules/")

include(GitVersion)

git_version(PROJECT_VERSION)

project(peli
	VERSION ${PROJECT_VERSION}
	DESCRIPTION "Peli JSON interaction library"
	HOMEPAGE_URL "https://github.com/aclex/peli"
	LANGUAGES CXX
)

include(GNUInstallDirs)
include(AddUninstallTarget)

set(USE_INTERNAL_VARIANT FALSE CACHE STRING "Force using the internal `variant` implementation, rather than `std::variant`, even if it's available.")

add_library(peli INTERFACE)
target_include_directories(peli INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

if ("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES AND NOT USE_INTERNAL_VARIANT)
	target_compile_features(peli INTERFACE cxx_std_17)
	message("Using C++17's `std::variant`")

else()
	message("Using internal `variant`")
	target_compile_features(peli INTERFACE cxx_std_14)
	target_compile_definitions(peli INTERFACE INTERNAL_VARIANT)

endif()

include(CMakePackageConfigHelpers)
set(CONFIG_PACKAGE_INSTALL_DIR lib/cmake/${PROJECT_NAME})

write_basic_package_version_file(
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
	)

install(TARGETS peli
	EXPORT peli-targets
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_package_config_file(
	${PROJECT_SOURCE_DIR}/cmake/config.cmake.in
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
	INSTALL_DESTINATION ${CONFIG_PACKAGE_INSTALL_DIR}
	PATH_VARS CMAKE_INSTALL_FULL_INCLUDEDIR
	)

install(EXPORT ${PROJECT_NAME}-targets DESTINATION ${CONFIG_PACKAGE_INSTALL_DIR})
install(FILES
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
	DESTINATION ${CONFIG_PACKAGE_INSTALL_DIR}
	)

install(DIRECTORY
	${PROJECT_SOURCE_DIR}/include/peli
	${PROJECT_SOURCE_DIR}/dep/floaxie/include/floaxie
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_uninstall_target()


if (BUILD_EXAMPLES)
	add_subdirectory(example)
endif (BUILD_EXAMPLES)

if (CALC_COVERAGE AND (CMAKE_BUILD_TYPE STREQUAL "Debug") AND CMAKE_COMPILER_IS_GNUCXX)
	set(COVERAGE_ENABLED TRUE)
endif()

if (BUILD_TESTS)
	if (COVERAGE_ENABLED)
		message("Will calculate code coverage.")
		target_compile_options(floaxie INTERFACE --coverage)
		target_link_options(floaxie INTERFACE --coverage)
	endif()

	enable_testing()
	add_subdirectory(test)

endif (BUILD_TESTS)
