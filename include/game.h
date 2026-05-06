#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.h"
#include "enemy.h"


class Game{
    public:
        Game();
        ~Game();

        bool init();
        void run();

    private:
        void handleEvents();
        void update();
        void render();

        bool running;
        Player player;
        Enemy enemy;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *background;
        
};


#endif