#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "enemy.h"
#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class EnemySpawner{
    private:
        Uint32 lastSpawnTime;
        Uint32 spawnDelay;

        int currentWave;
        int enemiesPerWave;
        int spawnedEnemies;

    public:
        EnemySpawner();
        ~EnemySpawner();

        int getCurrentWave()const;

        void nextWave();
        void update(vector<Enemy> &enemies,SDL_Texture *enemyTexture);
};


#endif