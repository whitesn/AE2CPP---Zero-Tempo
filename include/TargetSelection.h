#ifndef TARGETSELECTION_H
#define TARGETSELECTION_H

#include <vector>
#include "Helper.h"
#include "Character.h"
#include "Monster.h"
#include "Skill.h"

using namespace std;

const int SELECTION_POINTER_MARGIN = 30;
enum SELECTION_MODE { BACKWARD, FORWARD };

class TargetSelection
{
    public:
        TargetSelection( SDL_Renderer* r, string pointer_path, vector<Character*> c, vector<Monster*> m  );
        virtual ~TargetSelection();
        void point_previous();
        void point_next();
        void point_single_target( SELECTION_MODE p );
        vector<Creature*> get_pointed_creature();
        void render();
        void activate_target_selection( Skill* s );
        void reset_selection();
        void set_monsters_list( vector<Monster*> monsters );
        bool is_basic_attack;

    protected:

    private:
        SDL_Renderer* _renderer;
        SDL_Texture* _selector;
        vector<Monster*> _monsters;
        vector<Character*> _characters;
        vector<Creature*> _pointed_target;
        int _pointer_width;
        int _pointer_height;
        bool is_pointing_monster();
        int get_pointing_index();
        void set_pointing_characters();
        void set_pointing_monsters();

        Skill* _active_skill;
};

#endif // TARGETSELECTION_H
