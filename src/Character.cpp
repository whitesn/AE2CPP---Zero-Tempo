#include "Character.h"

Character::Character(string name, int max_hp, int initial_cooldown, int atk,
                     int def, Sprite* sprite, ActionSprite* action_sprite,
                     SDL_Texture* dead_sprite ) :
           Creature( name, max_hp, initial_cooldown, atk, def, sprite, action_sprite, dead_sprite )
{

}


Character::~Character()
{
    //dtor
}
