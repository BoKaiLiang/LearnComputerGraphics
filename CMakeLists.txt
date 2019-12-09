cmake_minimum_required(VERSION 3.1)

project(MATH_transformation)
project(MATH_projection)

FILE(GLOB ALL_CGLM_SRC "deps/ext/cglm/src/*.c")

add_definitions(-std=c99 -O3)

add_executable(
    MATH_transformation
    src/MATH_transformation/MATH_transformation.c
    deps/shader.c
    deps/util.c
    deps/ext/stb_image/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

add_executable(
    MATH_projection
    src/MATH_projection/MATH_projection.c
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
    target_link_libraries(MATH_transformation glfw ${GLFW_LIBRARIES})
    target_link_libraries(MATH_projection glfw ${GLFW_LIBRARIES})
endif()