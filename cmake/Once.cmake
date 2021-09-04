function(path_to_varname output_var path prefix)
    # message(">> func")
    # message("path ${path}")
    string(REPLACE "." "_" varname "${path}")
    string(REPLACE "/" "_" varname "${varname}")
    string(REPLACE "\\" "_" varname "${varname}")
    # message("varname ${varname}")
    # message("output_var, ${output_var}, ${${output_var}}")

    set(${output_var} ${prefix}${varname} PARENT_SCOPE)
    # message("output_var, ${output_var}, ${${output_var}}")
    # message("<< func")
endfunction()



macro(pragma_once)
    set(PragmaOnce_basename ${CMAKE_CURRENT_LIST_FILE})
    string(FIND ${PragmaOnce_basename} "/" PragmaOnce_last_sep REVERSE)
    math(EXPR PragmaOnce_last_sep "${PragmaOnce_last_sep} + 1")
    string(SUBSTRING ${PragmaOnce_basename} ${PragmaOnce_last_sep} "-1" PragmaOnce_basename)

    string(REPLACE "." "_" PragmaOnce_varname "${CMAKE_CURRENT_LIST_FILE}")
    string(REPLACE "/" "_" PragmaOnce_varname "${PragmaOnce_varname}")
    string(REPLACE "\\" "_" PragmaOnce_varname "${PragmaOnce_varname}")


    set(PragmaOnce_varname "${PragmaOnce_varname}_INCLUDED")
    # message("========= **PragmaOnce_varname: ${PragmaOnce_varname}")

    # message("========= include ${PragmaOnce_basename}")
    # message("========= CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
    if(${PragmaOnce_varname})
        # message("========= include ${PragmaOnce_basename} - No, already included")
        return()
    endif()

    # message("========= include ${PragmaOnce_basename} Yes")
    set(${PragmaOnce_varname} Yes)
endmacro()


macro(add_subdirectory_once source_directory binary_directory)
    # message("--------------------------------------------------")
    # message("source_directory ${source_directory}")
    # get_filename_component(source_directory "${source_directory}/" ABSOLUTE)
    set(input_path ${source_directory})
    cmake_path(ABSOLUTE_PATH input_path OUTPUT_VARIABLE abs_path)
    cmake_path(NORMAL_PATH abs_path OUTPUT_VARIABLE abs_path)
    # message("abs_path ${abs_path}")

    path_to_varname(SubdirOnce_varname ${abs_path} ${CMAKE_PROJECT_NAME}_subdirectory_added_once_)
    # message("SubdirOnce_varname ${SubdirOnce_varname}")
    # set(SubdirOnce_varname subdirectory_added_once_${SubdirOnce_varname})
    # message("SubdirOnce_varname ${SubdirOnce_varname}")


    # # get_filename_component(source_directory "${source_directory}" REALPATH)
    # message("-- add_subdirectory ${abs_path} ${SubdirOnce_varname}")
    # path_to_varname( SubdirOnce_varname ${source_directory})
    # set(SubdirOnce_varname subdir_added_once_${SubdirOnce_varname})
    # message("SubdirOnce_varname ${SubdirOnce_varname} ${${SubdirOnce_varname}}")
    if(NOT DEFINED ENV{${SubdirOnce_varname}})

        # message("-- add_subdirectory ${abs_path} YES")
        set(ENV{${SubdirOnce_varname}} TRUE)
        add_subdirectory(${source_directory} ${binary_directory})
    else()
        # message("-- add_subdirectory ${abs_path} NO")
    endif()
    # message("--------------------------------------------------")
endmacro()