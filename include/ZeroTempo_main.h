#ifndef ZEROTEMPO_MAIN_H
#define ZEROTEMPO_MAIN_H

#include <iostream>
#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <random>
#include <time.h>
#include "Sprite.h"
#include "Map.h"
#include "Menu.h"
#include "Helper.h"
#include "PartyStatusBox.h"
#include "Character.h"
#include "Monster.h"
#include "TargetSelection.h"
#include "StatusAilments.h"

class MainWindow;

// Window Configurations
const string WINDOW_TITLE = "Zero Tempo";

// How many creatures in  a party
const int MAX_PARTY_NUMBERS = 3;

// Creatures Positioning (%)
const int POS_CREATURES_Y = 8;
const int CREATURES_MARGIN = 20;

// Monster Position X (%)
const int POS_MONSTERS_X = 25;

// Characters Configurations (%)
const int POS_CHARACTERS_X = 70;

const string KNIGHT_NAME = "Loki";
const int KNIGHT_MAX_HP = 4700;
const int KNIGHT_INITIAL_COOLDOWN = 1800;
const int KNIGHT_ATK = 45;
const int KNIGHT_DEF = 60;
const int SPRITE_KNIGHT_FRAMES = 6;
const int SPRITE_KNIGHT_ACTION_FRAMES = 7;
const string SPRITE_KNIGHT_PATH = "sprites/knight/knight.png";
const string SPRITE_KNIGHT_ACTION_PATH = "sprites/knight/knight_action.png";
const string SPRITE_KNIGHT_DEAD = "sprites/knight/knight_dead.png";

const string WIZARD_NAME = "Ares";
const int WIZARD_MAX_HP = 2500;
const int WIZARD_INITIAL_COOLDOWN = 3500;
const int WIZARD_ATK = 70;
const int WIZARD_DEF = 20;
const int SPRITE_WIZARD_FRAMES = 6;
const int SPRITE_WIZARD_ACTION_FRAMES = 5;
const string SPRITE_WIZARD_PATH = "sprites/wizard/wizard.png";
const string SPRITE_WIZARD_ACTION_PATH = "sprites/wizard/wizard_action.png";
const string SPRITE_WIZARD_DEAD = "sprites/wizard/wizard_dead.png";

const string PRIEST_NAME = "Iris";
const int PRIEST_MAX_HP = 3800;
const int PRIEST_INITIAL_COOLDOWN = 2800;
const int PRIEST_ATK = 40;
const int PRIEST_DEF = 48;
const int SPRITE_PRIEST_FRAMES = 6;
const int SPRITE_PRIEST_ACTION_FRAMES = 5;
const string SPRITE_PRIEST_PATH = "sprites/priest/priest.png";
const string SPRITE_PRIEST_ACTION_PATH = "sprites/priest/priest_action.png";
const string SPRITE_PRIEST_DEAD = "sprites/priest/priest_dead.png";
/* ============================= */

// Map Configurations
const string MAP_PATH = "sprites/map.png";

// Target Selector Configurations
const string TARGET_SELECTOR_POINTER_PATH = "sprites/selector_pointer.png";

// Sound Paths
const string BG_MUSIC_PATH = "audio/battle_music.mp3";
const string SOUND_EFFECT_PATH = "audio/skills/";

// Texts
const string MAIN_SCREEN_FONT_PATH = "fonts/segoeuib.ttf";
const int GAME_OVER_TEXT_SIZE = 32;

using namespace std;

class ZeroTempo_main
{
    public:
        enum LEVEL { HARD, HARDER, HARDEST, IMPOSSIBLE };
        enum CLASSES { KNIGHT, WIZARD, PRIEST };
        enum MONSTER { BANSHEE, THANATOS, DRACULA };
        enum SKILL_DEFS { BASH, QUICK_ATTACK, HEAVY_DROP, PROVOKE,
                          FROST_BOLT, DISPEL, CYCLONE, MEDITATE,
                          HEAL, SANCTUARY, BARRIER, VENOM_SLASH,
                          HEAVY_GRAVITY, CURSED_FIRE, MAGNETIC_FIELD,
                          SKYNET_BLOW, JACK_FROST, LEX_DIVINA, REFLECT_SHIELD,
                          RECOVERY, STATIC_LIGHTNING, TETRA_VORTEX, METEOR,
                          DECREASE_AGILITY, INCREASE_AGILITY, SONIC_BLOW };

        ZeroTempo_main();
        virtual ~ZeroTempo_main();
        void init();
        void main_window();
        void load_media();
        void load_monsters( LEVEL level );
        void start_game();
        void close();
        bool running();
        typedef StatusAilments::Ailment Ailment;
        typedef StatusBuff::Buff Buff;
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;

    protected:
    private:
        bool _quit;
        bool _game_over;
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        Map* _map;
        Menu* _menu;
        PartyStatusBox* _psb;
        TargetSelection* _ts;
        Mix_Music* _bg_music;

        vector<Character*> _characters;
        vector<Monster*> _monsters;

        void initialize_skills_map();
        void initialize_character_skills();
        void load_monster_db();

        void initialize_characters();
        void initialize_monsters( MONSTER* ms, int num );

        void reload_objects();
        void game_handling();
        void render_blackout_screen( string text );
        void game_over();
        bool exists_alive_character();
        bool exists_alive_monster();
        void reset_creatures();
        void free_monsters();

        map< SKILL_DEFS, Skill* > SKILL_MAPS;
        map< CLASSES, vector<SKILL_DEFS> > CHARACTER_SKILLS;

        map< MONSTER, int > M_IDLE_FRAME_COUNTS;
        map< MONSTER, int > M_ACTION_FRAME_COUNTS;
        map< MONSTER, string > M_SPRITE_PATH;
        map< MONSTER, string > M_ACTION_SPRITE_PATH;
        map< MONSTER, string > M_DEAD_SPRITE_PATH;
        map< MONSTER, string > M_NAMES;
        map< MONSTER, int > M_HP;
        map< MONSTER, int > M_INIT_CD;
        map< MONSTER, int > M_ATK;
        map< MONSTER, int > M_DEF;
        map< MONSTER, vector<SKILL_DEFS> > M_SKILLS;

};

#endif // ZEROTEMPO_MAIN_H
