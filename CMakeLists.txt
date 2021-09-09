cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")
include(Once)
include(CMakeDependentOption)

project(Quicklog
	VERSION 1.0
	DESCRIPTION "A logging library for realtime and timing critical applications."
	LANGUAGES C CXX)


set(quicklog_dir ${CMAKE_CURRENT_LIST_DIR})

include (cmake/BuildOptions.cmake)

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
	add_custom_target(format
		COMMAND tools/format.sh
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	)

	add_custom_target(format-patch
		COMMAND tools/format-patch.sh
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	)
endif()

if(ENABLE_COVERAGE)
	include(CodeCoverage)
	append_coverage_compiler_flags()
endif()

add_library(quicklog INTERFACE)



if(USE_SANITIZER MATCHES "([Aa]ddress)")
	target_compile_options(quicklog INTERFACE -fsanitize=address)
	target_link_options(quicklog INTERFACE -fsanitize=address)
elseif(USE_SANITIZER MATCHES "([Tt]hread)")
	target_compile_options(quicklog INTERFACE -fsanitize=thread)
	target_link_options(quicklog INTERFACE -fsanitize=thread)
elseif(USE_SANITIZER MATCHES "([Uu]ndefined)")
	target_compile_options(quicklog INTERFACE -fsanitize=undefined)
	target_link_options(quicklog INTERFACE -fsanitize=undefined)
elseif(USE_SANITIZER MATCHES "([Ll]eak)")
	target_compile_options(quicklog INTERFACE -fsanitize=leak)
	target_link_options(quicklog INTERFACE -fsanitize=leak)
elseif(USE_SANITIZER MATCHES "([Mm]emory)")
	target_compile_options(quicklog INTERFACE -fsanitize=memory)
	target_link_options(quicklog INTERFACE -fsanitize=memory)
elseif(USE_SANITIZER MATCHES "([Aa]ddress);([Uu]ndefined)")
	target_compile_options(quicklog INTERFACE -fsanitize=address,undefined)
	target_link_options(quicklog INTERFACE -fsanitize=address,undefined)
elseif(NOT "${USE_SANITIZER}" STREQUAL "")
	message(FATAL_ERROR "Unsupported value of USE_SANITIZER: ${USE_SANITIZER}")
endif()




target_include_directories(quicklog INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
target_sources(quicklog INTERFACE
	./src/decode.c
	./src/lr_buff.c
	./src/sem.c
	./src/client.c
	./src/server.c
)





if(${BUILD_QUICKLOG_TESTS})
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

	add_custom_target(qkl-unittests-xml
        COMMAND mkdir -p ${CMAKE_BINARY_DIR}/testresults/
		COMMAND unittests --reporters=xml --out=${CMAKE_BINARY_DIR}/testresults/unittests.xml
	)

	add_custom_target(run-speed-test
		COMMAND speed_test | grep -A 5 times
	)
	add_custom_target(run-speed-test-verbose
		COMMAND speed_test
	)
endif()

if(ENABLE_COVERAGE)
	add_custom_target(coverage-xml
		# DEPENDS libc_tests printf_tests
		COMMAND ctest
		COMMAND gcovr --xml
		-r ${CMAKE_SOURCE_DIR} --object-directory=${CMAKE_BINARY_DIR}
		-o ${CMAKE_BINARY_DIR}/coverage.xml
		BYPRODUCTS ${CMAKE_BINARY_DIR}/coverage.xml
	)

	add_custom_target(coverage-html
		# DEPENDS libc_tests printf_tests
		COMMAND ctest
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
		COMMAND gcovr --html --html-details --exclude='.*doctest.*'
		-r ${CMAKE_SOURCE_DIR} --object-directory=${CMAKE_BINARY_DIR}
		-o ${CMAKE_BINARY_DIR}/coverage/index.html
	)


	# Remove coverage directory on `clean`
	set_target_properties(coverage-html PROPERTIES
		ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/coverage
	)

	add_custom_target(coverage
		DEPENDS coverage-xml coverage-html
	)
endif()


if(BUILD_WITH_STATIC_ANALYSIS)
	include(StaticAnalysis)
endif()