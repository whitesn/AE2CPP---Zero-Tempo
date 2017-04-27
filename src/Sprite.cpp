#include "Sprite.h"

Sprite::Sprite( int f, int x, int y, string path, SDL_Renderer* renderer )
{
    this->_frames = f;
    this->renderer = renderer;
    this->_sprite = Helper::load_texture( renderer, path );

    SDL_QueryTexture( _sprite, NULL, NULL, &width, &height );
    this->width = width / _frames;

    this->pos_x = x;
    this->pos_y = y;
    this->_cur_frame = 0;
}

Sprite::~Sprite()
{
    SDL_DestroyTexture( _sprite );
}

void Sprite::next_frame()
{
    if( ++_cur_frame / FRAME_CYCLES == _frames ) {
        _cur_frame = 0;
    }
}

SDL_Rect Sprite::get_cropper()
{
    SDL_Rect cropper = { _cur_frame / FRAME_CYCLES * width, 0, width, height };
    return cropper;
}

void Sprite::animate_texture()
{
    SDL_Rect cropper, opt;
    cropper = get_cropper();
    opt = { pos_x, pos_y, width, height };
    SDL_RenderCopy( renderer, _sprite, &cropper, &opt );
    this->next_frame();
}
