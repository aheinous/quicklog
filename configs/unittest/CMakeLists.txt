add_library(unittest_config INTERFACE)

target_include_directories(unittest_config INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_sources(unittest_config INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/src/qkl_assert.c
	${CMAKE_CURRENT_LIST_DIR}/src/log_out_buffer.cpp
)