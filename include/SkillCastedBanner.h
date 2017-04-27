#ifndef SKILLCASTEDBANNER_H
#define SKILLCASTEDBANNER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Helper.h"

const string CAST_BANNER_FONT_PATH = "fonts/segoeuib.ttf";
const int FONT_SIZE = 12; //pixels
const int BANNER_DURATION = 2000; //ms
const int BG_PADDING = 4; // pixels
const int TRANSPARENCY = 150; // out of 255
const int CASTED_BANNER_TOP_MARGIN = 10; // pixels

class SkillCastedBanner
{
    public:
        SkillCastedBanner( SDL_Renderer* r, string name, int char_pos_x, int char_pos_y, int char_width );
        virtual ~SkillCastedBanner();
        void render();
        bool is_done();

    protected:

    private:
        SDL_Renderer* _renderer;
        SDL_Texture* _texture;
        long _timer;
        int _x, _y;
        int _width, _height;
};

#endif // SKILLCASTEDBANNER_H
