#include "game.h"
#include "player.h"

#include <iostream>

using namespace std;

Game::Game(){
    this->running=false;
    this->window=nullptr;
    this->renderer=nullptr;
    this->background=nullptr;
}

Game::~Game(){
    if(this->background)
        SDL_DestroyTexture(this->background);

    if(this->renderer)
        SDL_DestroyRenderer(this->renderer);

    if(this->window)
        SDL_DestroyWindow(this->window);
    

    IMG_Quit();
    SDL_Quit();
}

bool Game::init(){
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        cout<<"SDL init failed : "<<SDL_GetError()<<endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout<<"IMG init failed : "<<IMG_GetError()<<endl;
        return false;
    }

    this->window=SDL_CreateWindow("GaLaGa-Clone",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800, 600,0);
    if(!this->window){
        cout<<"Window creation failed : "<<SDL_GetError()<<endl;
        return false;
    }

    this->renderer=SDL_CreateRenderer(this->window,-1,SDL_RENDERER_ACCELERATED);
    if(!this->renderer){
        cout<<"Renderer creation failed : "<<SDL_GetError()<<endl;
        return false;
    }

    this->background=IMG_LoadTexture(this->renderer,"../assets/background.png");
    if(!this->background){
        cout<<"Background load failed : "<<IMG_GetError()<<endl;
    }

    SDL_Texture *playerTexture=IMG_LoadTexture(this->renderer,"../assets/player.png");
    if(!playerTexture){
        cout<<"Player texture load failed : "<<IMG_GetError()<<endl;
        return false;
    }
    player.setTexture(playerTexture);

    SDL_Texture *enemyTexture=IMG_LoadTexture(this->renderer,"../assets/enemy.png");
    if(!enemyTexture){
        cout<<"Enemy texture load failed : "<<IMG_GetError()<<endl;
        return false;
    }
    enemy.setTexture(enemyTexture);

    // for now
    enemy.setPosition(375.0f,50.0f);

    return true;
}

void Game::run(){
    if(!init()){
        return;
    }

    this->running=true;

    while(this->running){
        this->handleEvents();
        this->update();
        this->render();

        SDL_Delay(16);
    }
}

void Game::handleEvents(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){
            running=false;
        }
    }


    const Uint8 *keystate=SDL_GetKeyboardState(nullptr);
    this->player.handleInput(keystate);
}

void Game::update(){
    this->player.update();
    this->enemy.update();
}

void Game::render(){
    SDL_SetRenderDrawColor(this->renderer,0,0,0,255);
    SDL_RenderClear(this->renderer);

    if(this->background){
        SDL_RenderCopy(this->renderer, this->background, nullptr, nullptr);
    }

    this->player.render(this->renderer);
    this->enemy.render(this->renderer);

    SDL_RenderPresent(this->renderer);
}