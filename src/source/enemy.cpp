#include "enemy.h"

#define WINDOW_WIDTH 800

using namespace std;

Enemy::Enemy(){
    this->x=0.0f;
    this->y=-50.0f;
    this->homeX=0.0f;
    this->homeY=0.0f;
    this->angle=0.0f;

    this->speed=2;
    this->direction=1;
    this->texture=nullptr;
    this->alive=true;
    this->state=EnemyState::ENTERING;

    this->rect.x=0;
    this->rect.y=0;
    this->rect.w=50;
    this->rect.h=50;

    this->lastShootTime=0;
    this->fireDelay=1500;
}

Enemy::~Enemy(){}

void Enemy::setTexture(SDL_Texture *tex){
    this->texture=tex;
}

void Enemy::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    this->rect.x = (int)x;
    this->rect.y = (int)y;
}

void Enemy::setHomePosition(float x, float y) {
    this->homeX = x;
    this->homeY = y;
}

void Enemy::setAlive(){
    this->alive=true;
}

void Enemy::setDead(){
    this->alive=false;
}

bool Enemy::isAlive(){
    return this->alive;
}

float Enemy::getX(){
    return this->x;
}

float Enemy::getY(){
    return this->y;
}

void Enemy::currentToLastShootTime(Uint32 currentTime){
    this->lastShootTime=currentTime;
}

Uint32 Enemy::getLastShootTime(){
    return this->lastShootTime;
}

Uint32 Enemy::getFireDelay(){
    return this->fireDelay;
}

SDL_Rect Enemy::getRect()const{
    return rect;
}

bool Enemy::isTargetable()const{ 
    return (state == EnemyState::IN_FORMATION || state == EnemyState::DIVING || state == EnemyState::ENTERING); 
}

void Enemy::startDive() {
    if (this->state == EnemyState::IN_FORMATION) {
        this->state = EnemyState::DIVING;
        this->angle = 0.0f;
    }
}

void Enemy::update(float formationXOffset){
    if(!this->alive) return;

    float currentTargetX = this->homeX + formationXOffset;

    switch(this->state){
        case EnemyState::ENTERING:
            this->x += (currentTargetX - this->x) * 0.05f;
            this->y += (this->homeY - this->y) * 0.05f;

            if(std::abs(this->x - currentTargetX) < 1.1f && std::abs(this->y - this->homeY) < 1.1f) {
                this->state = EnemyState::IN_FORMATION;
            }
            break;

        case EnemyState::IN_FORMATION:
            this->x = currentTargetX; 
            this->y = this->homeY;
        
            this->angle += 0.05f;
            this->y += std::sin(this->angle) * 2.0f;
            break;

        case EnemyState::DIVING:
            this->y += this->speed + 2;
            this->x += std::sin(this->angle) * 4.0f;
            this->angle += 0.1f;

            if (this->y > 650) {
                this->y = -50;
                this->state = EnemyState::RETURNING;
            }
            break;

        case EnemyState::RETURNING:
            this->x += (currentTargetX - this->x) * 0.03f;
            this->y += (this->homeY - this->y) * 0.03f;

            if (std::abs(this->x - currentTargetX) < 2.0f && std::abs(this->y - this->homeY) < 2.0f) {
                this->state = EnemyState::IN_FORMATION;
            }
    }


    this->rect.x = (int)this->x;
    this->rect.y = (int)this->y;
}

void Enemy::render(SDL_Renderer *renderer){
    if(!this->texture) return;
    if(!this->alive) return;

    SDL_RenderCopy(renderer,this->texture,NULL,&this->rect);
}