cmake_minimum_required(VERSION 3.17)


set(quicklog_dir "../..")

# add config
add_subdirectory(${quicklog_dir}/configs/unittest ${CMAKE_CURRENT_BINARY_DIR}/quicklog_config)

# add platform implementation
add_subdirectory(${quicklog_dir}/platforms/pthreads ${CMAKE_CURRENT_BINARY_DIR}/quicklog_platform)



add_executable(unittests)
target_link_libraries(unittests PUBLIC quicklog)
target_link_libraries(unittests PUBLIC unittest_config)
target_link_libraries(unittests PUBLIC pthreads_platform)

target_include_directories(unittests PUBLIC include)
target_compile_definitions(unittests PUBLIC QKL_INCLUDE_TESTS)

target_sources(unittests PUBLIC
	./src/main.cpp
	./src/tests.cpp
	./src/c_tests.c
)
