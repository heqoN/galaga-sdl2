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

enum class EnemyType{
    NORMAL,
    BOSS
};

class Enemy{
    public:
        Enemy(EnemyType t=EnemyType::NORMAL);
        ~Enemy();

        void update(float formationXOffset);
        void render(SDL_Renderer *renderer);

        void setTexture(SDL_Texture *tex);
        void setPosition(float x,float y);
        void setHomePosition(float x, float y);
        void startDive();
        bool isTargetable()const;
        bool takeDamage(int amount);

        int getHealth();
        EnemyType getType();

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
        int health;

        EnemyState state;
        EnemyType type;
        float angle;

        Uint32 lastShootTime;
        Uint32 fireDelay;

        SDL_Texture *texture;
        SDL_Rect rect;
};


#endif
