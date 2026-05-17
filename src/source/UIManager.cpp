#include "UIManager.h"
#include <string>

using namespace std;

void UIManager::renderText(SDL_Renderer *renderer,TTF_Font *font,const string &text,int x,int y){
    SDL_Color color={255,255,255,255};
    SDL_Surface *surface=TTF_RenderText_Solid(font,text.c_str(),color);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Rect rect={x,y,surface->w,surface->h};

    SDL_RenderCopy(renderer,texture,NULL,&rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void UIManager::renderHud(SDL_Renderer* renderer,TTF_Font* font,bool alive,int score,int wave,int lives){
    this->renderText(renderer,font,"Score: " + std::to_string(score),20,20);
    this->renderText(renderer,font,"Wave: " + std::to_string(wave),20,50);
    if(alive){
        this->renderText(renderer,font,"Lives: " + std::to_string(lives),20,80);
    }
    else{
        this->renderText(renderer,font,"Lives: 0",20,80);
    }
}

void UIManager::renderMenu(SDL_Renderer* renderer,TTF_Font* font){
    this->renderText(renderer,font,"GALAGA SDL2",320,180);
    this->renderText(renderer,font,"Press ENTER to Start",280,300);
    this->renderText(renderer,font,"Press L to View Leaderboard",240,380);
    this->renderText(renderer,font,"Press ESC to Exit",300,460);
}

void UIManager::renderGameOverMenu(SDL_Renderer* renderer,TTF_Font* font,int score,int wave){
    this->renderText(renderer,font,"GAME OVER",330,230);
    this->renderText(renderer,font,"Final Score: " + std::to_string(score),300,270);
    this->renderText(renderer,font,"Final Wave: " + std::to_string(wave),310,300);
    this->renderText(renderer,font,"Press R for restart",285,330);
    this->renderText(renderer,font,"Press BACKSPACE to return to Menu",225,360);
    this->renderText(renderer,font,"Press ESC to Exit",300,390);
}

void UIManager::renderLeaderboard(SDL_Renderer *renderer,TTF_Font *font,vector<int> scores){
    this->renderText(renderer,font,"Leaderboard :",320,180);

    if(scores.empty()){
        this->renderText(renderer,font,"No scores yet",300,300);
    }
    else{
        for(long unsigned int i = 0; i < scores.size(); i++){
            string text = std::to_string(i+1) + "- " + std::to_string(scores[i]);
            this->renderText(renderer,font,text,300,270 + i*30);
        }
    }

    this->renderText(renderer,font,"Press BACKSPACE to return to Menu",200,450);
}