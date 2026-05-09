#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <ctime>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "enemySpawner.h"
#include "assetManager.h"
#include "UIManager.h"


using namespace std;


int main(void)
{
    srand(time(NULL));

    Game game;

    game.run();

    return 0;
}