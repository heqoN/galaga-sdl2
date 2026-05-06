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

        float getX();
        float getY();

        void currentToLastShootTime(Uint32 currentTime);
        Uint32 getLastShootTime();
        Uint32 getFireDelay();

        SDL_Rect getRect() const;

    private:
        float x,y;
        int speed;
        int direction; //1 sağ , -1 sol

        Uint32 lastShootTime;
        Uint32 fireDelay;

        SDL_Texture *texture;
        SDL_Rect rect;
};


#endif
