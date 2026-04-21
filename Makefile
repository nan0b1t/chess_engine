# Chess Engine

CXX = c++
CXXFLAGS = -Wall -Wextra -std=c++23

SRC := $(shell find . -maxdepth 1 -type f -name '*.cpp')

OBJ := $(SRC:.cpp=.o)

TARGET = chess_engine

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
