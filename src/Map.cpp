#include "Map.h"

Map::Map( string path, SDL_Renderer* r, int width, int height )
{
    this->_path = path;
    this->_renderer = r;
    this->_width = width;
    this->_height = height;
    this->_texture = Helper::load_texture( r, path );
}

Map::~Map()
{
    SDL_DestroyTexture( _texture );
}

void Map::render()
{
    int w, h;
    SDL_Rect cropper, opt;

    SDL_QueryTexture( this->_texture, NULL, NULL, &w, &h );
    cropper = { 0, 0, w, h };
    opt = { 0, 0, _width, _height };
    SDL_RenderCopy( _renderer, _texture, &cropper, &opt );
}
