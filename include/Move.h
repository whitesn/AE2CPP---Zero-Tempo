#ifndef MOVE_H
#define MOVE_H

#include <SDL.h>
#include <vector>
#include "Skill.h"

class Creature;

class Move
{
    public:
        Move( Skill* s, vector<Creature*> target );
        virtual ~Move();
        bool is_casted();
        Skill* get_skill();
        vector<Creature*> get_target();
        int get_cast_percentage();
        void pause();
        void unpause();

    protected:
    private:
        Skill* _casted_skill;
        vector<Creature*> _target;
        long _cast_timer;
        bool _is_pause;
        long _pause_time;
};

#endif // MOVE_H
