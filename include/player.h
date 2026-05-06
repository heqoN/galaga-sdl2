#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player{
    public:
        Player();
        ~Player();

        void handleInput(const Uint8 *keystate);
        void update();
        void render(SDL_Renderer *renderer);

        float getX();
        float getY();

        void setTexture(SDL_Texture *tex);

        SDL_Rect getRect();

    private:
        float x,y;
        int speed;

        SDL_Texture *texture;
        SDL_Rect rect;
};


#endif