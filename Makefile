CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SRC_DIR = src
SOURCE_DIR = $(SRC_DIR)/source

TARGET = build/game

SRCS = $(SRC_DIR)/main.cpp $(wildcard $(SOURCE_DIR)/*.cpp)

# -----------------------
# SDL (Linux)
# -----------------------
ifeq ($(OS),Windows_NT)
    SDL_INC = -IC:/SDL2/include -IC:/SDL2_image/include
    SDL_LIB = -LC:/SDL2/lib -LC:/SDL2_image/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
    RM = del /Q
    EXEC = $(TARGET).exe
else
    SDL_INC =
    SDL_LIB = $(shell sdl2-config --cflags --libs) -lSDL2_image
    RM = rm -f
    EXEC = $(TARGET)
endif

# -----------------------
# Build
# -----------------------
all:
	$(RM) $(EXEC) 2>nul || true
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC) $(SDL_INC) $(SDL_LIB)

# -----------------------
# Run
# -----------------------
run: all
	./$(EXEC)

# -----------------------
# Clean
# -----------------------
clean:
	$(RM) $(EXEC)