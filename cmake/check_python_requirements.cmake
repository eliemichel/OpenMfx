# Check Python packages
# PYTHON_REQUIREMENTS_TXT must be relative to the project's root
# NB: This does not check versions
macro (check_python_requirements PYTHON_REQUIREMENTS_TXT)
	find_package(Python)
	if (NOT PYTHON_FOUND)
		message(FATAL_ERROR "Python was not found but is needed to build the documentation, install it or turn OPENMFX_BUILD_DOC to OFF")
	endif()

	# Load requirements.txt
	file(STRINGS "${PROJECT_SOURCE_DIR}/${PYTHON_REQUIREMENTS_TXT}" requirements)
	set(packages "")
	foreach(line ${requirements})
		string(REGEX MATCH "^[^<>=]*" p ${line})
		string(TOLOWER ${p} p)
		list(APPEND packages ${p})
	endforeach()
	message(STATUS "Checking python packages ${packages}")

	# Call pip show
	execute_process(
		COMMAND ${PYTHON_EXECUTABLE} -m pip show ${packages}
		RESULT_VARIABLE status
		OUTPUT_VARIABLE output
	)
	message(STATUS "status = ${status}")
	string(REPLACE "\n" ";" output ${output})
	set(found_packages "")
	foreach (line ${output})
		string(REGEX MATCH "^Name: " match ${line})
		if (match)
			string(REGEX REPLACE "^Name: (.*)$" "\\1" p ${line})
			string(TOLOWER ${p} p)
			list(APPEND found_packages ${p})
		endif()
	endforeach()

	# Compare lists
	list(SORT found_packages)
	list(SORT packages)
	foreach(p IN ZIP_LISTS packages found_packages)
		if (NOT p_0 STREQUAL p_1)
			message(FATAL_ERROR "Python package '${p_0}' was not found; to install Python dependencies run\n    python -m pip install -r ${PYTHON_REQUIREMENTS_TXT}")
		endif()
	endforeach()
endmacro()
