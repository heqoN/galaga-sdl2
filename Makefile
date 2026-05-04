CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
SDLFLAGS = $(shell sdl2-config --cflags --libs)

SRC = src/main.cpp
TARGET = build/game

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p build
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(SDLFLAGS)

run:
	./$(TARGET)

clean:
	rm -rf build