# =========================
# Compiler
# =========================
CXX := g++

CXXFLAGS := -std=c++17 -Wall -Wextra

# =========================
# SDL2 (Linux / MSYS2 uyumlu)
# =========================
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS := $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf

# =========================
# Project structure
# =========================
SRC_DIR := src
SOURCE_DIR := src/source
BUILD_DIR := build
INC_DIR := include
ASSETS_DIR := assets

# =========================
# Sources
# =========================
SRCS := $(wildcard $(SRC_DIR)/*.cpp) \
        $(wildcard $(SOURCE_DIR)/*.cpp)

OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

TARGET := $(BUILD_DIR)/galaga

# =========================
# Include
# =========================
INCLUDES := -I$(INC_DIR)

# =========================
# Default target
# =========================
all: prepare $(TARGET) copy_assets

# =========================
# Build executable
# =========================
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(SDL_LIBS)

# =========================
# Compile objects
# =========================
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SDL_CFLAGS) -c $< -o $@

# =========================
# Create build directory
# =========================
prepare:
	@mkdir -p $(BUILD_DIR)

# =========================
# Copy assets to build
# =========================
copy_assets:
	@cp -r $(ASSETS_DIR) $(BUILD_DIR)/

# =========================
# Run
# =========================
run: all
	./$(TARGET)

# =========================
# Clean
# =========================
clean:
	rm -rf $(BUILD_DIR)