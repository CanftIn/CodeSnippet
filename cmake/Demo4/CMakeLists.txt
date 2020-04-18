cmake_minimum_required(VERSION 3.0)

project(Demo4)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
option(USE_MYMATH "USE provided math implementation." ON)

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

if (USE_MYMATH)
  include_directories("${PROJECT_SOURCE_DIR}/math")
  add_subdirectory(math)
  set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

aux_source_directory(. DIR_SRCS)

add_executable(Demo4 ${DIR_SRCS})
target_link_libraries(Demo4 ${EXTRA_LIBS})