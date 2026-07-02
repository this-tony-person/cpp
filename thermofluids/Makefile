# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -I./components/include -I./plants/shared/include -I./plants/lox/include

# Directories
BUILD_DIR = build
SRC_DIRS = ./components/src ./plants/shared/src ./plants/lox/src ./plants/lox/tests

# Find source files
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

# Define executable name
TARGET = $(BUILD_DIR)/test_lox_plant

# Build rules
all: 
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET) -lyaml-cpp
	
# Cleanup
clean:
	rm -rf $(BUILD_DIR)/* 
	rm -f compile_commands.json
	
.PHONY: all clean
