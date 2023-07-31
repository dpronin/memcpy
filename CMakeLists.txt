cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(memcpy VERSION 1.1.1 LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(benchmark REQUIRED)

add_executable(${PROJECT_NAME}-bench
    bench_main.cpp
    common.hpp
    libc_memcpy.hpp
    manual_memcpy_8b.hpp
    manual_memcpy_avx512_2048b.hpp
    manual_memcpy_avx512_512b.hpp
    manual_memcpy_avx512_64b.hpp
    manual_memcpy_sse_256b.hpp
)

target_link_libraries(${PROJECT_NAME}-bench PRIVATE
    benchmark::benchmark
)
