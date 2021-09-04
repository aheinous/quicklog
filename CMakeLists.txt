cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(Once)
include(CMakeDependentOption)

project(Quicklog
	VERSION 1.0
	DESCRIPTION "A logging library for realtime and timing critical applications."
	LANGUAGES C CXX)


add_library(quicklog INTERFACE)


target_include_directories(quicklog INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
target_sources(quicklog INTERFACE
	./src/decode.c
	./src/lr_buff.c
	./src/sem.c
	./src/client.c
	./src/server.c
)



if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	# we are the 'root' project
	set(BUILD_QUICKLOG_TESTS_DEFAULT ON)
	add_compile_options("-fdiagnostics-color=always")
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	set(CMAKE_C_STANDARD 11)
	set(CMAKE_CXX_STANDARD 11)
else()
	# we are a subproject
	set(BUILD_QUICKLOG_TESTS_DEFAULT OFF)
endif()



cmake_dependent_option(BUILD_QUICKLOG_TESTS
	"Build quicklog tests."
	${BUILD_QUICKLOG_TESTS_DEFAULT}
	"NOT CMAKE_CROSSCOMPILING" OFF)

if(${BUILD_QUICKLOG_TESTS})
	message("including CTest")
    include(CTest)
	add_subdirectory("tests/unittests")
	add_subdirectory("tests/speed_test")

	add_test(NAME qkl-unittests COMMAND unittests)
	add_test(NAME qkl-unittests-build
		COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target unittests)
	set_tests_properties(qkl-unittests
		PROPERTIES
			DEPENDS qkl-unittests-build
	)
	add_custom_target(run-qkl-unittests
		COMMAND unittests --force-colors=1
	)
	add_custom_target(run-speed-test
		COMMAND speed_test | grep -A 5 times
	)


endif()