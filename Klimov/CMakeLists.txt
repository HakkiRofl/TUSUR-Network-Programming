add_executable (Klimov "Klimov.cpp"  "Klimov.h")


if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET Klimov PROPERTY CXX_STANDARD 20)
endif()