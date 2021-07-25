##
# Sudoku Generator
#
# @file
# @version 0.1

# PROJ_NAME specifies the name of the project
PROJ_NAME = sudokuGenerator

# OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp src/sudokuGenerator.cpp src/sudokuExporter.cpp src/sudokuBoardFile.cpp src/sudokuImporter.cpp

# CC Specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're using
# -Wall shows all warnings
# -Iinclude sets ./include as an include path
# -g compiles with debug symbols
COMPILER_FLAGS = -Wall -Iinclude -g

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS =

# OBJ_NAME specifies the name of our executable
OBJ_NAME = $(PROJ_NAME)

# This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

# This is the target that cleans build files
clean :
	-rm sudokuGenerator sudokuBoards/*.sb

# end
