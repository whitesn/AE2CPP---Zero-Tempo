#include "Helper.h"

Helper::Helper()
{
    //ctor
}

Helper::~Helper()
{
    //dtor
}

void Helper::error() {
    cout << "SDL_Error: " << SDL_GetError() << endl;
}

SDL_Texture* Helper::load_texture( SDL_Renderer* r, string path )
{
    SDL_Surface* s = IMG_Load( path.c_str() );

    if( s == NULL ) {
        cout << "Failed to load texture: " + path + " | SDL_Error() : " + SDL_GetError();
        exit( 1 );
    }

    SDL_Texture* t = SDL_CreateTextureFromSurface( r, s );
    if( t == NULL ) {
        cout << "Failed to convert texture: " + path + " | SDL_Error() : " + SDL_GetError();
        exit( 1 );
    }

    SDL_FreeSurface( s );

    return t;
}

int Helper::get_left_margin_pos( int margin, int target_x_pos, int src_width )
{
    return target_x_pos - margin - src_width;
}

int Helper::get_right_margin_pos(int margin, int target_pos_x, int target_width)
{
    return target_pos_x + target_width + margin;
}

int Helper::get_centered_horizontal_pos( int target_x_pos, int src_width, int target_width )
{
    if( src_width > target_width ) {
        return target_x_pos - (abs(target_width-src_width) / 2);
    } else {
        return target_x_pos + (abs(target_width-src_width) / 2);
    }
}

int Helper::get_centered_vertical_pos( int target_y_pos, int src_height, int target_height )
{
    if( src_height > target_height ) {
        return target_y_pos - (abs(target_height-src_height) / 2);
    } else {
        return target_y_pos + (abs(target_height-src_height) / 2);
    }
}

string Helper::to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

void Helper::set_draw_color(SDL_Renderer* r, SDL_Color c )
{
     SDL_SetRenderDrawColor( r, c.r, c.g, c.b, c.a );
}
