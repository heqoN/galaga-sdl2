#include "enemySpawner.h"
#include <cstdlib>

EnemySpawner::EnemySpawner(){
    this->lastSpawnTime=0;
    this->spawnDelay=1500;

    this->currentWave=1;
    this->enemiesPerWave=5;
    this->spawnedEnemies=0;

    this->rowSize = 6;
    this->spacingX = 100.0f;
    this->spacingY = 60.0f;
    this->startX = 150.0f;
    this->startY = 50.0f;

    this->formationOffset = 0.0f;
    this->formationDirection = 1;
    this->formationSpeed = 1.0f;
}

EnemySpawner::~EnemySpawner(){}

int EnemySpawner::getCurrentWave()const{
    return this->currentWave;
}

void EnemySpawner::nextWave(){
    this->currentWave++;
    this->spawnedEnemies = 0;

    if (this->currentWave % 3 == 0) {
        this->enemiesPerWave = 1;
    } else {
        this->enemiesPerWave = 5 + (this->currentWave / 3) * 2; 
    }

    if (this->spawnDelay > 500) {
        this->spawnDelay -= 100;
    }
}

int EnemySpawner::getCurrentWave(){
    return this->currentWave;
}

float EnemySpawner::getFormationOffset(){
    return this->formationOffset;
}

void EnemySpawner::update(vector<Enemy> &enemies,SDL_Texture *enemyTexture,SDL_Texture *bossTexture){
    this->formationOffset += this->formationDirection * this->formationSpeed;

    if (std::abs(this->formationOffset) > 50.0f) {
        this->formationDirection *= -1;
    }

    Uint32 currentTime = SDL_GetTicks();
    if (this->spawnedEnemies < this->enemiesPerWave && currentTime - this->lastSpawnTime > this->spawnDelay) {
        if (enemyTexture != nullptr && bossTexture!=nullptr) {
            EnemyType spawnType = EnemyType::NORMAL;
            if (this->currentWave % 3 == 0) {
                spawnType = EnemyType::BOSS;
            }

            Enemy e(spawnType);
            if(spawnType==EnemyType::NORMAL){
                e.setTexture(enemyTexture);
            }
            else if(spawnType==EnemyType::BOSS){
                e.setTexture(bossTexture);
            }

            int col = this->spawnedEnemies % this->rowSize;
            int row = this->spawnedEnemies / this->rowSize;

            float targetX = startX + (col * spacingX);
            float targetY = startY + (row * spacingY);

            e.setPosition(targetX, -50.0f);
            e.setHomePosition(targetX, targetY);

            enemies.push_back(e);

            this->spawnedEnemies++;
            this->lastSpawnTime = currentTime;
        }
    }

    for (auto &e : enemies) {
        e.update(this->formationOffset);
    }

    if (enemies.empty() && this->spawnedEnemies >= this->enemiesPerWave) {
        this->nextWave();
    }

    if (!enemies.empty() && rand() % 500 == 0) {
        int randomIndex = rand() % enemies.size();
        enemies[randomIndex].startDive(); 
    }
}