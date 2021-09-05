if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	# we are the 'root' project
	set(BUILD_QUICKLOG_TESTS_DEFAULT ON)
	set(ENABLE_COVERAGE_DEFAULT ON)
	set(BUILD_WITH_STATIC_ANALYSIS_DEFAULT ON)
	add_compile_options("-fdiagnostics-color=always")
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	set(CMAKE_C_STANDARD 11)
	set(CMAKE_CXX_STANDARD 11)

	else()
	# we are a subproject
	set(BUILD_QUICKLOG_TESTS_DEFAULT OFF)
	set(ENABLE_COVERAGE_DEFAULT OFF)
	set(BUILD_WITH_STATIC_ANALYSIS_DEFAULT OFF)
endif()



cmake_dependent_option(BUILD_QUICKLOG_TESTS
	"Build quicklog tests."
	${BUILD_QUICKLOG_TESTS_DEFAULT}
	"NOT CMAKE_CROSSCOMPILING" OFF
)
cmake_dependent_option(ENABLE_COVERAGE
	"Enable code coverage analysis."
	"${ENABLE_COVERAGE_DEFAULT}"
	"\"${CMAKE_BUILD_TYPE}\" STREQUAL \"Debug\" AND NOT CMAKE_CROSSCOMPILING" OFF
)

option(BUILD_WITH_STATIC_ANALYSIS
	"Enable static analysis output when building the project."
	${BUILD_WITH_STATIC_ANALYSIS_DEFAULT}
)


set(USE_SANITIZER
    "" CACHE STRING
    "Compile with a sanitizer. Options are: Address, Memory, Leak, Undefined, Thread, 'Address;Undefined'"
)

if(USE_SANITIZER MATCHES "([Aa]ddress)")
	add_compile_options(-fsanitize=address)
	add_link_options(-fsanitize=address)
elseif(USE_SANITIZER MATCHES "([Tt]hread)")
	add_compile_options(-fsanitize=thread)
	add_link_options(-fsanitize=thread)
elseif(USE_SANITIZER MATCHES "([Uu]ndefined)")
	add_compile_options(-fsanitize=undefined)
	add_link_options(-fsanitize=undefined)
elseif(USE_SANITIZER MATCHES "([Ll]eak)")
	add_compile_options(-fsanitize=leak)
	add_link_options(-fsanitize=leak)
elseif(USE_SANITIZER MATCHES "([Mm]emory)")
	add_compile_options(-fsanitize=memory)
	add_link_options(-fsanitize=memory)
elseif(USE_SANITIZER MATCHES "([Aa]ddress);([Uu]ndefined)")
	add_compile_options(-fsanitize=address,undefined)
	add_link_options(-fsanitize=address,undefined)
elseif(NOT "${USE_SANITIZER}" STREQUAL "")
	message(FATAL_ERROR "Unsupported value of USE_SANITIZER: ${USE_SANITIZER}")
endif()