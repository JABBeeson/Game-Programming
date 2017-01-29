set(PROJECT "Pacman")

project(${PROJECT})
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT} 
	source/main.cpp
	source/headers/Globals.h
	source/headers/GameWorld.h
	source/headers/GameWorld.cpp
	source/headers/Sprite.h
	source/headers/Sprite.cpp
	source/headers/Position.h
	source/headers/Position.cpp
	source/headers/Input.h
	source/headers/Input.cpp)
target_link_libraries(${PROJECT} ${CONAN_LIBS})


set (CMAKE_CXX_STANDARD 11)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT})

file(COPY source/assets DESTINATION bin)
