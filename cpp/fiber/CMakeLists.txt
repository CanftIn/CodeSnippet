cmake_minimum_required(VERSION 3.20)
project(
  fiber
  VERSION 0.0.1
  LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_COMPILER "clang++")
set(project_version "${${PROJECT_NAME}_VERSION}")

message(STATUS "Project '${PROJECT_NAME}', version: '${project_version}'")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # for debug of stl structure while using clang compile
  add_compile_options(-fstandalone-debug)
endif()

# CMake helpers:
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include(CTest)
enable_testing()

find_package(Boost REQUIRED)

include_directories(include)

set(FIBER_SRCS)

set(STATIC_LIB_NAME ${PROJECT_NAME})

file(GLOB_RECURSE LIB_PATH
    ./lib/*/*.cc
  )
list(APPEND FIBER_SRCS ${LIB_PATH})

add_library(${STATIC_LIB_NAME} STATIC ${FIBER_SRCS})
target_link_libraries(${STATIC_LIB_NAME})
target_include_directories(${STATIC_LIB_NAME} SYSTEM PRIVATE include)
target_include_directories(${STATIC_LIB_NAME} SYSTEM PRIVATE ${BOOST_INCLUDE_DIRS})

#add_subdirectory(unittests)