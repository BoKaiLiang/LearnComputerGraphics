cmake_minimum_required(VERSION 3.1)

project(MATH_transformation)
project(MATH_projection)
project(MATH_fps_camera)
project(LIGHT_color)
project(LIGHT_phong)
project(BASIC_material)
project(BASIC_light_map)
project(LIGHT_caster)

FILE(GLOB ALL_CGLM_SRC "deps/ext/cglm/src/*.c")

add_definitions(-std=c99 -O3)

# Project: MATH_transform
add_executable(
    MATH_transformation
    src/MATH_transformation/MATH_transformation.c
    deps/shader.c
    deps/util.c
    deps/ext/stb/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

# Project: MATH_projection
add_executable(
    MATH_projection
    src/MATH_projection/MATH_projection.c
    deps/shader.c
    deps/util.c
    deps/ext/stb/stb_image.c
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
    deps/ext/stb/stb_image.c
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
    deps/ext/stb/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

# Project: LIGHT_phong
add_executable(
    LIGHT_phong
    src/LIGHT_phong/LIGHT_phong.c
    src/LIGHT_phong/camera.c
    deps/shader.c
    deps/util.c
    deps/ext/stb/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

# Project: BASIC_material
add_executable(
    BASIC_material
    src/BASIC_material/BASIC_material.c
    src/BASIC_material/camera.c
    deps/shader.c
    deps/util.c
    deps/ext/stb/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

# Project: BASIC_light_map
add_executable(
    BASIC_light_map
    src/BASIC_light_map/BASIC_light_map.c
    src/BASIC_light_map/camera.c
    deps/shader.c
    deps/util.c
    deps/ext/stb/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

# Project: LIGHT_caster
add_executable(
    LIGHT_caster
    src/LIGHT_caster/LIGHT_caster.c
    src/LIGHT_caster/camera.c
    deps/shader.c
    deps/util.c
    deps/ext/stb/stb_image.c
    deps/ext/glad/src/glad.c
    ${ALL_SRC}
)

add_subdirectory(deps/ext/glfw)
include_directories(deps)
include_directories(deps/ext/glfw/include)
include_directories(deps/ext/glad/include)
include_directories(deps/ext/cglm/include)
include_directories(deps/ext/stb)

if (MINGW)
    target_link_libraries(MATH_transformation glfw ${GLFW_LIBRARIES})
    target_link_libraries(MATH_projection glfw ${GLFW_LIBRARIES})
    target_link_libraries(MATH_fps_camera glfw ${GLFW_LIBRARIES})
    target_link_libraries(LIGHT_color glfw ${GLFW_LIBRARIES})
    target_link_libraries(LIGHT_phong glfw ${GLFW_LIBRARIES})
    target_link_libraries(BASIC_material glfw ${GLFW_LIBRARIES})
    target_link_libraries(BASIC_light_map glfw ${GLFW_LIBRARIES})
    target_link_libraries(LIGHT_caster glfw ${GLFW_LIBRARIES})
endif()