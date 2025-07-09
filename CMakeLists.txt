cmake_minimum_required(VERSION 3.15)
project(raylib_dual_target C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Select build target: desktop (default) or web
if(NOT DEFINED TARGET)
    set(TARGET desktop)
endif()

# Common source
set(SRC src/main.cpp src/canvas_node.cpp src/canvas_navigator.cpp src/canvas_manager.cpp src/canvas_renderer.cpp src/data_manager.cpp)

# Header include path (shared)
include_directories(libs/raylib/include)
include_directories(libs/)

# Platform-specific settings
if(${TARGET} STREQUAL "desktop")
    message(STATUS "Configuring for Desktop build")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    link_directories(${CMAKE_SOURCE_DIR}/libs/raylib/lib_desktop)

    add_executable(app ${SRC})
    target_link_libraries(app raylib opengl32 gdi32 winmm)

elseif(${TARGET} STREQUAL "web")
    message(STATUS "Configuring for WebAssembly build")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/docs)
    link_directories(${CMAKE_SOURCE_DIR}/libs/raylib/lib_web)

    add_executable(index ${SRC})
    target_link_libraries(index raylib)
	target_compile_options(index PRIVATE -Wno-deprecated-declarations) # Warning surpression

    set_target_properties(index PROPERTIES
        #LINK_FLAGS "-s USE_GLFW=3 -s ASYNCIFY"
		#LINK_FLAGS "-s USE_GLFW=3 -s ASYNCIFY --shell-file ${CMAKE_SOURCE_DIR}/emscripten_html_template/fullscreen_template.html"
		LINK_FLAGS "-s USE_GLFW=3 -s ASYNCIFY --shell-file ${CMAKE_SOURCE_DIR}/emscripten_html_template/centered.html --preload-file ../fonts/"
        SUFFIX ".html"
    )
else()
    message(FATAL_ERROR "Unknown TARGET specified: ${TARGET}. Use -DTARGET=desktop or -DTARGET=web.")
endif()


#//Desktop Build
# cmake -B build_desktop -DTARGET=desktop
# cmake --build build_desktop

#//Web Build
# C:\Users\Michael\emsdk\emsdk_env.bat
# emcmake cmake -G "Ninja" -B build_web -DTARGET=web
# cmake --build build_web


# in root directory