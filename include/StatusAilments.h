#ifndef STATUSAILMENTS_H
#define STATUSAILMENTS_H

#include <SDL.h>
#include <sstream>
#include <random>
#include <map>
#include "Helper.h"

using namespace std;

class StatusAilments
{
    public:
        enum Ailment { NONE, SLOW, POISON, FREEZE, COUNT };
        StatusAilments( Ailment a );
        virtual ~StatusAilments();
        Ailment ailment;
        bool is_done();
        bool is_tick(); // 1 tick per 1000ms
        int get_second_duration();
        string get_status_name();
        static string get_status_duration_seconds( Ailment a );
        static string get_status_name( Ailment a );
        SDL_Texture* get_ailment_sprite( SDL_Renderer* r );
        void pause();
        void unpause();

        static const int AIL_MIN_DURATION_DEFAULT = 5; // sec(s)
        static const int AIL_MAX_DURATION_DEFAULT = 15; // sec(s)
        static const int SLOW_MIN_ADD_COOLDOWN_MS = 3000; // ms
        static const int SLOW_ADD_COOLDOWN_PERCENTAGE = 50;
        static const int POISON_LOST_HP_PERCENTAGE_PER_TICK = 3;

    protected:

    private:
        long _duration;
        long _next_tick;
        bool _is_pause;
        long _pause_time;
        static map< Ailment, SDL_Texture* > Ailment_Icons;
        static bool _is_icon_loaded;
        static int* ailment_range_duration( Ailment a );
        static SDL_Texture* get_ailment_sprite( Ailment a, SDL_Renderer* r );
};

#endif // STATUSAILMENTS_H
