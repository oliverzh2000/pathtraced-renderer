cmake_minimum_required(VERSION 3.10)
project(pathtraced-flight-sim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
        third_party/
        third_party/include/
        third_party/GLFW/glfw-3.3.2/include/
        third_party/glad/include/
        third_party/glad/include/glad/
        third_party/imgui/
        third_party/imgui/backend/

        graphics/
        physics/
)

add_subdirectory(
        third_party/GLFW/glfw-3.3.2
)

link_directories(
        third_party/GLFW/build/src/RelWithDebInfo/
        third_party/imgui/
)

add_executable(
        flight-sim
        main.cpp
        graphics/main_window.cpp graphics/main_window.h
        third_party/glad/src/glad.c
        camera.h
        graphics/shader.cpp graphics/shader.h
        graphics/quad_texture_renderer.cpp
        graphics/quad_texture_renderer.h
        third_party/imgui/imgui.cpp
        third_party/imgui/imgui_demo.cpp
        third_party/imgui/imgui_draw.cpp
        third_party/imgui/imgui_tables.cpp
        third_party/imgui/imgui_widgets.cpp
        third_party/imgui/backend/imgui_impl_glfw.cpp
        third_party/imgui/backend/imgui_impl_opengl3.cpp
)

add_executable(
        imgui_demo
        third_party/imgui/example/main.cpp
        third_party/imgui/imgui.cpp
        third_party/imgui/imgui_demo.cpp
        third_party/imgui/imgui_draw.cpp
        third_party/imgui/imgui_tables.cpp
        third_party/imgui/imgui_widgets.cpp
        third_party/imgui/backend/imgui_impl_glfw.cpp
        third_party/imgui/backend/imgui_impl_opengl3.cpp
        third_party/glad/src/glad.c
)


target_link_libraries(flight-sim glfw)
target_link_libraries(imgui_demo glfw)

