#include "player.h"

Player::Player(){
    this->x=350;
    this->y=400;
    this->speed=5;
    this->texture=nullptr;
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

void Player::handleInput(const Uint8 *keystate){
    if (keystate[SDL_SCANCODE_W]) this->y -= this->speed;
    if (keystate[SDL_SCANCODE_S]) this->y += this->speed;
    if (keystate[SDL_SCANCODE_A]) this->x -= this->speed;
    if (keystate[SDL_SCANCODE_D]) this->x += this->speed;
}

void Player::update(){
    //------------------
}

void Player::render(SDL_Renderer *renderer){
    if(!texture) return;

    SDL_Rect dest={(int)this->x,(int)this->y,50,50};
    SDL_RenderCopy(renderer,this->texture,NULL,&dest);
}