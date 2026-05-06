#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

class Bullet{
    public:
        Bullet();
        ~Bullet();

        void update();
        void render(SDL_Renderer *renderer);

        void shoot();

        void setPosition(float x,float y);

        SDL_Rect getRect();
        bool isActive();

    private:
        float x,y;
        int speed;

        bool active;

        SDL_Rect rect;
        

};


#endif