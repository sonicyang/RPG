#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Texture{

    public:
        Texture(SDL_Renderer* ren, TTF_Font* font);
        ~Texture();

        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

        void free(); 
        int getWidth() const { return _Width; };
        int getHeight() const { return _Height; };
    private:
        SDL_Renderer* gRenderer;
        TTF_Font* gFont;
        SDL_Texture* _Texture = NULL;
        int _Width;
        int _Height;
};

#endif //TEXTURE_H
