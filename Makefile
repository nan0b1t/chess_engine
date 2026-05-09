# Chess Engine
CXX = c++
CXXFLAGS = -Wall -Wextra -std=c++23
CXXFLAGS += -fuse-ld=mold # faster linker
TARGET = chess_engine

MODE ?= release

ifeq ($(MODE), debug)
    CXXFLAGS += -g -O0 -DDEBUG
    BUILD_DIR = build/debug
else
    CXXFLAGS += -O3 -DNDEBUG
    BUILD_DIR = build/release
endif

SRC := $(shell find . -maxdepth 1 -type f -name '*.cpp')
OBJ := $(SRC:%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET)

# Link the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile objects into their specific build directory
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: all cleann
