#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "enemySpawner.h"

using namespace std;

enum GameState{
    MENU,
    PLAYING,
    GAME_OVER
};

class Game{
    public:
        Game();
        ~Game();

        bool init();
        void run();
        void renderText(const string &text,int x,int y);
        void resetGame();
        void renderMenu();
        void renderGameOverMenu();

        bool checkCollision(const SDL_Rect &a,const SDL_Rect &b);

    private:
        void handleEvents();
        void update();
        void render();

        int score;
        int wave;
        TTF_Font *font;

        bool running;
        GameState state;

        Player player;
        vector<Enemy> enemies;
        vector<Bullet> bullets;
        EnemySpawner spawner;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *background;
        SDL_Texture *enemyTexture;
        
};


#endif