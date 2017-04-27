#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Helper
{
    public:
        Helper();
        virtual ~Helper();
        static void error();
        static SDL_Texture* load_texture( SDL_Renderer* r, string path );
        static int get_left_margin_pos( int margin, int target_pos_x, int src_width );
        static int get_right_margin_pos( int margin, int target_pos_x, int target_width );
        static int get_centered_horizontal_pos( int target_x_pos, int src_width, int target_width );
        static int get_centered_vertical_pos( int target_y_pos, int src_height, int target_height );
        static string to_string(int i);
        static void set_draw_color( SDL_Renderer* r, SDL_Color c );
    protected:
    private:
};

#endif // HELPER_H
