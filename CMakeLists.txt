cmake_minimum_required(VERSION 3.14)
project(pathtraced-renderer VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
        third_party/
        third_party/GLFW/glfw-3.3.2/include/
        third_party/glad/include/
        third_party/glad/include/glad/
        third_party/imgui/
        third_party/imgui/backend/
        third_party/stb/include/
        third_party/catch2/

        src/graphics/
        src/core/
        src/physics/
)

add_subdirectory(third_party/GLFW/glfw-3.3.2)

add_executable(
        renderer
        main.cpp
        src/graphics/main_window.cpp
        third_party/glad/src/glad.c
)

add_executable(
        test
        test/tests_main.cpp
        test/quadratic_solver_test.cpp
        test/vector_test.cpp
        test/bound_test.cpp
)

add_executable(
        imgui_demo
        third_party/imgui/example/main.cpp
        third_party/glad/src/glad.c
)

add_library(
        imgui_lib
        third_party/imgui/imgui.cpp
        third_party/imgui/imgui_demo.cpp
        third_party/imgui/imgui_draw.cpp
        third_party/imgui/imgui_tables.cpp
        third_party/imgui/imgui_widgets.cpp
        third_party/imgui/backend/imgui_impl_glfw.cpp
        third_party/imgui/backend/imgui_impl_opengl3.cpp
)

add_library(
        renderer_lib
        src/core/geometry.cpp
        src/core/ray.cpp
        src/graphics/shader.cpp
        src/graphics/quad_renderer.cpp
        src/graphics/sphere.cpp
        src/graphics/render_primitive_group.cpp
        src/graphics/camera.cpp
        src/graphics/stb_image.cpp
        src/graphics/lambertian.cpp
        src/graphics/metal.cpp
        src/graphics/light_interaction.cpp
        src/graphics/texture.cpp
        src/graphics/cube_map.cpp
        src/graphics/equirectangular_map.cpp
        src/graphics/triangle.cpp
        src/core/matrix.cpp
        src/core/quadratic_solver.h
        src/core/bound.cpp
        src/core/bound.h
)

find_package(OpenMP)
target_link_libraries(renderer glfw imgui_lib OpenMP::OpenMP_CXX renderer_lib)
target_link_libraries(test renderer_lib)
target_link_libraries(imgui_demo glfw imgui_lib)
