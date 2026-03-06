cmake_minimum_required(VERSION 3.16)

project(FusionANNS VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(fusionanns_core
    src/vector.cpp
    src/distance.cpp
    src/flat_index.cpp
)

target_include_directories(fusionanns_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(fusionanns src/main.cpp)
target_link_libraries(fusionanns PRIVATE fusionanns_core)

add_executable(fusionanns_basic_test tests/basic_test.cpp)
target_link_libraries(fusionanns_basic_test PRIVATE fusionanns_core)

enable_testing()
add_test(NAME basic_test COMMAND fusionanns_basic_test)
