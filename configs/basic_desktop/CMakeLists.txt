target_include_directories(quicklog INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_sources(quicklog INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/src/qkl_usr_config.c
)