# CMakeList.txt: проект CMake для Socket_server; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.

add_executable (server "Socket_server.cpp" "Socket_server.h" "../res/server.rc")

add_executable (server_refactor "Server.h" "Server.cpp" "Socket.h" "Socket.cpp" "../res/server.rc")

add_executable (client_refactor "Client.h" "Client.cpp" "Socket.h" "Socket.cpp" "../res/client.rc")

add_executable (client "Socket_client.cpp" "Socket_client.h" "../res/client.rc")


if(WIN32)
	target_link_libraries(server wsock32 ws2_32)
	target_link_libraries(server_refactor wsock32 ws2_32)
	target_link_libraries(client_refactor wsock32 ws2_32)
	target_link_libraries(client wsock32 ws2_32)
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET server PROPERTY CXX_STANDARD 20)
	set_property(TARGET client PROPERTY CXX_STANDARD 20)
	set_property(TARGET server_refactor PROPERTY CXX_STANDARD 20)
	set_property(TARGET client_refactor PROPERTY CXX_STANDARD 20)
endif()


# TODO: Добавьте тесты и целевые объекты, если это необходимо.
