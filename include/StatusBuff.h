#ifndef STATUSBUFF_H
#define STATUSBUFF_H

#include <SDL.h>
#include <string>
#include <map>
#include "Helper.h"

using namespace std;

class StatusBuff
{
    public:
        enum Buff { NONE, BARRIER, REFLECT, AGILITY_UP, CONCENTRATED, RECOVERY };
        StatusBuff( Buff b );
        virtual ~StatusBuff();
        Buff buff;
        bool is_done();
        string get_status_name();
        int get_second_duration();
        static string get_status_name( Buff b );
        SDL_Texture* get_buff_sprite( SDL_Renderer* r );
        void pause();
        void unpause();

        static const int BUFF_DEFAULT_DURATION = 0;
        static const int BARRIER_REDUCE_PERCENTAGE = 50;
        static const int AGILITY_UP_REDUCE_PERCENTAGE = 50;
        static const int REFLECT_RETURN_DAMAGE_PERCENTAGE = 50;
        static const int CONCENTRATED_ADD_DAMAGE_PERCENTAGE = 80;
        static int get_second_duration( Buff b );

    protected:

    private:
        unsigned long _duration;
        bool _is_pause;
        long _pause_time;
        static bool _is_icon_loaded;
        static map< Buff, SDL_Texture* > Buff_Icons;
        static SDL_Texture* get_buff_sprite( Buff b, SDL_Renderer* r );
};

#endif // STATUSBUFF_H
