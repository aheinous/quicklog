cmake_minimum_required(VERSION 3.17)

project(QuicklogSpeedTest)


add_compile_options("-fdiagnostics-color=always")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)



if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE
			STRING "Choose the type of build."
			FORCE
	)
endif()

set(quicklog_dir "../..")

# add Quicklog
add_subdirectory(${quicklog_dir} ${CMAKE_CURRENT_BINARY_DIR}/quicklog_lib)

# add config
add_subdirectory(${quicklog_dir}/configs/basic_desktop ${CMAKE_CURRENT_BINARY_DIR}/quicklog_config)

# add platform implementation
add_subdirectory(${quicklog_dir}/platforms/pthreads ${CMAKE_CURRENT_BINARY_DIR}/quicklog_platform)



add_executable(speed_test)
target_link_libraries(speed_test PUBLIC quicklog)
target_link_libraries(speed_test PUBLIC basic_desktop_config)
target_link_libraries(speed_test PUBLIC pthreads_platform)
target_sources(speed_test PUBLIC
	./src/main.cpp
)
