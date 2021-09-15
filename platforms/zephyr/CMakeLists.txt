add_library(zephyr_platform INTERFACE)

target_include_directories(zephyr_platform INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_sources(zephyr_platform INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/src/qkl_usr_platform.c
)
