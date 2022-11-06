
# A simple utility function to treat warnings as errors
function(target_treat_warnings_as_errors target)
	if(MSVC)
		target_compile_options(${target} PRIVATE /W4 /WX)
	else()
		target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic -Werror)
	endif()
endfunction()

# List all targets defined in the project
function(get_all_targets ROOT_DIR OUT_VAR)
	cmake_parse_arguments(ARG "NO_INTERFACE" "" "" ${ARGN})
	get_directory_property(target_list DIRECTORY ${ROOT_DIR} BUILDSYSTEM_TARGETS)

	# Filter
	foreach (target ${target_list})
		if (DEFINED ARG_NO_INTERFACE)
			get_target_property(type ${target} TYPE)
			if (${type} STREQUAL "INTERFACE_LIBRARY")
				continue()
			endif()
		endif()
		list(APPEND ${OUT_VAR} ${target})
	endforeach()

	# Recurse
	get_directory_property(subdir_list DIRECTORY ${ROOT_DIR} SUBDIRECTORIES)
	foreach(subdir ${subdir_list})
		get_all_targets(${subdir} ${OUT_VAR})
	endforeach()

	# Set in parent scope
	set(${OUT_VAR} ${${OUT_VAR}} PARENT_SCOPE)
endfunction()

function(option_if_not_defined var doc default default_if_main_project)
	if (NOT DEFINED ${var})
		if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
			set(value ${default_if_main_project})
		else()
			set(value ${default})
		endif()
		option(${var} "${doc}" ${value})
	endif()
endfunction()
