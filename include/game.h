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
#include "assetManager.h"
#include "UIManager.h"

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
        void resetGame();

        bool checkCollision(const SDL_Rect &a,const SDL_Rect &b);

    private:
        void handleEvents();
        void update();
        void render();

        int score;
        int wave;

        bool running;
        GameState state;

        Player player;
        vector<Enemy> enemies;
        vector<Bullet> bullets;
        EnemySpawner spawner;
        AssetManager assetManager;
        UIManager uiManager;

        SDL_Window *window;
        SDL_Renderer *renderer;
        
};


#endif