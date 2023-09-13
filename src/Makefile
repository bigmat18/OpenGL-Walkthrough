CC = g++
CFLAGS = -std=c++17 -Wall -O2 -g

SRC_DIR = .
LIB_DIR := ./lib
BUILD_DIR := ./build

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
LIB_FILES := $(wildcard $(LIB_DIR)/*.cpp)

# Generate object file names from source files
LIB_OBJ_FILES := $(patsubst $(LIB_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(LIB_FILES))
EXE_FILES := $(patsubst $(SRC_DIR)/%.c, %, $(SRC_FILES))

INCLUDE_PATHS = `pkg-config --cflags glfw3` `pkg-config --cflags glew`
LIBRARY_PATHS = `pkg-config --static --libs glfw3` `pkg-config --static --libs glew`

OBJ_NAME = main

# Default target
all: $(EXE_FILES)

# Build executable targets
$(EXE_FILES): % : $(BUILD_DIR)/%.o $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $^ -o $@ -framework OpenGL

# Build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) -c $< -o $@ -framework OpenGL

# Build object files from library source files
$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) -c $< -o $@ -framework OpenGL