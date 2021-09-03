set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(quicklog INTERFACE Threads::Threads)

target_include_directories(quicklog INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_sources(quicklog INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/src/qkl_usr_platform.c
)


