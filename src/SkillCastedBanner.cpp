#include "SkillCastedBanner.h"

SkillCastedBanner::SkillCastedBanner( SDL_Renderer* r, string name, int char_pos_x, int char_pos_y, int char_width )
{
    _renderer = r;
    _timer = SDL_GetTicks() + BANNER_DURATION;

    TTF_Font* font = TTF_OpenFont( CAST_BANNER_FONT_PATH.c_str(), FONT_SIZE );
    if( font == NULL ) {
        Helper::error();
    }

    SDL_Color text_color = { 255, 255, 255, 100 };
    SDL_Surface* s = TTF_RenderText_Blended( font, name.c_str(), text_color );
    if( s == NULL ) {
        Helper::error();
    }

    _texture = SDL_CreateTextureFromSurface( _renderer, s );
    SDL_QueryTexture( _texture, NULL, NULL, &_width, &_height );

    TTF_CloseFont( font );
    font = NULL;
    SDL_FreeSurface( s );

    _x = Helper::get_centered_horizontal_pos( char_pos_x, _width, char_width );
    _y = char_pos_y - _height - CASTED_BANNER_TOP_MARGIN;
}

SkillCastedBanner::~SkillCastedBanner()
{
    SDL_DestroyTexture( _texture );
}

bool SkillCastedBanner::is_done()
{
    return _timer <= (long) SDL_GetTicks();
}

void SkillCastedBanner::render()
{
    SDL_Rect cropper, opt;
    cropper = { 0, 0, _width + BG_PADDING * 2, _height + BG_PADDING * 2 };
    opt = { _x - BG_PADDING, _y - BG_PADDING, _width + BG_PADDING * 2, _height + BG_PADDING * 2 };
    SDL_Texture* bg = SDL_CreateTexture( _renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                        _width + BG_PADDING * 2, _height + BG_PADDING * 2 );
    SDL_SetTextureBlendMode( bg, SDL_BLENDMODE_BLEND );

    // Fill Texture
    SDL_SetRenderTarget( _renderer, bg );
    SDL_SetRenderDrawColor( _renderer, 0, 0, 0, TRANSPARENCY );
    SDL_RenderFillRect( _renderer, NULL );
    SDL_SetRenderDrawColor( _renderer, 0, 0, 0, 255 );
    SDL_SetRenderTarget( _renderer, NULL );
    SDL_RenderCopy( _renderer, bg, &cropper, &opt );

    // Printing Text
    cropper = { 0, 0, _width, _height };
    opt = { _x, _y, _width, _height };
    SDL_RenderCopy( _renderer, _texture, &cropper, &opt );

    SDL_DestroyTexture( bg );
}
