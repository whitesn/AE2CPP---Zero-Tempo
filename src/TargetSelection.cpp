#include "TargetSelection.h"

TargetSelection::TargetSelection( SDL_Renderer* r, string pointer_path,
                                  vector<Character*> c, vector<Monster*> m )
{
    _renderer = r;
    _characters = c;
    _monsters = m;

    _selector = Helper::load_texture( r, pointer_path );
    SDL_QueryTexture( _selector, NULL, NULL, &_pointer_width, &_pointer_height );

    is_basic_attack = false;
}

TargetSelection::~TargetSelection()
{
    SDL_DestroyTexture( _selector );
}

bool TargetSelection::is_pointing_monster()
{
    for( Uint8 i = 0; i < _monsters.size(); i++ ) {
        if( _pointed_target[0] == _monsters[i] ) {
            return true;
        }
    }
    return false;
}

int TargetSelection::get_pointing_index()
{
    vector<Creature*>* target_list = (is_pointing_monster()) ? (vector<Creature*>*) &_monsters : (vector<Creature*>*) &_characters;

    for( Uint8 i = 0; i < (*target_list).size(); i++ ) {
        if( _pointed_target[0] == (*target_list)[i] ) {
            return i;
        }
    }

    return 0;
}

void TargetSelection::set_pointing_characters()
{
    _pointed_target.clear();
    for( Uint8 i = 0; i < _characters.size(); i++ ) {
        if( _characters[i]->is_alive() ) {
            _pointed_target.push_back( _characters[i] );
        }
    }
}

void TargetSelection::set_pointing_monsters()
{
    _pointed_target.clear();
    for( Uint8 i = 0; i < _monsters.size(); i++ ) {
        if( _monsters[i]->is_alive() ) {
            _pointed_target.push_back( _monsters[i] );
        }
    }
}

void TargetSelection::point_single_target( SELECTION_MODE path )
{
    Uint8 iterate = ( path == FORWARD ) ? 1 : -1;
    Uint8 pointed_index = get_pointing_index() + iterate;

    vector<Creature*>* target_list;
    vector<Creature*>* second_list;

    if( is_pointing_monster() ) {
        target_list = (vector<Creature*>*) &_monsters;
        second_list = (vector<Creature*>*) &_characters;
    } else {
        target_list = (vector<Creature*>*) &_characters;
        second_list = (vector<Creature*>*) &_monsters;
    }


    for( Uint8 i = pointed_index; i >= 0 && i < (*target_list).size(); i += iterate )
    {
        if( (*target_list)[i]->is_alive() ) {
            _pointed_target[0] = (*target_list)[i];
            return;
        }
    }

    Uint8 start_index = ( path == FORWARD ) ? 0 : (*second_list).size() - 1;

    for( Uint8 i = start_index; i >= 0 && i < (*second_list).size(); i += iterate )
    {
        if( (*second_list)[i]->is_alive() ) {
            _pointed_target[0] = (*second_list)[i];
            return;
        }
    }
}

void TargetSelection::point_previous()
{
    if( !is_basic_attack && _active_skill->is_aoe ) {
        if( is_pointing_monster() ) {
            set_pointing_characters();
        } else {
            set_pointing_monsters();
        }
    } else {
        point_single_target( BACKWARD );
    }
}

void TargetSelection::point_next()
{
    if( !is_basic_attack && _active_skill->is_aoe ) {
        if( is_pointing_monster() ) {
            set_pointing_characters();
        } else {
            set_pointing_monsters();
        }
    } else {
        point_single_target( FORWARD );
    }
}

vector<Creature*> TargetSelection::get_pointed_creature()
{
    return _pointed_target;
}

void TargetSelection::render()
{
    for( auto const& target: _pointed_target ){
        int pos_x = (target->get_sprite()->pos_x) + ((target->get_sprite()->width - _pointer_width) / 2);
        int pos_y = (target->get_sprite()->pos_y) - _pointer_height - SELECTION_POINTER_MARGIN;

        SDL_Rect cropper, opt;
        cropper = { 0, 0, _pointer_width, _pointer_height };
        opt = { pos_x, pos_y, _pointer_width, _pointer_height };
        SDL_RenderCopy( _renderer, _selector, &cropper, &opt );
    }
}

void TargetSelection::activate_target_selection( Skill* s )
{
    _active_skill = s;

    if( is_basic_attack ) {

        size_t i = 0;
        Monster* m;

        do {
            m = _monsters[i];
        } while( !m->is_alive() && ++i < _monsters.size() );

        _pointed_target.push_back( m );

    } else if( s->is_aoe ) {
        if( s->is_healing_skill() || s->is_positive_skill() ) {
            set_pointing_characters();
        } else {
            set_pointing_monsters();
        }
    } else {

        if( s->is_healing_skill() || s->is_positive_skill() ) {

            Character* c;
            size_t i = 0;

            do {
                c = _characters[i];
            } while( !c->is_alive() && ++i < _characters.size() );

            _pointed_target.push_back( c );

        } else {

            Monster* m;
            size_t i = 0;

            do {
                m = _monsters[i];
            } while( !m->is_alive() && ++i < _monsters.size() );

            _pointed_target.push_back( m );
        }
    }
}

void TargetSelection::reset_selection()
{
    _pointed_target.clear();
    is_basic_attack = false;
    _active_skill = NULL;
}

void TargetSelection::set_monsters_list( vector<Monster*> monsters )
{
    _monsters.clear();
    this->_monsters = monsters;
}
