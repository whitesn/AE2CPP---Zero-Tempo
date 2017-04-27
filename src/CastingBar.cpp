#include "CastingBar.h"

CastingBar::CastingBar()
{
}

CastingBar::~CastingBar()
{
    //dtor
}

void CastingBar::render_casting_bar( SDL_Renderer* r, int spr_pos_x, int spr_pos_y,
                                     int spr_width, int percentage )
{
    SDL_Rect shape = { Helper::get_centered_horizontal_pos(spr_pos_x, CASTING_BAR_WIDTH, spr_width),
                       spr_pos_y - TOP_MARGIN - CASTING_BAR_HEIGHT, CASTING_BAR_WIDTH, CASTING_BAR_HEIGHT };

    // Draw the base
    SDL_SetRenderDrawColor( r, CastingBar::CASTING_BAR_BASE_COLOR.r,
                               CastingBar::CASTING_BAR_BASE_COLOR.g,
                               CastingBar::CASTING_BAR_BASE_COLOR.b,
                               CastingBar::CASTING_BAR_BASE_COLOR.a );
    SDL_RenderFillRect( r, &shape );

    // Draw the cooldown percentage
    shape.w = (double) percentage / 100 * CASTING_BAR_WIDTH;
    SDL_SetRenderDrawColor( r, CastingBar::CASTING_BAR_COLOR.r,
                               CastingBar::CASTING_BAR_COLOR.g,
                               CastingBar::CASTING_BAR_COLOR.b,
                               CastingBar::CASTING_BAR_BASE_COLOR.a );
    SDL_RenderFillRect( r, &shape );

    // Draw the border
    shape.w = CASTING_BAR_WIDTH;
    SDL_SetRenderDrawColor( r, CastingBar::CASTING_BAR_BORDER_COLOR.r,
                               CastingBar::CASTING_BAR_BORDER_COLOR.g,
                               CastingBar::CASTING_BAR_BORDER_COLOR.b,
                               CastingBar::CASTING_BAR_BORDER_COLOR.a );
    SDL_RenderDrawRect( r, &shape );
}
