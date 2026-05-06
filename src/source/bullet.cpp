#include "bullet.h"

#include <SDL2/SDL.h>

Bullet::Bullet(){
    this->x=0;
    this->y=0;
    
    this->speed=8;
    this->active=false;

    this->rect.x=0;
    this->rect.y=0;
    this->rect.w=6;
    this->rect.h=14;
}

Bullet::~Bullet(){}

void Bullet::setPosition(float x,float y){
    this->x=x;
    this->y=y;

    this->rect.x=(int)x;
    this->rect.y=(int)y;
}

void Bullet::shoot(BULLET_Type type){
    active=true;

    this->type=type;
}

BULLET_Type Bullet::getType(){
    return this->type;
}

SDL_Rect Bullet::getRect(){
    return this->rect;
}

bool Bullet::isActive(){
    return this->active;
}

void Bullet::update(){
    if(!active)
        return;

    switch (this->type)
    {
        case BULLET_Type::Player:
            this->y -= this->speed;
            break;
        
        case BULLET_Type::Enemy:
            this->y += this->speed;
            break;
    }

    if(y<0)
        active=false;

    this->rect.x=(int)this->x;
    this->rect.y=(int)this->y;
}

void Bullet::render(SDL_Renderer *renderer){
    if(!active)
        return;

    switch (this->type)
    {
        case BULLET_Type::Player:
            SDL_SetRenderDrawColor(renderer,255,255,0,255);
            break;
        
        case BULLET_Type::Enemy:
            SDL_SetRenderDrawColor(renderer,255,0,0,255);
            break;
    }

    SDL_RenderFillRect(renderer,&this->rect);
}