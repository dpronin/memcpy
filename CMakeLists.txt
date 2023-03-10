cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(memcpy VERSION 1.0.0 LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(benchmark REQUIRED)

add_executable(${PROJECT_NAME}-bench
    bench_main.cpp
    common.hpp
    libc_memcpy.cpp
    manual_memcpy_8b.cpp
    manual_memcpy_avx512_64b.cpp
    manual_memcpy_avx512_512b.cpp
    manual_memcpy_avx512_2048b.cpp
    manual_memcpy_sse_256b.cpp
)

target_link_libraries(${PROJECT_NAME}-bench PRIVATE
    benchmark::benchmark
)
