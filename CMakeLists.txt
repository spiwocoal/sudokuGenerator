cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(openSudoku
  VERSION 1.0
  DESCRIPTION ""
  LANGUAGES CXX
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(openSudoku-lib
  include/sudokuBoard.hpp
  include/sudokuBoardFile.hpp
  include/sudokuExporter.hpp
  include/sudokuGenerator.hpp
  include/sudokuImporter.hpp
  src/sudoku/sudokuBoard.cpp
  src/sudoku/sudokuBoardFile.cpp
  src/sudoku/sudokuExporter.cpp
  src/sudoku/sudokuGenerator.cpp
  src/sudoku/sudokuImporter.cpp
)

target_include_directories(
  openSudoku-lib
  PUBLIC
    "include"
)

add_executable(openSudoku-server
  include/ipc_common.hpp
  include/server.hpp
  src/server/server.cpp
  src/server/main.cpp
)

add_executable(openSudoku-client
  include/ipc_common.hpp
  src/client/main.cpp
)

if(MSVC)
  # MSVC compiler options would go here
  #
  # If only I knew what those were
else()
  target_compile_options(openSudoku-client PRIVATE -Wall -Wextra -Wpedantic -Wpedantic -Weffc++ -g -fdiagnostics-color=always)
  target_compile_options(openSudoku-server PRIVATE -Wall -Wextra -Wpedantic -Wpedantic -Weffc++ -g -fdiagnostics-color=always)
  target_compile_options(openSudoku-lib PRIVATE -Wall -Wextra -Wpedantic -Wpedantic -Weffc++ -g -fdiagnostics-color=always)
endif()

target_link_libraries(openSudoku-client openSudoku-lib CONAN_PKG::boost Threads::Threads)
target_link_libraries(openSudoku-server openSudoku-lib CONAN_PKG::boost Threads::Threads)
