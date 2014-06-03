#include "texture.h"


Texture::Texture()
{

}

Texture::~Texture(){
    free();
}


bool Texture::loadFromRenderedText(const char* textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont){
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText, textColor );
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

bool Texture::loadFromFile( std::string path, SDL_Renderer* gRenderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface != NULL ){
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture != NULL ){
			//Get image dimensions
			_Width = loadedSurface->w;
			_Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	_Texture = newTexture;
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

void Texture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect renderQuad = { x, y, _Width, _Height };

    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( gRenderer, _Texture, clip, &renderQuad, angle, center, flip );
}

