#include "assetManager.h"

#include <iostream>

AssetManager::AssetManager(){
    this->backgroundTexture=nullptr;
    this->enemyTexture=nullptr;
    this->playerTexture=nullptr;
    this->font=nullptr;
}

AssetManager::~AssetManager(){}

bool AssetManager::load(SDL_Renderer *renderer){
    this->backgroundTexture=IMG_LoadTexture(renderer,"../assets/background.png");
    if(!this->backgroundTexture){
        cout<<"Background texture load failed : "<<IMG_GetError()<<endl;
        return false;
    }

    this->enemyTexture=IMG_LoadTexture(renderer,"../assets/enemy.png");
    if(!this->enemyTexture){
        cout<<"Enemy texture load failed : "<<IMG_GetError()<<endl;
        return false;
    }

    this->playerTexture=IMG_LoadTexture(renderer,"../assets/player.png");
    if(!this->playerTexture){
        cout<<"Player texture load failed : "<<IMG_GetError()<<endl;
        return false;
    }

    this->font=TTF_OpenFont("../assets/arial.ttf",20);
    if(!this->font){
        cout<<"Font load failed : "<<TTF_GetError()<<endl;
        return false;
    }

    return true;
}

void AssetManager::clean(){
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(enemyTexture);
    TTF_CloseFont(this->font);
}

SDL_Texture* AssetManager::getBackgroundTexture(){
    return this->backgroundTexture;
}

SDL_Texture* AssetManager::getPlayerTexture(){
    return this->playerTexture;
}

SDL_Texture* AssetManager::getEnemyTexture(){
    return this->enemyTexture;
}

TTF_Font* AssetManager::getFont(){
    return this->font;
}