#ifndef CASTINGBAR_H
#define CASTINGBAR_H

#include <SDL.h>
#include "Helper.h"

const int CASTING_BAR_WIDTH = 80;
const int CASTING_BAR_HEIGHT = 8;
const int TOP_MARGIN = 0;
const int BORDER_WIDTH = 2;

class CastingBar
{
    public:
        CastingBar();
        virtual ~CastingBar();
        static void render_casting_bar( SDL_Renderer* r, int spr_pos_x, int spr_pos_y,
                                        int spr_width, int percentage );

    protected:

    private:
        static constexpr SDL_Color CASTING_BAR_COLOR = { 40, 255, 40, 255 };
        static constexpr SDL_Color CASTING_BAR_BORDER_COLOR = { 0, 0, 0, 255 };
        static constexpr SDL_Color CASTING_BAR_BASE_COLOR = { 60, 60, 60, 255 };

};

#endif // CASTINGBAR_H
