#include "Move.h"

Move::Move(Skill* s, vector<Creature*> target)
{
    this->_casted_skill = s;
    this->_target = target;
    this->_cast_timer = SDL_GetTicks() + s->cast_time;
    this->_is_pause = false;
}

Move::~Move()
{

}

int Move::get_cast_percentage()
{
    if( _is_pause ) {
        return 100 - ((double(_cast_timer - _pause_time) / _casted_skill->cast_time) * 100);
    } else {
        int val = 100 - ((double(_cast_timer - SDL_GetTicks()) / _casted_skill->cast_time) * 100);

        if( val < 0 || val > 100 ) {
            val = 100;
        }

        return val;
    }
}

bool Move::is_casted()
{
    return _cast_timer <= (long) SDL_GetTicks();
}

Skill* Move::get_skill()
{
    return _casted_skill;
}

vector<Creature*> Move::get_target()
{
    return _target;
}

void Move::pause()
{
    _is_pause = true;
    _pause_time = SDL_GetTicks();
}

void Move::unpause()
{
    _is_pause = false;
    _cast_timer += SDL_GetTicks() - _pause_time;
}
