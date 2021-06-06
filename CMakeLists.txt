cmake_minimum_required(VERSION 3.12)

# ---- Include guards ----

include(cmake/tools/guards.cmake)

# ---- Project ----

project(
    glTessellation
    DESCRIPTION "Real-time adaptative level of detail with tessellation shader"
    HOMEPAGE_URL "https://github.com/florianvazelle/glTessellation"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

# --- Import tools ----

include(cmake/tools/libcpp.cmake)
include(cmake/tools/sanitizer.cmake)

# ---- Conan package ----

if(CONAN_EXPORTED)
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    include(cmake/conan.cmake)
    conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP BUILD missing)
endif()

# ---- Add source files ----

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})

add_libcpp_option(TARGET ${PROJECT_NAME})
add_sanitizer_options(TARGET ${PROJECT_NAME})

# ---- Compile definitions for shaders paths ----

file(GLOB_RECURSE SHADERS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/*")

foreach(shader_path ${SHADERS_PATH})
    string(REPLACE "." "_" new_name ${shader_path})
    get_filename_component(filename ${new_name} NAME)
    string(TOUPPER ${filename} filename)
    add_compile_definitions(${filename}="${shader_path}")
endforeach()