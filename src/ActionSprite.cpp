#include "ActionSprite.h"

ActionSprite::ActionSprite( int f, int x, int y, string path,
                           SDL_Renderer* renderer) :
              Sprite( f, x, y, path, renderer )
{

}

ActionSprite::~ActionSprite()
{
    //dtor
}

bool ActionSprite::is_action_done()
{
    return _cur_frame == 0;
}
