#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"


using namespace std;


int main(void)
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        cout<<"SDL init failed. Sdl error : "<<SDL_GetError()<<endl;
        return 1;
    }
    
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout<<"SDL init failed. SDL error : " <<SDL_GetError()<< endl;
        return 1;
    }

    SDL_Window *window=SDL_CreateWindow("GaLaGa-Clone",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
    if(!window){
        cout<<"Window creation failed. Sdl error : "<<SDL_GetError()<<endl;
        return 1;
    }

    SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(!renderer){
        cout<<"Renderer creation failed. Sdl error : "<<SDL_GetError()<<endl;
        return 1;
    }

    SDL_Texture *background=IMG_LoadTexture(renderer,"../assets/background.png");
    if (!background) {
        cout<<"Background load failed : "<<IMG_GetError()<<endl;
    }

    Player p;

    SDL_Texture *playerTexture=IMG_LoadTexture(renderer,"../assets/player.png");
    if(!playerTexture){
        cout<<"Player texture load failed : "<<IMG_GetError()<<endl;
        return 1;
    }
    SDL_SetTextureBlendMode(playerTexture,SDL_BLENDMODE_BLEND);
    p.setTexture(playerTexture);

    SDL_Event event;

    bool running=true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        const Uint8 *keystate=SDL_GetKeyboardState(nullptr);
        p.handleInput(keystate);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, NULL);

        p.render(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(24);
    }


    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(background);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);


    SDL_Quit();
    IMG_Quit();

    

    return 0;
}