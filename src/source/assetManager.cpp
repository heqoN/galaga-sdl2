#include "assetManager.h"

#include <iostream>

AssetManager::AssetManager(){
    this->backgroundTexture=nullptr;
    this->enemyTexture=nullptr;
    this->playerTexture=nullptr;
    this->font=nullptr;
    this->backgroundMusic=nullptr;
    this->laserEffect=nullptr;
    this->explosionEffect=nullptr;
}

AssetManager::~AssetManager(){}

bool AssetManager::load(SDL_Renderer *renderer){
    this->backgroundTexture=IMG_LoadTexture(renderer,"../assets/texture/background.png");
    if(!this->backgroundTexture){
        cout<<"Background texture load failed : "<<IMG_GetError()<<endl;
        return false;
    }

    this->enemyTexture=IMG_LoadTexture(renderer,"../assets/texture/enemy.png");
    if(!this->enemyTexture){
        cout<<"Enemy texture load failed : "<<IMG_GetError()<<endl;
        return false;
    }

    this->playerTexture=IMG_LoadTexture(renderer,"../assets/texture/player.png");
    if(!this->playerTexture){
        cout<<"Player texture load failed : "<<IMG_GetError()<<endl;
        return false;
    }

    this->font=TTF_OpenFont("../assets/font/font.ttf",16);
    if(!this->font){
        cout<<"Font load failed : "<<TTF_GetError()<<endl;
        return false;
    }

    this->backgroundMusic=Mix_LoadMUS("../assets/sound/music.ogg");
    if(!this->backgroundMusic){
        cout<<"Background music load failed : "<<Mix_GetError()<<endl;
        return false;
    }

    this->laserEffect=Mix_LoadWAV("../assets/sound/laser.wav");
    if(!this->laserEffect){
        cout<<"Laser effect load failed : "<<Mix_GetError()<<endl;
        return false;
    }

    this->explosionEffect=Mix_LoadWAV("../assets/sound/explosion.wav");
    if(!this->explosionEffect){
        cout<<"Explosion effect load failed : "<<Mix_GetError()<<endl;
        return false;
    }

    return true;
}

void AssetManager::clean(){
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(enemyTexture);
    TTF_CloseFont(this->font);
    Mix_FreeMusic(this->backgroundMusic);
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

Mix_Music* AssetManager::getBackgroundMusic(){
    return this->backgroundMusic;
}

Mix_Chunk* AssetManager::getLaserEffect(){
    return this->laserEffect;
}

Mix_Chunk* AssetManager::getExplosionEffect(){
    return this->explosionEffect;
}