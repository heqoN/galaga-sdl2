#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;

class UIManager{
    public:
        void renderText(SDL_Renderer *renderer,TTF_Font *font,const string &text,int x,int y);
        void renderHud(SDL_Renderer *renderer,TTF_Font *font,bool alive,int score,int wave,int lives);
        void renderMenu(SDL_Renderer* renderer,TTF_Font* font);
        void renderGameOverMenu(SDL_Renderer* renderer,TTF_Font* font,int score,int wave);
};


#endif