#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "enemySpawner.h"


using namespace std;


int main(void)
{
    Game game;

    game.run();

    return 0;
}