cmake_minimum_required(VERSION 3.1)

project(BASIC_transformation)

FILE(GLOB ALL_CGLM_SRC "deps/ext/cglm/src/*.c")

add_definitions(-std=c99 -O3)

add_executable(
    BASIC_transformation
    src/BASIC_transformation/BASIC_transformation.c
    deps/shader.c
    deps/util.c
    deps/ext/stb_image/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

add_subdirectory(deps/ext/glfw)
include_directories(deps)
include_directories(deps/ext/glfw/include)
include_directories(deps/ext/glad/include)
include_directories(deps/ext/cglm/include)
include_directories(deps/ext/stb_image)

if (MINGW)
    target_link_libraries(BASIC_transformation glfw ${GLFW_LIBRARIES})
endif()