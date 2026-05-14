# Chess Engine
CXX = c++
CXXFLAGS = -Wall -Wextra -std=c++23

ifeq ($(MOLD), 1)
    CXXFLAGS += -fuse-ld=mold
endif

TARGET = chess_engine

MODE ?= release

ifeq ($(MODE), debug)
    CXXFLAGS += -g -O0 -DDEBUG
    BUILD_DIR = build/debug
else
    CXXFLAGS += -O3 -DNDEBUG
    BUILD_DIR = build/release
endif

SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

all: $(TARGET)

# Link the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile objects into their specific build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

TEST_DIR := tests
TEST_FILE ?= pawntest.fen
TEST_PATH := $(TEST_DIR)/$(TEST_FILE)
PRINT_BOARD ?=
SHOW_FAILED ?=

.PHONY: all clean test

test: $(TARGET)
	python $(TEST_DIR)/test.py $(TEST_PATH) $(PRINT_BOARD) $(SHOW_FAILED)
