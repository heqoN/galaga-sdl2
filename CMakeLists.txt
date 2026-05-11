cmake_minimum_required(VERSION 3.10)
project(Galaga-SDL2 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(include)

file(GLOB SOURCES 
    "src/main.cpp"
    "src/source/*.cpp"
)


add_executable(galaga ${SOURCES})


target_link_libraries(galaga 
    SDL2::SDL2 
    SDL2_image::SDL2_image 
    SDL2_ttf::SDL2_ttf 
    SDL2_mixer::SDL2_mixer
)

add_custom_command(TARGET galaga POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "Assets klasoru build dizinine kopyalaniyor..."
)