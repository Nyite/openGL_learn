cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(OpenGL_learn)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
# message(${OPENGL_LIBRARIES})

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
