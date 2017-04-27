#include "Skill.h"

Skill::Skill( string name, int dmg, int cd, int ct, bool is_cast_breaking,
              bool is_aoe, bool is_self_cast, StatusAilments::Ailment sa,
              int sa_chance, StatusBuff::Buff sb, string sound_effect_path )
{
    this->name = name;
    this->damage = dmg;
    this->cooldown = cd;
    this->cast_time = ct;
    this->is_cast_breaking = is_cast_breaking;
    this->is_aoe = is_aoe;
    this->is_self_cast = is_self_cast;
    this->status_ailment = sa;
    this->status_ailment_chance = sa_chance;
    this->buff = sb;

     _sound_effect = Mix_LoadWAV( sound_effect_path.c_str() );
}

Skill::Skill()
{
}

Skill::~Skill()
{
    Mix_FreeChunk( _sound_effect );
}

bool Skill::is_healing_skill() {
    return damage < 0;
}

bool Skill::is_positive_skill() {
    return damage <= 0 && status_ailment == StatusAilments::NONE && !is_cast_breaking;
}

void Skill::play_sound_effect() {
    Mix_PlayChannel( -1, _sound_effect, 0 );
}

