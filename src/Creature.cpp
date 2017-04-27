#include "Creature.h"

Creature::Creature()
{
    //ctor
}

Creature::~Creature()
{
    delete( _sprite );
    delete( _action_sprite );
    SDL_DestroyTexture( _dead_texture );

    if( _move != NULL ) {
        delete( _move );
    }

    if( _scb != NULL ) {
        delete( _scb );
    }

    for( StatusAilments* sa : _ail_statuses ) {
        delete( sa );
    }

    for( StatusBuff* sb : _buff_statuses ) {
        delete( sb );
    }
}

Creature::Creature( string name, int max_hp, int initial_cooldown,
                    int atk, int def, Sprite* sprite, ActionSprite* action_sprite,
                    SDL_Texture* dead_texture )
{
    _name = name;
    _max_hp = max_hp;
    _hp = _max_hp;
    _ail_statuses.clear();
    _buff_statuses.clear();
    add_cooldown( initial_cooldown );
    _initial_cooldown = initial_cooldown;
    _cooldown = initial_cooldown;
    _atk = atk;
    _def = def;
    _sprite = sprite;
    _action_sprite = action_sprite;
    _dead_texture = dead_texture;

    _move = NULL;
    _is_casting = false;
    _is_executing = false;
    _is_pause = false;
    _scb = NULL;
}

void Creature::reset_state()
{
    _hp = _max_hp;
    _ail_statuses.clear();
    _buff_statuses.clear();
    _cooldown = 0;
    add_cooldown( _initial_cooldown );
    _move = NULL;
    _is_casting = false;
    _is_executing = false;
    _is_pause = false;
    _scb = NULL;
}

void Creature::set_action_sprite(ActionSprite* sprite)
{
    _action_sprite = sprite;
}


void Creature::set_name(string name)
{
    _name = name;
}

void Creature::set_hp(int hp)
{
    _hp = hp;
}

void Creature::set_max_hp(int max_hp)
{
    _max_hp = max_hp;
}

void Creature::set_atk(int atk)
{
    _atk = atk;
}

void Creature::set_def(int def)
{
    _def = def;
}

void Creature::add_buff_status(StatusBuff* buff_status)
{
    for( size_t i = 0; i < _buff_statuses.size(); i++ ) {
        StatusBuff* sb = _buff_statuses[i];
        if( sb->buff == buff_status->buff ) {
            _buff_statuses.erase( _buff_statuses.begin() + i );
            delete( sb );
            break;
        }
    }

    _buff_statuses.push_back( buff_status );
}

void Creature::add_ail_status(StatusAilments* ail_status)
{
    for( size_t i = 0; i < _ail_statuses.size(); i++ ) {
        StatusAilments* sa = _ail_statuses[i];
        if( sa->ailment == ail_status->ailment ) {
            _ail_statuses.erase( _ail_statuses.begin() + i );
            delete( sa );
            break;
        }
        i++;
    }

    _ail_statuses.push_back( ail_status );
}

void Creature::add_skill(Skill* new_skill)
{
    cout << print_name() << " learned " << new_skill->name << "!" << endl;
    _skills.push_back( new_skill );
}

string Creature::get_name()
{
    return _name;
}

int Creature::get_hp()
{
    return _hp;
}

int Creature::get_max_hp()
{
    return _max_hp;
}

long Creature::get_cooldown()
{
    long cd;

    if( _is_pause ) {
        cd = _cooldown - _pause_time;
    } else {
        cd = _cooldown - SDL_GetTicks();
    }

    cd = ( cd <= 0 ) ? 0 : cd;

    return cd;
}

Skill* Creature::get_skill( int i )
{
    Skill* s = _skills.at( i );
    return s;
}

int Creature::get_skill_count()
{
    return _skills.size();
}

Sprite* Creature::get_sprite()
{
    return _sprite;
}

bool Creature::is_frozen()
{
    for( StatusAilments* sa : _ail_statuses )
    {
        if( sa->ailment == StatusAilments::FREEZE ) {
            return true;
        }
    }
    return false;
}

bool Creature::is_ready()
{
    return _cooldown <= SDL_GetTicks() && !_is_casting && !is_frozen();
}

int Creature::get_atk()
{
    return _atk;
}

int Creature::get_def()
{
    return _def;
}

vector<StatusBuff*> Creature::get_buff_statuses()
{
    return _buff_statuses;
}

vector<StatusAilments*> Creature::get_ail_statuses()
{
    return _ail_statuses;
}

bool Creature::is_casting()
{
    return _is_casting;
}

bool Creature::is_alive()
{
    return _hp > 0;
}

void Creature::set_sprite(Sprite* sprite)
{
    _sprite = sprite;
}

void Creature::render()
{
    if( !is_alive() ) {
        SDL_Rect cropper, opt;
        int w, h;
        SDL_QueryTexture( _dead_texture, NULL, NULL, &w, &h );
        cropper = { 0, 0, w, h };
        opt = { _sprite->pos_x, _sprite->pos_y, w, h };
        SDL_RenderCopy( _sprite->renderer, _dead_texture, &cropper, &opt );
    } else {
        if( _is_executing ) {
            _action_sprite->animate_texture();
            if( _action_sprite->is_action_done() ) {
                _is_executing = false;
            }
        } else {
            _sprite->animate_texture();
        }

        if( _is_casting ) {
            CastingBar::render_casting_bar( _sprite->renderer, _sprite->pos_x, _sprite->pos_y,
                                            _sprite->width, _move->get_cast_percentage() );
        }

        if( _scb != NULL && !_scb->is_done() ) {
            _scb->render();
        } else {
            delete( _scb );
            _scb = NULL;
        }
    }
}

void Creature::basic_attack( Creature* target )
{
    _is_executing = true;
    add_cooldown( BASIC_ATTACK_COOLDOWN );
    target->receive_damage( this->_atk * BASIC_ATTACK_DMG );
    play_basic_attack_sound();
}

void Creature::skill( int skill_index, vector<Creature*> target )
{
    Skill* s = this->_skills[skill_index];
    cout << print_name() << " is casting " << s->name << endl;

    if( s->cast_time > 0 ) {
        play_casting_sound();
        _is_casting = true;
    }

    _move = new Move( s, target );
}

void Creature::execute_move()
{
    if( !is_alive() ) {
        return;
    }

    Skill* s = _move->get_skill();
    vector<Creature*> targets = _move->get_target();

    // Apply damage or healing
    if( s->is_healing_skill() ) {
        int healing = s->damage * (-_atk);
        for( auto const& target: targets ){
            cout << print_name() << " heals " << target->print_name() << " for " << healing << endl;
            target->receive_healing( healing );
        }
    } else if( !s->is_positive_skill() && s->damage > 0 ) {
        for( auto const& target: targets ){

            int damage = (s->damage * _atk) * ((double) target->get_def() / 100);

            if( is_concentrated() ) {
                damage += (double) damage * StatusBuff::CONCENTRATED_ADD_DAMAGE_PERCENTAGE / 100;
            }

            if( target->has_reflect_shield() ) {
                damage *= (double) StatusBuff::REFLECT_RETURN_DAMAGE_PERCENTAGE / 100;
                cout << target->print_name() << " reflected " << damage << " dmg(s) to "
                     << print_name() << endl;
                receive_damage( damage );
            } else {
                cout << print_name() << " executes " << s->name << " dealing "
                     << damage << " dmg(s) to " << target->get_name() << endl;
                target->receive_damage( damage );
            }
        }
    }

    // Apply Cast breaking
    if( s->is_cast_breaking ) {
        for( auto const& target: targets ){
            if( !(target == this) && !target->has_reflect_shield() && rand() % 100 + 1 <= CAST_BREAKING_CHANCE ) {
                target->break_cast();
            }
        }
    }

    // Apply Status Ailment
    if( s->status_ailment != StatusAilments::NONE ) {
        for( auto const& target: targets ){
            if( (rand() % 100) + 1 <= s->status_ailment_chance ) {

                StatusAilments* sa = new StatusAilments( s->status_ailment );

                if( target->has_reflect_shield() ) {
                    add_ail_status( sa );
                    cout << print_name() << " received status: " << sa->get_status_name()
                         << " for " << sa->get_second_duration() << " sec(s)." << endl;
                } else {
                    target->add_ail_status( sa );
                    cout << target->print_name() << " received status: " << sa->get_status_name()
                         << " for " << sa->get_second_duration() << " sec(s)." << endl;
                }

            }
        }
    }

    // Apply Status Buff
    if( s->buff != StatusBuff::NONE ) {
        for( auto const& target: targets ){
            StatusBuff* sb = new StatusBuff( s->buff );
            target->add_buff_status( sb );
            cout << target->print_name() << " received status: " << sb->get_status_name()
                 << " for " << sb->get_second_duration() << " sec(s)." << endl;
        }
    }

    // Apply Recovery
    if( s->buff == StatusBuff::RECOVERY ) {
        for( auto const& target: targets ) {
            target->remove_all_ailments();
        }
    }

    _move->get_skill()->play_sound_effect();

    // Remove movement from queue
    delete( _move );
    _move = NULL;
    add_cooldown( s->cooldown );
    _is_casting = false;
    _is_executing = true;
}

bool Creature::has_ailment()
{
    return !_ail_statuses.empty();
}

void Creature::remove_finished_ailment()
{
    for( size_t i = 0; i < _ail_statuses.size(); ) {
        StatusAilments* sa = _ail_statuses[i];
        if( sa->is_done() ) {
            cout << print_name() << " is freed from Ailment: " << sa->get_status_name() << endl;
            _ail_statuses.erase( _ail_statuses.begin()+i );
            delete( sa );
        } else {
            i++;
        }
    }
}

void Creature::remove_all_ailments()
{
    for( size_t i = 0; i < _ail_statuses.size(); ) {
        StatusAilments* sa = _ail_statuses[i];
        cout << print_name() << " is freed from Ailment: " << sa->get_status_name() << endl;
        _ail_statuses.erase( _ail_statuses.begin()+i );
        delete( sa );
    }
}

void Creature::remove_finished_buff()
{
    for( size_t i = 0; i < _buff_statuses.size(); ) {
        StatusBuff* sb = _buff_statuses[i];
        if( sb->is_done() ) {
            cout << print_name() << " Buff is finished: " << sb->get_status_name() << endl;
            _buff_statuses.erase( _buff_statuses.begin()+i );
            delete( sb );
        } else {
            i++;
        }
    }
}

void Creature::apply_ailment_effects()
{
    for( StatusAilments* sa : _ail_statuses ) {
        switch( sa->ailment ) {
        case StatusAilments::POISON:
            if( sa->is_tick() ) {
                receive_damage( StatusAilments::POISON_LOST_HP_PERCENTAGE_PER_TICK * _max_hp / 100 );
            }
            break;

        default:
            break;
        }
    }
}

void Creature::move()
{
    if( !is_alive() ) {
        return;
    }

    if( _move != NULL ) {
        if( _move->is_casted() ) {
            _scb = new SkillCastedBanner( _sprite->renderer, _move->get_skill()->name,
                                          _sprite->pos_x, _sprite->pos_y, _sprite->width );
            execute_move();
        }
    }

    remove_finished_ailment();
    remove_finished_buff();
    apply_ailment_effects();
}

void Creature::receive_damage( int dmg )
{
    if( is_alive() ) {
        if( !_buff_statuses.empty() ) {
            for( StatusBuff* sb : _buff_statuses ) {
                switch( sb->buff ) {
                case StatusBuff::BARRIER:
                    dmg -= (double) dmg * StatusBuff::BARRIER_REDUCE_PERCENTAGE / 100;
                    break;

                default:
                    break;
                }
            }
        }

        _hp = (_hp - dmg < 0) ? 0 : _hp - dmg;
    }
}

void Creature::receive_healing( int heal )
{
    if( is_alive() ) {
        _hp = (_hp + heal > _max_hp) ? _max_hp : _hp + heal;
    }
}

void Creature::break_cast()
{
    _is_casting = false;
    if( _move != NULL ) {
        cout << print_name() << _move->get_skill()->name
             << " is interrupted!" << endl;

        add_cooldown( _move->get_skill()->cooldown / 2 );
        delete( _move );
        _move = NULL;
    }
}

string Creature::print_name()
{
    return "[" + _name + "]:";
}

bool Creature::is_slowed()
{
    for( StatusAilments* sa : _ail_statuses ) {
        if( sa->ailment == StatusAilments::SLOW ) {
            return true;
        }
    }
    return false;
}

bool Creature::has_reflect_shield()
{
    for( StatusBuff* sb : _buff_statuses ) {
        if( sb->buff == StatusBuff::REFLECT ) {
            return true;
        }
    }
    return false;
}

bool Creature::is_agility_up()
{
    for( StatusBuff* sb : _buff_statuses ) {
        if( sb->buff == StatusBuff::AGILITY_UP ) {
            return true;
        }
    }
    return false;
}

bool Creature::is_concentrated()
{
    for( StatusBuff* sb : _buff_statuses ) {
        if( sb->buff == StatusBuff::CONCENTRATED ) {
            return true;
        }
    }
    return false;
}

void Creature::add_cooldown( long cooldown )
{
    if( is_slowed() ) {
        long add_cooldown = cooldown * double(StatusAilments::SLOW_ADD_COOLDOWN_PERCENTAGE) / 100;
        if( add_cooldown < StatusAilments::SLOW_MIN_ADD_COOLDOWN_MS ) {
            cooldown += StatusAilments::SLOW_MIN_ADD_COOLDOWN_MS;
        } else {
            cooldown += add_cooldown;
        }
    }

    if( is_agility_up() ) {
        cooldown -= (double) cooldown * StatusBuff::AGILITY_UP_REDUCE_PERCENTAGE / 100;
     }

    _cooldown = ( _cooldown > SDL_GetTicks() ) ? _cooldown + cooldown : SDL_GetTicks() + cooldown;
}

void Creature::play_casting_sound()
{
    static Mix_Chunk* _casting_sound;

    if( _casting_sound == NULL ) {
        _casting_sound = Mix_LoadWAV( CASTING_SOUND_EFFECT_PATH.c_str() );
    }

    Mix_PlayChannel( -1, _casting_sound, 0 );
}

void Creature::play_basic_attack_sound()
{
    static Mix_Chunk* _casting_sound;

    if( _casting_sound == NULL ) {
        _casting_sound = Mix_LoadWAV( BASIC_ATTACK_SOUND_EFFECT_PATH.c_str() );
    }

    Mix_PlayChannel( -1, _casting_sound, 0 );
}

void Creature::pause()
{
    _is_pause = true;
    _pause_time = SDL_GetTicks();

    if( _move != NULL ) {
        _move->pause();
    }

    for( StatusAilments* sa : _ail_statuses ) {
        sa->pause();
    }

    for( StatusAilments* sa : _ail_statuses ) {
        sa->pause();
    }

    for( StatusBuff* sb : _buff_statuses ) {
        sb->pause();
    }
}

void Creature::unpause()
{
    _is_pause = false;
    _cooldown += (SDL_GetTicks() - _pause_time);

    if( _move != NULL ) {
        _move->unpause();
    }

    for( StatusAilments* sa : _ail_statuses ) {
        sa->unpause();
    }

    for( StatusBuff* sb : _buff_statuses ) {
        sb->unpause();
    }
}
