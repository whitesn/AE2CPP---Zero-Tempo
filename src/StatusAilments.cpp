#include "StatusAilments.h"

bool StatusAilments::_is_icon_loaded = false;
map< StatusAilments::Ailment, SDL_Texture* > StatusAilments::Ailment_Icons;

StatusAilments::StatusAilments( Ailment a )
{
    ailment = a;

    int* range = ailment_range_duration( a );
    _duration = SDL_GetTicks() + (rand() % range[1] + range[0]) * 1000;
    _next_tick = SDL_GetTicks() + 1000;
    _is_pause = false;

    delete [] range;
}

StatusAilments::~StatusAilments()
{
    // destruct ailment icons
}

int StatusAilments::get_second_duration()
{
    if( _is_pause ) {
        return (_duration - _pause_time) / 1000;
    } else {
        return (_duration - SDL_GetTicks()) / 1000;
    }
}

bool StatusAilments::is_done()
{
    if( _is_pause ) {
        return false;
    } else {
        return _duration <= (long) SDL_GetTicks();
    }
}

bool StatusAilments::is_tick()
{
    bool is_ticked;

    if( _is_pause ) {
        is_ticked = false;
    } else {
        is_ticked = _next_tick <= (long) SDL_GetTicks();
    }

    if( is_ticked ) {
        _next_tick += 1000;
    }

    return is_ticked;
}

string StatusAilments::get_status_name()
{
    return get_status_name( ailment );
}

string StatusAilments::get_status_duration_seconds( Ailment a )
{
    ostringstream r1, r2;
    string duration;

    int* range = ailment_range_duration( a );

    r1 << floor((double) range[0] * 100.00 + 0.5) / 100.00;
    r2 << floor((double) range[1] * 100.00 + 0.5) / 100.00;

    duration += r1.str();
    duration += "~";
    duration += r2.str();
    return duration;
}

string StatusAilments::get_status_name( Ailment a )
{
    static map< Ailment, string > STATUS_NAMES;
    if( STATUS_NAMES.empty() )
    {
        STATUS_NAMES[SLOW] = "SLOW";
        STATUS_NAMES[POISON] = "POISON";
        STATUS_NAMES[FREEZE] = "FREEZE";
        STATUS_NAMES[NONE] = "";
    }

    string s = "";

    if( !(STATUS_NAMES.find(a) == STATUS_NAMES.end()) ) {
        s = STATUS_NAMES[a];
    }

    return s;
}

int* StatusAilments::ailment_range_duration( Ailment a )
{
    static map< Ailment, int > MIN_DURATION;
    static map< Ailment, int > MAX_DURATION;

    if( MIN_DURATION.empty() )
    {
        MIN_DURATION[SLOW] = 12;
        MIN_DURATION[POISON] = 4;
        MIN_DURATION[FREEZE] = 6;
    }

    if( MAX_DURATION.empty() )
    {
        MAX_DURATION[SLOW] = 20;
        MAX_DURATION[POISON] = 8;
        MAX_DURATION[FREEZE] = 12;
    }

    int* range = new int[2];
    range[0] = (!(MIN_DURATION.find(a) == MIN_DURATION.end())) ? MIN_DURATION[a] : AIL_MIN_DURATION_DEFAULT;
    range[1] = (!(MAX_DURATION.find(a) == MAX_DURATION.end())) ? MAX_DURATION[a] : AIL_MAX_DURATION_DEFAULT;

    return range;
}


SDL_Texture* StatusAilments::get_ailment_sprite( SDL_Renderer* r )
{
    return get_ailment_sprite( ailment, r );
}

SDL_Texture* StatusAilments::get_ailment_sprite( Ailment a, SDL_Renderer* r )
{
    if( !_is_icon_loaded ) {
        Ailment_Icons[SLOW] = Helper::load_texture( r, "sprites/ailments/slow.png" );
        Ailment_Icons[FREEZE] = Helper::load_texture( r, "sprites/ailments/freeze.png" );
        Ailment_Icons[POISON] = Helper::load_texture( r, "sprites/ailments/poison.png" );
        _is_icon_loaded = true;
    }

    return Ailment_Icons[a];
}

void StatusAilments::pause()
{
    _is_pause = true;
    _pause_time = SDL_GetTicks();
}

void StatusAilments::unpause()
{
    _is_pause = false;
    _duration += (SDL_GetTicks() - _pause_time);
    _next_tick += (SDL_GetTicks() - _pause_time);
}
