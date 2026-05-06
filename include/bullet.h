#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

enum class BULLET_Type{
    Player,
    Enemy
};


class Bullet{
    public:
        Bullet();
        ~Bullet();

        void update();
        void render(SDL_Renderer *renderer);

        void shoot(BULLET_Type type);

        void setPosition(float x,float y);

        SDL_Rect getRect();
        bool isActive();
        BULLET_Type getType();

    private:
        float x,y;
        int speed;

        BULLET_Type type;

        bool active;

        SDL_Rect rect;
        

};


#endif