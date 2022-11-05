include(check_python_requirements)

find_package(Doxygen)
if (NOT DOXYGEN_FOUND)
	message(FATAL_ERROR "Doxygen was not found but is needed to build the documentation, install it and add its location to your PATH or turn OPENMFX_BUILD_DOC to OFF")
endif()
find_package(Literate)
if (NOT LITERATE_FOUND)
	message(FATAL_ERROR "Literate (the 'lit' command) was not found but is needed to build the documentation, add its location to your PATH or turn OPENMFX_BUILD_DOC to OFF\nNB: Literate can be downloaded from https://github.com/zyedidia/Literate and a build for Windows is available at https://github.com/zyedidia/Literate/issues/49")
endif()

# Check Python packages
check_python_requirements("doc/requirements.txt")

configure_file(
	_tools/doxygen/Doxyfile.in
	${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	@ONLY
)

configure_file(
	_tools/sphinx/conf.py
	${CMAKE_CURRENT_BINARY_DIR}/conf.py
	@ONLY
)

add_custom_target(OpenMfx_Doc_Doxygen
	COMMAND ${DOXYGEN_EXECUTABLE}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating documentation API with doxygen"
)

add_custom_target(OpenMfx_Doc_Sphinx
	COMMAND
		${PYTHON_EXECUTABLE}
		-m sphinx
		-c ${CMAKE_CURRENT_BINARY_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_BINARY_DIR}/install/doc
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Generating documentation website with Sphinx"
)
