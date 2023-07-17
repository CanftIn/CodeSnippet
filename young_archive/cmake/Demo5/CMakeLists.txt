cmake_minimum_required(VERSION 3.0)

project(Demo5)

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

add_executable(Demo5 ${DIR_SRCS})
target_link_libraries(Demo5 ${EXTRA_LIBS})

install(TARGETS Demo5 DESTINATION bin)
install(FILES  "${PROJECT_BINRAY_DIR}/config.h"
        DESTINATION include)

enable_testing()

add_test(test_run Demo5 5 2)
add_test(test_usage Demo5)
set_tests_properties (test_usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

macro(do_test arg1 arg2 result)
  add_test (test_${arg1}_${arg2} Demo5 ${arg1} ${arg2})
  set_tests_properties(test_${arg1}_${arg2}
  PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)

do_test (5 2 "is 25")
do_test (10 5 "is 100000")
do_test (2 10 "is 1024")
