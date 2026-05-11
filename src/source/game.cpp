#include "game.h"
#include "player.h"

#include <iostream>
#include <algorithm>    //for remove_if function

using namespace std;

Game::Game(){
    this->running=false;
    this->state=MENU;
    this->window=nullptr;
    this->renderer=nullptr;

    this->score=0;
    this->wave=1;
}

Game::~Game(){
    this->assetManager.clean();

    if(this->renderer)
        SDL_DestroyRenderer(this->renderer);

    if(this->window)
        SDL_DestroyWindow(this->window);

    Mix_CloseAudio();

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
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

    if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024) < 0) {
        cout<<"Mixer init failed : "<<Mix_GetError()<<endl;
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

    if(!this->assetManager.load(this->renderer)){
        return false;
    }

    this->player.setTexture(this->assetManager.getPlayerTexture());

    Mix_PlayMusic(this->assetManager.getBackgroundMusic(),-1);

    return true;
}

void Game::run(){
    if(!init()){
        return;
    }

    this->running=true;

    while(this->running){
        this->handleEvents();

        if(this->state==PLAYING){
            this->update();
        }

        this->render();

        SDL_Delay(16);
    }
}

void Game::handleEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT || event.key.keysym.sym==SDLK_ESCAPE){
            running=false;
        }

        switch(this->state){
            case MENU:
                if(event.type==SDL_KEYDOWN){
                    if(event.key.keysym.sym==SDLK_RETURN){
                        this->resetGame();
                    }

                    if(event.key.keysym.sym==SDLK_l){
                        this->state=LEADERBOARD;
                    }
                }
                break;

            case GAME_OVER:
                if(event.type==SDL_KEYDOWN){
                    if(event.key.keysym.sym==SDLK_r){   
                        this->resetGame();
                    }

                    if(event.key.keysym.sym==SDLK_BACKSPACE){
                        this->state=MENU;
                    }
                }
                break;

            case PLAYING:
                break;
            
            case LEADERBOARD:
                if(event.type==SDL_KEYDOWN){
                    if(event.key.keysym.sym==SDLK_BACKSPACE){
                        this->state=MENU;
                    }
                }
        }; 
                
    }

    if(this->state==PLAYING){
        const Uint8 *keystate=SDL_GetKeyboardState(nullptr);
        this->player.handleInput(keystate);

        Uint32 currentTime=SDL_GetTicks();
        if(keystate[SDL_SCANCODE_SPACE] &&   currentTime - this->player.getLastShootTime()  >  this->player.getFireDelay()  &&  this->player.isAlive()==true){
            Bullet b;

            b.setPosition(this->player.getX()+20,this->player.getY());
            b.shoot(BULLET_Type::Player);

            Mix_PlayChannel(-1,this->assetManager.getLaserEffect(),0);

            this->bullets.push_back(b);

            this->player.currentToLastShootTime(currentTime);
        }
    }
}

void Game::update(){
    this->player.update();

    for(auto &e:this->enemies){
        e.update(this->spawner.getFormationOffset());
    }
    
    Uint32 currentTime=SDL_GetTicks();
    for(long unsigned int i=0 ; i < this->enemies.size() ; i++){
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
                if(e.getY()>0 && e.isTargetable() && e.isAlive()){
                    if(this->checkCollision(it->getRect(),e.getRect())){
                        it=bullets.erase(it);
                        erased=true;

                        e.setDead();
                        this->score+=1;
                        Mix_PlayChannel(-1,this->assetManager.getExplosionEffect(),0);
                        break;
                    }
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

    if(!this->player.isAlive()){
        this->state=GAME_OVER;
        this->leaderboard.saveScore(this->score);
    }

    this->enemies.erase(
        remove_if(
            this->enemies.begin(),this->enemies.end(),
            [](Enemy &e){return !e.isAlive();}
        ),
        this->enemies.end()
    );

    this->bullets.erase(
        remove_if(this->bullets.begin(), this->bullets.end(),
        [](const Bullet& b) { return !b.isActive(); }), 
        this->bullets.end() 
    );

    this->spawner.update(enemies,this->assetManager.getEnemyTexture());
    this->wave=this->spawner.getCurrentWave();
    
}

void Game::render(){
    SDL_SetRenderDrawColor(this->renderer,0,0,0,255);
    SDL_RenderClear(this->renderer);

    switch(this->state){
        case MENU:
            this->uiManager.renderMenu(this->renderer,this->assetManager.getFont());
            break;
        
        case LEADERBOARD:
            this->uiManager.renderLeaderboard(this->renderer,this->assetManager.getFont(),this->leaderboard.getScores());
            break;

        case PLAYING:
            if(this->assetManager.getBackgroundTexture()){
                SDL_RenderCopy(this->renderer,this->assetManager.getBackgroundTexture(),nullptr,nullptr);
            }
            this->player.render(this->renderer);
            
            for(auto &e:enemies){
                e.render(this->renderer);
            }

            for(auto &b:bullets){
                b.render(this->renderer);
            }

            this->uiManager.renderHud(this->renderer,this->assetManager.getFont(),this->player.isAlive(),this->score,this->wave,this->player.getHealth());
            break;

        case GAME_OVER:
            this->uiManager.renderGameOverMenu(this->renderer,this->assetManager.getFont(),this->score,this->wave);
            break;
    }

    SDL_RenderPresent(this->renderer);
}

bool Game::checkCollision(const SDL_Rect &a,const SDL_Rect &b){
    return SDL_HasIntersection(&a,&b);
}

void Game::resetGame(){
    this->score=0;
    this->wave=1;
    this->state=PLAYING;

    this->bullets.clear();
    this->enemies.clear();

    SDL_Texture *texture=this->player.getTexture();
    this->player = Player();
    this->player.setTexture(texture);

    this->spawner=EnemySpawner();
}