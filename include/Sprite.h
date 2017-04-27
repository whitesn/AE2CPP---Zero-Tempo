#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Helper.h"

using namespace std;

const int FRAME_CYCLES = 6;

class Sprite
{
    public:
        Sprite( int f, int x, int y, string path, SDL_Renderer* renderer );
        virtual ~Sprite();
        SDL_Rect get_cropper();
        void animate_texture();
        int width;
        int height;
        int pos_x;
        int pos_y;
        SDL_Renderer* renderer;

    protected:
        int _cur_frame;
        int _frames;

    private:
        void next_frame();
        SDL_Texture* _sprite;
};

#endif // SPRITE_H
