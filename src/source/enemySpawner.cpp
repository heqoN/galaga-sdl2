#include "enemySpawner.h"
#include <cstdlib>

EnemySpawner::EnemySpawner(){
    this->lastSpawnTime=0;
    this->spawnDelay=1500;

    this->currentWave=1;
    this->enemiesPerWave=5;
    this->spawnedEnemies=0;
}

EnemySpawner::~EnemySpawner(){}

int EnemySpawner::getCurrentWave()const{
    return this->currentWave;
}

void EnemySpawner::nextWave(){
    this->currentWave++;

    this->enemiesPerWave+=2;
    this->spawnedEnemies=0;

    if(this->spawnDelay > 500){
        this->spawnDelay-=100;
    }
}

void EnemySpawner::update(vector<Enemy> &enemies,SDL_Texture *texture){
    Uint32 currentTime=SDL_GetTicks();

    if(this->spawnedEnemies < this->enemiesPerWave  &&  currentTime - this->lastSpawnTime > this->spawnDelay){
        Enemy e;
        e.setTexture(texture);

        int randomX=rand()%700+50;
        e.setPosition(randomX,50);

        enemies.push_back(e);

        this->spawnedEnemies++;
        this->lastSpawnTime=currentTime;
    }

    if(enemies.empty() && this->spawnedEnemies >= this->enemiesPerWave){
        this->nextWave();
    }
}