#include "player.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

Player::Player(){
    this->x=350;
    this->y=400;

    this->speed=5;
    this->health=3;
    this->alive=true;
    this->texture=nullptr;

    this->rect.x=350;
    this->rect.y=400;
    this->rect.w=50;
    this->rect.h=50;

    this->lastShootTime=0;
    this->fireDelay=200;
}

Player::~Player(){
    if(this->texture){
        SDL_DestroyTexture(this->texture);
        this->texture=nullptr;
    }
};

void Player::currentToLastShootTime(Uint32 currentTime){
    this->lastShootTime=currentTime;
}

Uint32 Player::getLastShootTime(){
    return this->lastShootTime;
}

Uint32 Player::getFireDelay(){
    return this->fireDelay;
}

void Player::setTexture(SDL_Texture *tex){
    this->texture=tex;
}

void Player::takeDamage(int dmg){
    if(dmg>=this->health){
        this->alive=false;
        return;
    }

    this->health-=dmg;
}

bool Player::isAlive(){
    return this->alive;
}

SDL_Rect Player::getRect(){
    return this->rect;
}

float Player::getX(){
    return this->x;
}

float Player::getY(){
    return this->y;
}

int Player::getHealth(){
    return this->health;
}

void Player::handleInput(const Uint8 *keystate){
    if (keystate[SDL_SCANCODE_W] && this->y>0)
        this->y -= this->speed;

    if (keystate[SDL_SCANCODE_S] &&  this->y < WINDOW_HEIGHT - this->rect.h)
        this->y += this->speed;

    if (keystate[SDL_SCANCODE_A] && this->x>0)
        this->x -= this->speed;

    if (keystate[SDL_SCANCODE_D] &&  this->x < WINDOW_WIDTH - this->rect.w)
        this->x += this->speed;
}

void Player::update(){
    this->rect.x=(int)this->x;
    this->rect.y=(int)this->y;
}

void Player::render(SDL_Renderer *renderer){
    if(!this->texture) return;
    if(!this->alive) return;

    SDL_RenderCopy(renderer,this->texture,NULL,&this->rect);
}