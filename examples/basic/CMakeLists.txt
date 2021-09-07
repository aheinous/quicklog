cmake_minimum_required(VERSION 3.20)

project(QuicklogExample)


add_compile_options("-fdiagnostics-color=always")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)


set(quicklog_dir "../..")

# add Quicklog
add_subdirectory(${quicklog_dir} ${CMAKE_CURRENT_BINARY_DIR}/quicklog_lib)

# add config
add_subdirectory_once(${quicklog_dir}/configs/basic_desktop ${CMAKE_CURRENT_BINARY_DIR}/quicklog_config)

# add platform implementation
add_subdirectory_once(${quicklog_dir}/platforms/pthreads ${CMAKE_CURRENT_BINARY_DIR}/quicklog_platform)



add_executable(basic_example)
target_link_libraries(basic_example PUBLIC quicklog)
target_link_libraries(basic_example PUBLIC basic_desktop_config)
target_link_libraries(basic_example PUBLIC pthreads_platform)
target_sources(basic_example PUBLIC
	./src/main.c
)

