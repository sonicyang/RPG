#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Texture{

    public:
        Texture();
        ~Texture();

        bool loadFromRenderedText(const char* textureText, SDL_Color textColor, SDL_Renderer*, TTF_Font*);

        void free();

        void render(SDL_Renderer*, int, int, SDL_Rect* = NULL, double = 0.0, SDL_Point* = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

        int getWidth() const { return _Width; };
        int getHeight() const { return _Height; };
    private:
        SDL_Texture* _Texture = NULL;
        int _Width;
        int _Height;
};

#endif //TEXTURE_H
