#ifndef SKILL_H
#define SKILL_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <random>
#include <time.h>
#include "StatusAilments.h"
#include "StatusBuff.h"
#include "Helper.h"

using namespace std;

class Skill
{
    public:
        Skill( string name, int dmg, int cd, int ct, bool is_cast_breaking,
               bool is_aoe, bool is_self_cast, StatusAilments::Ailment _sa,
               int _sa_chance, StatusBuff::Buff buff, string sound_effect_path );
        Skill();
        virtual ~Skill();
        typedef StatusAilments::Ailment Ailment;

        string name;
        int damage;
        int cooldown;
        int cast_time;
        bool is_cast_breaking;
        bool is_self_cast;
        bool is_aoe;
        StatusAilments::Ailment status_ailment;
        StatusBuff::Buff buff;
        int status_ailment_chance;
        bool is_healing_skill();
        bool is_positive_skill();
        void play_sound_effect();

    protected:
    private:
        Mix_Chunk* _sound_effect;
};

#endif // SKILL_H
