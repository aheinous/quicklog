
find_program(CPPCHECK cppcheck)

if(CPPCHECK)
    message("cppcheck found -----")
	set(CPPCHECK_DEFAULT_ARGS
		${CPPCHECK}  --quiet --enable=style,warning,performance,portability --force
		--std=c11
		--config-exclude=include/doctest
		# -i decode.c
		--inline-suppr
		--suppress=internalAstError
		# Include directories
		-I ${quicklog_dir}/include
	)

    set(CMAKE_C_CPPCHECK "${CPPCHECK_DEFAULT_ARGS}")
	# unset(CMAKE_C_CPPCHECK CACHE)
    # unset(CPPCHECK CACHE)

	add_custom_target(cppcheck
        COMMAND mkdir -p ${CMAKE_BINARY_DIR}/cppcheck/
		COMMAND ${CPPCHECK_DEFAULT_ARGS}
        --template=gcc
        # Source directories
        ${quicklog_dir}/src/ | tee ${CMAKE_BINARY_DIR}/cppcheck/cppcheck
        )

        add_custom_target(cppcheck-xml
        COMMAND mkdir -p ${CMAKE_BINARY_DIR}/cppcheck/
		COMMAND ${CPPCHECK_DEFAULT_ARGS}
        # enable XML output
            --xml --xml-version=2
            # Source directories
            ${quicklog_dir}/src/
            # Redirect to file
            2>${CMAKE_BINARY_DIR}/cppcheck/cppcheck.xml
	)
endif()

if(DEFINED ENV{CLANG_TIDY})
    set(CLANG_TIDY $ENV{CLANG_TIDY})
else()
    find_program(CLANG_TIDY clang-tidy)
endif()
message("clang tidy: ${CLANG_TIDY}")
if(CLANG_TIDY)
	if(BUILD_WITH_STATIC_ANALYSIS)
		set(CMAKE_C_CLANG_TIDY ${CLANG_TIDY})
	endif()

	add_custom_target(tidy
        COMMAND mkdir -p ${CMAKE_BINARY_DIR}/tidy
		COMMAND tools/clang-tidy.sh  ${CLANG_TIDY} ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/tidy/tidy
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
	)



endif()


find_program(LIZARD lizard)
if(LIZARD)

	set(LIZARD_BASE_ARGS
		${LIZARD}
		--length 75 # fail when functions longer than this
		--CCN 10 # fail over this CCN
		--arguments 10 # fail this arg count
		--exclude **/decode.c
	)

	execute_process(COMMAND find ${quicklog_dir} -type d -name src OUTPUT_VARIABLE possible_paths)
	string(REPLACE "\n" ";" possible_paths ${possible_paths})
	foreach(path IN LISTS possible_paths)
		if(NOT path MATCHES "CMakeFiles")
			list(APPEND LIZARD_PATHS ${path})
		endif()
	endforeach()


	add_custom_target(complexity-concise
		COMMAND
			${LIZARD_BASE_ARGS}
			-w # Only show warnings
			${LIZARD_PATHS}
	)

	add_custom_target(complexity-full
        COMMAND
            ${LIZARD_BASE_ARGS}
            ${LIZARD_PATHS}
	)
	add_custom_target(complexity-html
        COMMAND
            mkdir -p ${CMAKE_BINARY_DIR}/complexity
		COMMAND
			${LIZARD_BASE_ARGS}
			${LIZARD_PATHS}
			--html
			> ${CMAKE_BINARY_DIR}/complexity/complexity.html
		BYPRODUCTS
			${CMAKE_BINARY_DIR}/complexity/complexity.html
	)
	add_custom_target(complexity-xml
		COMMAND
			${LIZARD_BASE_ARGS}
			--xml # Generate XML output
			${LIZARD_PATHS}
			# Redirect output to file
			> ${CMAKE_BINARY_DIR}/complexity.xml
		BYPRODUCTS
			${CMAKE_BINARY_DIR}/complexity.xml
	)

endif()

