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
    "Compile with a sanitizer. Options are: Address, Leak, Undefined, Thread"
)

