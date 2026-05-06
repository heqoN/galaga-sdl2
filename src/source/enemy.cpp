#include "enemy.h"

#define WINDOW_WIDTH 800

Enemy::Enemy(){
    this->x=0.0f;
    this->y=0.0f;

    this->speed=2;
    this->direction=1;
    this->texture=nullptr;

    this->rect.x=0;
    this->rect.y=0;
    this->rect.w=50;
    this->rect.h=50;

    this->lastShootTime=0;
    this->fireDelay=1000;
}

Enemy::~Enemy(){}

void Enemy::setTexture(SDL_Texture *tex){
    this->texture=tex;
}

void Enemy::setPosition(float x,float y){
    this->x=x;
    this->y=y;

    this->rect.x=(int)x;
    this->rect.y=(int)y;
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

void Enemy::update(){
    this->x += this->speed * this->direction;

    if (x<=0 || x+rect.w>=WINDOW_WIDTH){
        this->direction*=-1;
    }

    rect.x=static_cast<int>(x);
    rect.y=static_cast<int>(y);
}

void Enemy::render(SDL_Renderer *renderer){
    if(!this->texture) return;

    SDL_RenderCopy(renderer,this->texture,NULL,&this->rect);
}