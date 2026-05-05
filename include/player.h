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
        void setTexture(SDL_Texture *tex);

        float x,y;
        int speed;

    private:
        SDL_Texture *texture;
};


#endif