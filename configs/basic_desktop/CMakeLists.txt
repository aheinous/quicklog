add_library(basic_desktop_config INTERFACE)

target_include_directories(basic_desktop_config INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_sources(basic_desktop_config INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/src/qkl_usr_config.c
)