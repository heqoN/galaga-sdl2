#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <cmath>

enum class EnemyState{
    ENTERING,
    IN_FORMATION,
    DIVING,
    RETURNING
};

class Enemy{
    public:
        Enemy();
        ~Enemy();

        void update(float formationXOffset);
        void render(SDL_Renderer *renderer);

        void setTexture(SDL_Texture *tex);
        void setPosition(float x,float y);
        void setHomePosition(float x, float y);
        void startDive();
        bool isTargetable()const;


        void setAlive();
        void setDead();
        bool isAlive();

        float getX();
        float getY();

        void currentToLastShootTime(Uint32 currentTime);
        Uint32 getLastShootTime();
        Uint32 getFireDelay();

        SDL_Rect getRect() const;

    private:
        float x,y;
        float homeX,homeY;
        int speed;
        int direction; //1 sağ , -1 sol
        bool alive;

        EnemyState state;
        float angle;

        Uint32 lastShootTime;
        Uint32 fireDelay;

        SDL_Texture *texture;
        SDL_Rect rect;
};


#endif
