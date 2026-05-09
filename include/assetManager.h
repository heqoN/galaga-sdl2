#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class AssetManager{
    private:
        SDL_Texture *playerTexture;
        SDL_Texture *enemyTexture;
        SDL_Texture *backgroundTexture;
        TTF_Font *font;

    public:
        AssetManager();
        ~AssetManager();

        bool load(SDL_Renderer *renderer);
        void clean();

        SDL_Texture* getPlayerTexture();
        SDL_Texture* getEnemyTexture();
        SDL_Texture* getBackgroundTexture();
        TTF_Font* getFont();
};

#endif