cmake_minimum_required(VERSION 3.10)

add_compile_options(-Wall -Wextra -pedantic  -Werror -g)

project(mipcomp)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

link_directories(/usr/local/lib)

message([STATUS] " Compiling executable: mipcomp " ...)

add_executable(mipcomp src/main.c)

# target_include_directories(mipcomp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(mipcomp PUBLIC scip)