#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

class Enemy{
    public:
        Enemy();
        ~Enemy();

        void update();
        void render(SDL_Renderer *renderer);

        void setTexture(SDL_Texture *tex);
        void setPosition(float x,float y);

        SDL_Rect getRect() const;

    private:
        float x,y;
        int speed;
        int direction; //1 sağ , -1 sol

        SDL_Texture *texture;
        SDL_Rect rect;
};


#endif
