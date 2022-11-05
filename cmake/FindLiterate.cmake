include(FindPackageHandleStandardArgs)

# Maybe the Literate repo was cloned next to this one
set(HINT_PATHS
	"${CMAKE_SOURCE_DIR}/../Literate/bin"
)

find_program(
	LITERATE_EXECUTABLE
	NAMES lit lit.exe
	HINTS ${HINT_PATHS})
mark_as_advanced(LITERATE_EXECUTABLE)

find_package_handle_standard_args(Literate DEFAULT_MSG LITERATE_EXECUTABLE)
