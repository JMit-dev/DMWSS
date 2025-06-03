cmake_minimum_required(VERSION 3.10)
project(DMWSS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
include_directories("${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(DMWSS ${SOURCE_FILES})

add_executable(DMWSS_DEBUG EXCLUDE_FROM_ALL ${SOURCE_FILES})

target_compile_options(DMWSS_DEBUG PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/Zi /Od>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g -O0>)

target_compile_definitions(DMWSS_DEBUG PRIVATE DEBUG=1)

add_custom_target(debug DEPENDS DMWSS_DEBUG)
