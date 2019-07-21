cmake_minimum_required (VERSION 2.6)
project (tinyrenderer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin)

add_executable(tinyrenderer ${CMAKE_CURRENT_LIST_DIR}/main.cpp ${CMAKE_CURRENT_LIST_DIR}/../lib/geometry.cpp ${CMAKE_CURRENT_LIST_DIR}/../lib/model.cpp ${CMAKE_CURRENT_LIST_DIR}/../lib/tgaimage.cpp)
include_directories(tinyrenderer ${CMAKE_CURRENT_LIST_DIR}/../lib)
