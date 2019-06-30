cmake_minimum_required(VERSION 3.0)

project (inter VERSION 1)

message(${CMAKE_SOURCE_DIR})

set(CMAKE_BUILD_TYPE Release)
set (SOURCES 
      ./main.cpp
      ./functor.cpp
      ./ast.cpp
      ./lexer.cpp
      ./parser.cpp
      ./ast_convert.cpp
      ./exception.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
