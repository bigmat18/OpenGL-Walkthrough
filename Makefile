CC = g++
CFLAGS = -std=c++17 -Wall -g 
LFLAGS = -lglfw -lGLEW -framework OpenGL 

ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
LIB_DIR = $(ROOT_DIR)/libs
BUILD_DIR = $(ROOT_DIR)/build

# ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
ROOT_FILES = $(wildcard $(ROOT_DIR)/*.cpp)


# Generate object file names from source files
SRC_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
EXE_FILES := $(patsubst $(ROOT_DIR)/%.cpp, %, $(ROOT_FILES))

INCLUDE_PATHS = `pkg-config --cflags glfw3` `pkg-config --cflags glew` `pkg-config --static --libs assimp` -I$(LIB_DIR)/stb -I$(LIB_DIR)/tiny_loader
LIBRARY_PATHS = `pkg-config --static --libs glfw3` `pkg-config --static --libs glew` `pkg-config --static --libs assimp`

OBJ_NAME = main

# Default target
all: $(EXE_FILES)

# Build executable targets
$(EXE_FILES): % : $(BUILD_DIR)/%.o $(SRC_OBJ_FILES)
	$(CC) $(CFLAGS) $(LFLAGS) $(INCLUDE_PATHS) $^ -o $@

# Build object files from library source files
$(BUILD_DIR)/%.o: $(ROOT_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@
	
# Build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/* $(EXE_FILES)