#include "game.h"
#include "player.h"

#include <iostream>
#include <algorithm>    //for remove_if function

using namespace std;

Game::Game(){
    this->running=false;
    this->window=nullptr;
    this->renderer=nullptr;
    this->background=nullptr;

    this->score=0;
    this->wave=1;
    this->font=nullptr;
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

    if(TTF_Init()==-1){
        cout<<"TTF init failed : "<<TTF_GetError()<<endl;
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
    this->player.setTexture(playerTexture);

    SDL_Texture *enemyTexture=IMG_LoadTexture(this->renderer,"../assets/enemy.png");
    if(!enemyTexture){
        cout<<"Enemy texture load failed : "<<IMG_GetError()<<endl;
        return false;
    }
    this->enemyTexture=enemyTexture;

    this->font=TTF_OpenFont("../assets/arial.ttf",20);
    if(!font){
        cout<<"Font load failed : "<<TTF_GetError()<<endl;
        return false;
    }

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

    Uint32 currentTime=SDL_GetTicks();
    if(keystate[SDL_SCANCODE_SPACE] &&   currentTime - this->player.getLastShootTime()  >  this->player.getFireDelay()  &&  this->player.isAlive()==true){
        Bullet b;

        b.setPosition(this->player.getX()+20,this->player.getY());
        b.shoot(BULLET_Type::Player);

        this->bullets.push_back(b);

        this->player.currentToLastShootTime(currentTime);
    }
}

void Game::update(){
    this->player.update();

    for(auto &e:this->enemies){
        e.update();
    }
    
    Uint32 currentTime=SDL_GetTicks();
    for(long unsigned int i=0 ; i<this->enemies.size() ; i++){
        if(this->enemies[i].isAlive()  &&  currentTime - this->enemies[i].getLastShootTime() > this->enemies[i].getFireDelay()){
            Bullet b;

            b.setPosition(this->enemies[i].getX()+20,this->enemies[i].getY()+20);
            b.shoot(BULLET_Type::Enemy);

            this->bullets.push_back(b);

            this->enemies[i].currentToLastShootTime(currentTime);
        }
    } 

    for(auto &b:this->bullets){
        b.update();
    }

    for(auto it=bullets.begin(); it !=bullets.end();){
        bool erased=false;

        if(it->getType()==BULLET_Type::Player){
            for(auto &e:this->enemies){
                if(this->checkCollision(it->getRect(),e.getRect())){
                    it=bullets.erase(it);
                    erased=true;

                    e.setDead();
                    this->score+=1;
                }
            }
        }

        else if(it->getType()==BULLET_Type::Enemy){
            if(this->checkCollision(it->getRect(),this->player.getRect())){
                it=bullets.erase(it);
                erased=true;

                this->player.takeDamage(1);
            }
        }

        if(!erased)
            ++it;
    }

    this->enemies.erase(
        remove_if(
            this->enemies.begin(),this->enemies.end(),
            [](Enemy &e){return !e.isAlive();}
        ),
        this->enemies.end()
    );

    this->spawner.update(enemies,enemyTexture);
    this->wave=this->spawner.getCurrentWave();
    
}

void Game::render(){
    SDL_SetRenderDrawColor(this->renderer,0,0,0,255);
    SDL_RenderClear(this->renderer);

    if(this->background){
        SDL_RenderCopy(this->renderer, this->background, nullptr, nullptr);
    }

    this->player.render(this->renderer);
    
    for(auto &e:this->enemies){
        e.render(this->renderer);
    }

    for(auto &b:this->bullets){
        b.render(this->renderer);
    }

    this->renderText("Score : "+to_string(this->score),20,20);
    this->renderText("Wave : "+to_string(this->wave),20,50);
    if(this->player.isAlive()){
        this->renderText("Lives : "+to_string(this->player.getHealth()),20,80);
    }
    else{
        this->renderText("Lives : 0",20,80);
    }


    SDL_RenderPresent(this->renderer);
}

bool Game::checkCollision(const SDL_Rect &a,const SDL_Rect &b){
    return SDL_HasIntersection(&a,&b);
}

void Game::renderText(const string &text,int x,int y){
    SDL_Color color={255,255,255,255};
    SDL_Surface *surface=TTF_RenderText_Solid(this->font,text.c_str(),color);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(this->renderer,surface);
    SDL_Rect rect={x,y,surface->w,surface->h};

    SDL_RenderCopy(this->renderer,texture,NULL,&rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}