set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(pthreads_platform INTERFACE)
target_link_libraries(pthreads_platform INTERFACE Threads::Threads)

target_include_directories(pthreads_platform INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_sources(pthreads_platform INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/src/qkl_usr_platform.c
)


