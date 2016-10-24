set(PROJECT "program")

project(${PROJECT})
cmake_minimum_required(VERSION 2.8.12)

include(conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT} main.cpp)
target_link_libraries(${PROJECT} ${CONAN_LIBS})

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT})
