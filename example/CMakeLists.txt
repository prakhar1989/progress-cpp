cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(progresscppExample
        LANGUAGES CXX
        )

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
        NAME progresscpp
        SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(progresscppExample ${sources})

set_target_properties(progresscppExample PROPERTIES
        CXX_STANDARD 11
        OUTPUT_NAME "Progress-cpp Example"
        )

target_link_libraries(progresscppExample progresscpp)