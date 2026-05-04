CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SRC = src/main.cpp
TARGET = build/game

# OS detection
ifeq ($(OS),Windows_NT)
    # Windows (MinGW)
    SDL_INC = -IC:/SDL2/include -IC:/SDL2_image/include
    SDL_LIB = -LC:/SDL2/lib -LC:/SDL2_image/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

    RM = del
    MKDIR = mkdir build
    EXEC = $(TARGET).exe
else
    # Linux
    SDL_INC =
    SDL_LIB = $(shell sdl2-config --cflags --libs) -lSDL2_image

    RM = rm -rf
    MKDIR = mkdir -p build
    EXEC = $(TARGET)
endif

all:
	$(MKDIR)
	$(CXX) $(SRC) -o $(EXEC) $(CXXFLAGS) $(SDL_INC) $(SDL_LIB)

run:
	./$(EXEC)

clean:
	$(RM) build