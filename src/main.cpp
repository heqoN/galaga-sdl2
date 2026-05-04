#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "entities.h"


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

    SDL_Texture *playerTexture=IMG_LoadTexture(renderer,"../assets/player.png");
    SDL_SetTextureBlendMode(playerTexture,SDL_BLENDMODE_BLEND);
    if(!playerTexture){
        cout<<"Player texture load failed : "<<IMG_GetError()<<endl;
        return 1;
    }

    SDL_Event event;

    bool running=true;

    Player p;
    p.x=385;
    p.y=400;
    p.speed=5;


    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        const Uint8* keystate = SDL_GetKeyboardState(nullptr);

        if (keystate[SDL_SCANCODE_W]) p.y -= p.speed;
        if (keystate[SDL_SCANCODE_S]) p.y += p.speed;
        if (keystate[SDL_SCANCODE_A]) p.x -= p.speed;
        if (keystate[SDL_SCANCODE_D]) p.x += p.speed;



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, NULL);

        SDL_Rect dest = { (int)p.x, (int)p.y, 50, 50 };
        SDL_RenderCopy(renderer, playerTexture, NULL, &dest);;

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