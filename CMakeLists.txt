cmake_minimum_required(VERSION 3.1)

project(MATH_transformation)
project(MATH_projection)
project(MATH_fps_camera)
project(LIGHT_color)

FILE(GLOB ALL_CGLM_SRC "deps/ext/cglm/src/*.c")

add_definitions(-std=c99 -O3)

# Project: MATH_transform
add_executable(
    MATH_transformation
    src/MATH_transformation/MATH_transformation.c
    deps/shader.c
    deps/util.c
    deps/ext/stb_image/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

# Project: MATH_projection
add_executable(
    MATH_projection
    src/MATH_projection/MATH_projection.c
    deps/shader.c
    deps/util.c
    deps/ext/stb_image/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

# Project: MATH_fps_camera
add_executable(
    MATH_fps_camera
    src/MATH_fps_camera/MATH_fps_camera.c
    src/MATH_fps_camera/camera.c
    deps/shader.c
    deps/util.c
    deps/ext/stb_image/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

# Project: LIGHT_color
add_executable(
    LIGHT_color
    src/LIGHT_color/LIGHT_color.c
    src/LIGHT_color/camera.c
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
    target_link_libraries(MATH_fps_camera glfw ${GLFW_LIBRARIES})
    target_link_libraries(LIGHT_color glfw ${GLFW_LIBRARIES})
endif()