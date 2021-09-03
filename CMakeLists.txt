cmake_minimum_required(VERSION 3.17)

project(Quicklog
	VERSION 1.0
	DESCRIPTION "A logging library for realtime and timing critical applications."
	LANGUAGES C CXX)

add_library(quicklog INTERFACE)



target_include_directories(quicklog INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
target_sources(quicklog INTERFACE
	./src/decode.c
	./src/lr_buff.c
	./src/sem.c
	./src/client.c
	./src/server.c
)