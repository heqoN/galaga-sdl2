#include "player.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

Player::Player(){
    this->x=350;
    this->y=400;

    this->speed=5;
    this->texture=nullptr;

    this->rect.x=350;
    this->rect.y=400;
    this->rect.w=50;
    this->rect.h=50;
}

Player::~Player(){
    if(this->texture){
        SDL_DestroyTexture(this->texture);
        this->texture=nullptr;
    }
};

void Player::setTexture(SDL_Texture *tex){
    this->texture=tex;
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
    if(!texture) return;

    SDL_RenderCopy(renderer,this->texture,NULL,&this->rect);
}