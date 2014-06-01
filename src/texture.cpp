#include "texture.h"


Texture::Texture(SDL_Renderer* ren, TTF_Font* font) :
    gRenderer(ren),
    gFont(font)
{

}

Texture::~Texture(){
    free();
}


bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor){
    free();
    
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL ){
        _Texture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( _Texture != NULL ){
            _Width = textSurface->w;
            _Height = textSurface->h;
        }
        
        SDL_FreeSurface( textSurface );
    }
    
    return _Texture != NULL;
}

void Texture::free(){
    if(_Texture != NULL){
        SDL_DestroyTexture(_Texture);
        _Texture = NULL;
        _Width = 0;
        _Height = 0;
    }
}
