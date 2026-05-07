#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "player.h"
#include "enemy.h"
#include "bullet.h"

using namespace std;


class Game{
    public:
        Game();
        ~Game();

        bool init();
        void run();

        bool checkCollision(const SDL_Rect &a,const SDL_Rect &b);

    private:
        void handleEvents();
        void update();
        void render();

        bool running;
        Player player;
        Enemy enemy;
        vector<Bullet> bullets;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *background;
        
};


#endif