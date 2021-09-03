cmake_minimum_required(VERSION 3.17)

project(QuicklogExample)


add_compile_options("-fdiagnostics-color=always")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)


set(quicklog_dir "../..")

# add Quicklog
add_subdirectory(${quicklog_dir} ${CMAKE_CURRENT_BINARY_DIR}/quicklog_lib)

# add config
add_subdirectory(${quicklog_dir}/configs/basic_desktop ${CMAKE_CURRENT_BINARY_DIR}/quicklog_config)

# add platform implementation
add_subdirectory(${quicklog_dir}/platforms/pthreads ${CMAKE_CURRENT_BINARY_DIR}/quicklog_platform)



# # add usr platform implementation and usr configuration
# target_include_directories(quicklog INTERFACE
# 	${quicklog_dir}/platforms/pthreads/include
# )
# target_sources(quicklog INTERFACE
# 	${quicklog_dir}/platforms/pthreads/src/qkl/usr/platform.c
# 	# ${quicklog_dir}/configs/basic_desktop/config.c
# )


# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)
# target_link_libraries(quicklog INTERFACE Threads::Threads)


# SRC_DIRS := $(QKL_DIR)/configs/basic_desktop
# SRC_INC_DIRS = $(QKL_DIR)/platforms/pthreads


add_executable(speed_test)
target_link_libraries(speed_test PUBLIC quicklog)
target_sources(speed_test PUBLIC
	./src/main.c
)
