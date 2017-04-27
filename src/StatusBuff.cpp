#include "StatusBuff.h"

bool StatusBuff::_is_icon_loaded = false;
map< StatusBuff::Buff, SDL_Texture* > StatusBuff::Buff_Icons;

StatusBuff::StatusBuff( Buff b )
{
    buff = b;
    _duration = SDL_GetTicks() + get_second_duration( b ) * 1000;
    _is_pause = false;
}

StatusBuff::~StatusBuff()
{
    //dtor
}

bool StatusBuff::is_done()
{
    if( _is_pause ) {
        return false;
    } else {
        return _duration <= SDL_GetTicks();
    }
}


string StatusBuff::get_status_name()
{
    return get_status_name( buff );
}

string StatusBuff::get_status_name( Buff b )
{
    static map< Buff, string > BUFF_NAMES;
    if( BUFF_NAMES.empty() )
    {
        BUFF_NAMES[REFLECT] = "REFLECT";
        BUFF_NAMES[BARRIER] = "BARRIER";
        BUFF_NAMES[AGILITY_UP] = "AGILITY UP";
        BUFF_NAMES[CONCENTRATED] = "CONCENTRATED";
        BUFF_NAMES[RECOVERY] = "RECOVERY";
        BUFF_NAMES[NONE] = "";
    }

    string s = "";

    if( !(BUFF_NAMES.find(b) == BUFF_NAMES.end()) ) {
        s = BUFF_NAMES[b];
    }

    return s;
}

int StatusBuff::get_second_duration()
{
    return get_second_duration( buff );
}

int StatusBuff::get_second_duration( Buff b )
{

    static map< Buff, int > BUFF_DURATION;

    if( BUFF_DURATION.empty() )
    {
        BUFF_DURATION[BARRIER] = 20;
        BUFF_DURATION[REFLECT] = 10;
        BUFF_DURATION[AGILITY_UP] = 20;
        BUFF_DURATION[CONCENTRATED] = 25;
        BUFF_DURATION[RECOVERY] = 0;
    }

    int duration = (!(BUFF_DURATION.find(b) == BUFF_DURATION.end())) ? BUFF_DURATION[b] : BUFF_DEFAULT_DURATION;

    return duration;
}

SDL_Texture* StatusBuff::get_buff_sprite( SDL_Renderer* r )
{
    return get_buff_sprite( buff, r );
}

SDL_Texture* StatusBuff::get_buff_sprite( Buff b, SDL_Renderer* r )
{
    if( !_is_icon_loaded ) {
        Buff_Icons[BARRIER] = Helper::load_texture( r, "sprites/buffs/barrier.bmp" );
        Buff_Icons[REFLECT] = Helper::load_texture( r, "sprites/buffs/reflect.bmp" );
        Buff_Icons[AGILITY_UP] = Helper::load_texture( r, "sprites/buffs/agility_up.bmp" );
        Buff_Icons[CONCENTRATED] = Helper::load_texture( r, "sprites/buffs/concentrated.bmp" );
        Buff_Icons[RECOVERY] = Helper::load_texture( r, "sprites/buffs/recovery.bmp" );
        _is_icon_loaded = true;
    }

    return Buff_Icons[b];
}

void StatusBuff::pause()
{
    _is_pause = true;
    _pause_time = SDL_GetTicks();
}

void StatusBuff::unpause()
{
    _is_pause = false;
    _duration += (SDL_GetTicks() - _pause_time);
}
