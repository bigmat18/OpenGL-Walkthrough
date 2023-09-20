CC = g++
CFLAGS = -std=c++17 -Wall -g 
LFLAGS = -lglfw -lGLEW -framework OpenGL 

SRC_DIR = .
LIB_DIR := ./libs
BUILD_DIR := ./build

# ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
LIB_FILES := $(wildcard $(LIB_DIR)/*.cpp)

# Generate object file names from source files
LIB_OBJ_FILES := $(patsubst $(LIB_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(LIB_FILES))
EXE_FILES := $(patsubst $(SRC_DIR)/%.cpp, %, $(SRC_FILES))

INCLUDE_PATHS = `pkg-config --cflags glfw3` `pkg-config --cflags glew` `pkg-config --static --libs assimp`
LIBRARY_PATHS = `pkg-config --static --libs glfw3` `pkg-config --static --libs glew` `pkg-config --static --libs assimp`

OBJ_NAME = main

# Default target
all: $(EXE_FILES)

# Build executable targets
$(EXE_FILES): % : $(BUILD_DIR)/%.o $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@

# Build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Build object files from library source files
$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/* $(EXE_FILES)