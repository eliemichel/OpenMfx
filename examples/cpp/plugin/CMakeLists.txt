
file(GLOB SRC *.hpp *.cpp)

add_library(plugin_cpp_examples SHARED ${SRC})
set_target_properties(plugin_cpp_examples PROPERTIES SUFFIX ".ofx")

target_link_libraries(
	plugin_cpp_examples
	PRIVATE
		OpenMfx::Sdk::Cpp::Plugin
)

target_treat_warnings_as_errors(plugin_cpp_examples)
set_property(TARGET plugin_cpp_examples PROPERTY FOLDER "OpenMfx/Examples")

