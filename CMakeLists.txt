set(PROJECT "program")

project(${PROJECT})
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB _SOURCES "*.cpp" "*.h")

add_executable(${PROJECT} ${_SOURCES})
target_link_libraries(${PROJECT} ${CONAN_LIBS})

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT})

file(COPY Assets DESTINATION bin)
