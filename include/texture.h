#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Texture{

    public:
        typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;

        Texture();
        ~Texture();

        bool loadFromRenderedText(const char* textureText, SDL_Color textColor, SDL_Renderer*, TTF_Font*);
        bool loadFromRenderedText(const wchar_t* textureText, SDL_Color textColor, SDL_Renderer*, TTF_Font*);
        bool loadFromFile(std::string path, SDL_Renderer*, bool enableKeying = false);

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
