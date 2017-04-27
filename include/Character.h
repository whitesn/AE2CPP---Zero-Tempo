#ifndef CHARACTER_H
#define CHARACTER_H

#include "Creature.h"
#include "Skill.h"
#include "Sprite.h"

class Character : public Creature
{
    public:
        Character();
        Character( string name, int max_hp, int initial_cooldown, int atk,
                   int def, Sprite* sprite, ActionSprite* action_sprite, SDL_Texture* dead_sprite );
        virtual ~Character();

    protected:
    private:
};

#endif // CHARACTER_H
