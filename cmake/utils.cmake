
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
	get_directory_property(target_list DIRECTORY ${ROOT_DIR} BUILDSYSTEM_TARGETS)
	list(APPEND ${OUT_VAR} ${target_list})
	get_directory_property(subdir_list DIRECTORY ${ROOT_DIR} SUBDIRECTORIES)
	foreach(subdir ${subdir_list})
		get_all_targets(${subdir} ${OUT_VAR})
	endforeach()
	set(${OUT_VAR} ${${OUT_VAR}} PARENT_SCOPE)
endfunction()

function(option_if_not_defined var doc default)
	if (NOT DEFINED ${var})
		option(${var} "${doc}" ${default})
	endif()
endfunction()
