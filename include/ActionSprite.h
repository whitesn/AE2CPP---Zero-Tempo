#ifndef ACTIONSPRITE_H
#define ACTIONSPRITE_H

#include "Sprite.h"

class ActionSprite : public Sprite
{
    public:
        ActionSprite( int f, int x, int y, string path, SDL_Renderer* renderer );
        virtual ~ActionSprite();
        bool is_action_done();

    protected:

    private:
};

#endif // ACTIONSPRITE_H
