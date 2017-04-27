#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <random>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Skill.h"
#include "Sprite.h"
#include "ActionSprite.h"
#include "Move.h"
#include "CastingBar.h"
#include "SkillCastedBanner.h"

using namespace std;

const int BASIC_ATTACK_DMG = 6;
const int BASIC_ATTACK_COOLDOWN = 5000; // ms
const int CAST_BREAKING_CHANCE = 80; // percent (/100)
const string CASTING_SOUND_EFFECT_PATH = "audio/casting.wav";
const string BASIC_ATTACK_SOUND_EFFECT_PATH = "audio/basic_attack.wav";

const int COOLDOWN_BAR_MAX_MS = 15000;
const int LOW_HP_PERCENTAGE = 20;

class Creature
{
    public:
        Creature();
        Creature( string name, int max_hp, int initial_cooldown, int atk,
                  int def, Sprite* sprite, ActionSprite* action_sprite,
                  SDL_Texture* dead_texture );
        virtual ~Creature();
        void set_name( string name );
        void set_hp( int hp );
        void set_max_hp( int max_hp );
        void set_atk( int atk );
        void set_def( int def );
        void add_buff_status( StatusBuff* buff_status );
        void add_ail_status( StatusAilments* ail_status );
        void add_skill( Skill* new_skill );
        void set_sprite( Sprite* sprite );
        void set_action_sprite( ActionSprite* sprite );

        string get_name();
        int get_hp();
        int get_max_hp();
        long get_cooldown();
        int get_atk();
        int get_def();
        vector<StatusAilments*> get_ail_statuses();
        vector<StatusBuff*> get_buff_statuses();

        bool is_casting();
        bool is_alive();
        Skill* get_skill( int index );
        int get_skill_count();
        Sprite* get_sprite();
        bool is_ready();
        virtual void render();
        void basic_attack( Creature* target );
        void skill( int skill_index, vector<Creature*> target );
        void move();
        void receive_damage( int dmg );
        void receive_healing( int heal );
        void break_cast();
        string print_name();
        void reset_state();

        void pause();
        void unpause();

    protected:
    private:
        string _name;
        int _hp;
        int _max_hp;
        unsigned long _cooldown;
        unsigned long _initial_cooldown;
        int _atk;
        int _def;
        vector<StatusBuff*> _buff_statuses;
        vector<StatusAilments*> _ail_statuses;
        vector<Skill*> _skills;
        Sprite* _sprite;
        ActionSprite* _action_sprite;
        SDL_Texture* _dead_texture;

        bool _is_casting;
        bool _is_executing;
        bool _is_pause;
        long _pause_time;
        Move* _move;
        SkillCastedBanner* _scb;

        void execute_move();

        bool has_ailment();
        bool is_slowed();
        bool is_frozen();

        bool is_agility_up();
        bool is_concentrated();
        bool has_reflect_shield();

        void add_cooldown( long ms );
        void remove_finished_ailment();
        void remove_finished_buff();
        void apply_ailment_effects();
        void remove_all_ailments();

        static void play_casting_sound();
        static void play_basic_attack_sound();
};

#endif // CREATURE_H
