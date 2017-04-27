#ifndef PARTYSTATUSBOX_H
#define PARTYSTATUSBOX_H

#include <SDL_ttf.h>
#include <math.h>
#include <string>
#include "Character.h"

using namespace std;

const string PARTY_STATUS_BOX_PATH = "sprites/party_status_box.png";
const string PARTY_STATUS_BOX_FONTS_PATH = "fonts/segoeuib.ttf";

const int PARTY_STATUS_BOX_SCREEN_MARGIN = 10; // pixel
const int PARTY_STATUS_BOX_TEXT_SIZE = 32; // px

const int PARTY_STATUS_BOX_NAME_BAR_MARGIN = 4; // pixel
const int PARTY_STATUS_BOX_DESC_MARGIN = 10; // pixel

const int NAME_ICON_MARGIN = 10; // pixels
const int STATUS_ICON_PARTY_BOX_MARGIN = 6; // pixels
const int AIL_BUFF_STATUS_ICON_MARGIN = 15; // pixels

// Character Block Configuration
const int PARTY_STATUS_BOX_NAME_HEIGHT = 40; // percent
const int PARTY_STATUS_BOX_BAR_HEIGHT = 30; // percent

const int PARTY_STATUS_BOX_BAR_WIDTH = 70; // percent
// =========================================

const int PARTY_STATUS_BOX_DESC_WIDTH = 30; // percent
const int PARTY_STATUS_BOX_RELATIVE_WIDTH = 35; // percent
const int PARTY_STATUS_BOX_RELATIVE_HEIGHT = 28; // percent

const int CHAR_BLOCK_WIDTH = 90; // percent
const int CHAR_BLOCK_HEIGHT = 30; // percent

class PartyStatusBox
{
    public:
        PartyStatusBox( SDL_Renderer* r, vector<Character*> characters,
                        int window_width, int window_height );
        virtual ~PartyStatusBox();
        void render( Character* character );
        int PARTY_STATUS_BOX_X;
        int PARTY_STATUS_BOX_Y;
        int PARTY_STATUS_BOX_WIDTH;
        int PARTY_STATUS_BOX_HEIGHT;
        int PARTY_STATUS_BOX_ORI_WIDTH;
        int PARTY_STATUS_BOX_ORI_HEIGHT;

    protected:
    private:
        SDL_Renderer* _renderer;
        SDL_Texture* _bg;
        vector<Character*> _characters;
        TTF_Font* _font;

        SDL_Color _text_color;
        SDL_Color _cur_hp_color;
        SDL_Color _cur_low_hp_color;
        SDL_Color _cur_cooldown_color;
        SDL_Color _base_bg_color;

        void load_texture();
        void add_name_label( Character* c, int block_height, bool is_active, int* pos_y );
        void add_hp_block( Character* c, int block_width, int block_height, int l_posy, int* pos_y );
        void add_cd_block( Character* c, int block_width, int block_height, int hp_posy );
};

#endif // PARTYSTATUSBOX_H
