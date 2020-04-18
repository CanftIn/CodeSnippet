cmake_minimum_required(VERSION 3.0)

project(curl)

add_executable(${PROJECT_NAME} main.c)
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

if(CURL_FOUND)
  include_directories(${CURL_INCLUDE_DIR})
  target_link_libraries(curl ${CURL_LIBRARY})
else(CURL_FOUND)
  message(FATAL_ERROR "CURL library not found")
endif(CURL_FOUND)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)