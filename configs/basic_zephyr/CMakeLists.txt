add_library(qkl_zephyr_config INTERFACE)

target_include_directories(qkl_zephyr_config INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_sources(qkl_zephyr_config INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/src/qkl_usr_config.c
)