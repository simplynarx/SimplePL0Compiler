cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(SimplePL0Compiler)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
  src/main.cpp
  src/lexer.cpp
  src/parser.cpp
  src/transpiler.cpp
)

add_executable(SimplePL0Compiler ${SOURCES})
