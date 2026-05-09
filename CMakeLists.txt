cmake_minimum_required(VERSION 3.10)
project(SimpleRenderer)

set(CMAKE_CXX_STANDARD 17)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED) # <--- TAMBAHKAN INI


find_path(GLM_INCLUDE_DIRS "glm/glm.hpp" PATHS /usr/include /usr/local/include)

add_executable(SimpleRenderer src/main.cpp)


target_include_directories(SimpleRenderer PRIVATE
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR} # <--- TAMBAHKAN INI
)


target_link_libraries(SimpleRenderer
    ${GLFW_LIBRARIES}
    GLEW::GLEW
    ${OPENGL_LIBRARIES}   # <--- TAMBAHKAN INI
)
