#ifndef MONSTER_H
#define MONSTER_H

#include <random>
#include "Creature.h"

using namespace std;

const int HP_CD_BAR_WIDTH = 100; // pixels
const int HP_CD_BAR_HEIGHT = 6; // pixels
const SDL_Color HP_BAR_COLOR = { 82, 155, 76, 255 };
const SDL_Color HP_BAR_LOW_COLOR = { 155, 70, 70, 255 };
const SDL_Color COOLDOWN_BAR_COLOR = { 61, 116, 184, 255 };
const SDL_Color BASE_BG_COLOR = { 200, 200, 200, 255 };
const int BAR_MARGIN = 6; // pixels
const int STATUS_AILMENT_RIGHT_MARGIN = 14; // pixels
const int STATUS_ICONS_MONSTER_MARGIN = 8; // pixels
const int STATUS_BUFF_AIL_MONSTER_MARGIN = 8; // pixels
const double STATUS_AILMENT_ICON_RESIZE_SCALING = 0.5; // percent
const double STATUS_BUFF_ICON_RESIZE_SCALING = 0.8; // percent

class Monster : public Creature
{
    public:
        Monster();
        Monster( string name, int max_hp, int initial_cooldown, int atk,
                 int def, Sprite* sprite, ActionSprite* action_sprite, SDL_Texture* dead_sprite );
        virtual ~Monster();
        void think( vector<Creature*>* characters, vector<Creature*>* monsters );
        void render() override;

    protected:
    private:
};

#endif // MONSTER_H
