OBJS = $(wildcard *.cpp)
CC = g++
INCLUDE_PATHS = `pkg-config --cflags glfw3` `pkg-config --cflags glew`
LIBRARY_PATHS = `pkg-config --static --libs glfw3` `pkg-config --static --libs glew`
COMPILER_FLAGS = -std=c++17 -Wall -O2 -g
OBJ_NAME = main

all:
	$(CC) $(COMPILER_FLAGS) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) -o $(OBJ_NAME) ../utils/*.cpp -framework OpenGL