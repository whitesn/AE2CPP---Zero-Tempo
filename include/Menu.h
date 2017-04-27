#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Helper.h"
#include "Character.h"
#include "TargetSelection.h"

const string MENU_BOX_PATH = "sprites/menu_box.png";
const string MENU_POINTER_PATH = "sprites/menu_pointer.png";
const string MENU_FONT_PATH = "fonts/segoeuib.ttf";

const int TOP_PADDING = 45;
const int LEFT_PADDING = 70;
const int MENU_MARGIN = 50;
const int POINTER_MARGIN = 14;
const int SELECTION_PER_PAGE = 3;

const int MENU_TEXT_SIZE = 32;

const int LEFT_MARGIN = 15;

const int MENU_BOX_RELATIVE_WIDTH = 60; // percent
const int MENU_BOX_RELATIVE_HEIGHT = 28; // percent

const string MAIN_MENU_LIST[] = {
    "BASIC ATTACK",
    "SKILL"
};

const int MAIN_MENU = 0;
const int SKILL_MENU = 1;
const int SELECTION_MENU = 2;

using namespace std;

class Menu
{
    public:
        Menu( SDL_Renderer* renderer, TargetSelection* ts, vector<Character*> characters,
              int menu_box_x, int menu_box_y, int screen_width, int screen_height );
        virtual ~Menu();
        void render();
        void handle_events( SDL_Event e );
        void set_active_character( Character* c );
        bool is_active();
        Character* get_active_character();
        void update_active_character();
        void reset_menu();
        int MENU_BOX_WIDTH;
        int MENU_BOX_HEIGHT;
        int MENU_BOX_ORI_WIDTH;
        int MENU_BOX_ORI_HEIGHT;
        int MENU_BOX_X;
        int MENU_BOX_Y;

    protected:
    private:
        SDL_Renderer* _renderer;
        SDL_Texture* _texture;
        SDL_Texture* _t_pointer;
        SDL_Color _text_color;
        TTF_Font* _font;
        TargetSelection* _ts;

        Character* _active_character;
        vector<Character*> _characters;

        int _active_selection;
        int _active_menu;
        bool _is_active;

        void generate_text( string text, int line );
        void load_texture();
        void execute_active_selection();
        void execute_main_menu( int selection );
        void navigate_back_action();
        void switch_next_active_character();
        string get_cast_breaking_tag( Skill* s );
        string get_status_ailment_tag( Skill* s );
};

#endif // MENU_H
