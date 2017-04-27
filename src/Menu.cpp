#include "Menu.h"

Menu::Menu( SDL_Renderer* renderer, TargetSelection* ts, vector<Character*> characters,
            int menu_box_x, int menu_box_y, int screen_width, int screen_height )
{
    _renderer = renderer;
    _ts = ts;
    _active_selection = 0;
    _active_menu = MAIN_MENU;
    _is_active = false;
    _active_character = NULL;
    _characters = characters;

    load_texture();

    MENU_BOX_X = menu_box_x + LEFT_MARGIN;
    MENU_BOX_Y = menu_box_y;
    MENU_BOX_WIDTH = (double) MENU_BOX_RELATIVE_WIDTH / 100 * screen_width;
    MENU_BOX_HEIGHT = (double) MENU_BOX_RELATIVE_HEIGHT / 100 * screen_height;
}

Menu::~Menu()
{
    SDL_DestroyTexture( _texture );
    SDL_DestroyTexture( _t_pointer );
    TTF_CloseFont( _font );
}

void Menu::load_texture() {
    _texture = Helper::load_texture( _renderer, MENU_BOX_PATH );
    _t_pointer = Helper::load_texture( _renderer , MENU_POINTER_PATH );

    _font = TTF_OpenFont( MENU_FONT_PATH.c_str(), MENU_TEXT_SIZE );
    if( _font == NULL ) {
        Helper::error();
    }
    _text_color = { 255, 255, 255, 100 };

    SDL_QueryTexture( _texture, NULL, NULL, &MENU_BOX_ORI_WIDTH, &MENU_BOX_ORI_HEIGHT );
}

void Menu::generate_text( string text, int line ) {

    SDL_Rect cropper, opt;

    SDL_Surface* text_surface = TTF_RenderText_Blended( _font, text.c_str(), _text_color );
    if( text_surface == NULL ) {
        Helper::error();
    }

    SDL_Texture* t = SDL_CreateTextureFromSurface( _renderer, text_surface );
    if( t == NULL ) {
        Helper::error();
    }

    cropper = { 0, 0, text_surface->w, text_surface->h };
    int text_pos_x = MENU_BOX_X + LEFT_PADDING;
    int text_pos_y = MENU_BOX_Y + text_surface->h + (MENU_MARGIN * line);
    opt = { text_pos_x, text_pos_y, text_surface->w, text_surface->h };
    SDL_RenderCopy( _renderer, t, &cropper, &opt );

    if( _active_selection % SELECTION_PER_PAGE == line ) {
        int pt_w, pt_h;
        SDL_QueryTexture( _t_pointer, NULL, NULL, &pt_w, &pt_h );
        cropper = { 0, 0, pt_w, pt_h };
        opt = { Helper::get_left_margin_pos(POINTER_MARGIN, text_pos_x, pt_w),
                Helper::get_centered_vertical_pos(text_pos_y, pt_h, text_surface->h),
                pt_w, pt_h };
        SDL_RenderCopy( _renderer, _t_pointer, &cropper, &opt );
    }

    SDL_FreeSurface( text_surface );
    SDL_DestroyTexture( t );
}

string Menu::get_status_ailment_tag( Skill* s )
{
    string tag = "";
    ostringstream ail_chance;

    ail_chance << s->status_ailment_chance;

    if( s->status_ailment != StatusAilments::NONE ) {
        tag = "[ " + StatusAilments::get_status_name(s->status_ailment) + " ("+
              StatusAilments::get_status_duration_seconds(s->status_ailment) + "s) "+
              ail_chance.str() +"% ]";
    }

    return tag;
}

string Menu::get_cast_breaking_tag( Skill* s )
{
    string tag = "";

    if( s->is_cast_breaking ) {
        tag += "[CAST-BREAKING]";
    }

    return tag;
}

void Menu::render()
{
    SDL_Rect cropper, opt;

    cropper = { 0, 0, MENU_BOX_ORI_WIDTH, MENU_BOX_ORI_HEIGHT
     };
    opt = { MENU_BOX_X, MENU_BOX_Y, MENU_BOX_WIDTH, MENU_BOX_HEIGHT };
    SDL_RenderCopy( _renderer, _texture, &cropper, &opt );

    if( _active_character != NULL && _active_menu == MAIN_MENU ) {
        for( Uint8 i = 0; i < sizeof(MAIN_MENU_LIST)/sizeof(string); i++ ) {
            generate_text( MAIN_MENU_LIST[i], i );
        }
    } else if( _active_character != NULL && _active_menu == SKILL_MENU ) {

        int _active_page = _active_selection / SELECTION_PER_PAGE;

        for( int i = 0; i < SELECTION_PER_PAGE; i++ ) {
            int skill_index = i + (_active_page*SELECTION_PER_PAGE);
            if( skill_index >= _active_character->get_skill_count() ) {
                break;
            }
            Skill* s = _active_character->get_skill(skill_index);
            generate_text( s->name + " " + get_status_ailment_tag(s) + get_cast_breaking_tag(s), i );
        }
    }
}

void Menu::reset_menu() {
    _active_character = NULL;
    _is_active = false;
    _ts->is_basic_attack = false;
    _active_selection = 0;
    _active_menu = MAIN_MENU;
    _ts->reset_selection();
}

void Menu::execute_main_menu( int selection ) {

    string cmd = MAIN_MENU_LIST[selection];

    if( cmd == "BASIC ATTACK" ) {
        _active_menu = SELECTION_MENU;
        _ts->is_basic_attack = true;
        _ts->activate_target_selection( NULL );
    } else if( cmd == "SKILL" ) {
        _active_menu = SKILL_MENU;
        _active_selection = 0;
    }
}

void Menu::execute_active_selection()
{
    switch( _active_menu ) {
    case MAIN_MENU:
        execute_main_menu( _active_selection );
        break;

    case SKILL_MENU:
        if( _active_character->get_skill(_active_selection)->is_self_cast ) {
            vector<Creature*> target { _active_character };
            _active_character->skill( _active_selection, target );
            reset_menu();
        } else {
            _active_menu = SELECTION_MENU;
            _ts->activate_target_selection( _active_character->get_skill(_active_selection) );
        }
        break;

    case SELECTION_MENU:
        vector<Creature*> target = _ts->get_pointed_creature();
        if( _ts->is_basic_attack ) {
            _active_character->basic_attack( target[0] );
        } else {
            _active_character->skill( _active_selection, target );
        }
        reset_menu();
        break;
    }
}

void Menu::navigate_back_action() {
    if( _active_menu == SKILL_MENU || _active_menu == SELECTION_MENU ) {
        _active_selection = 0;
        _active_menu = MAIN_MENU;
        _ts->reset_selection();
    }
}

void Menu::handle_events( SDL_Event e ) {
    switch( e.key.keysym.sym )
    {
        case SDLK_UP:
            if( _active_menu == SELECTION_MENU ) {
                _ts->point_previous();
            } else {
                _active_selection--;
            }
        break;

        case SDLK_DOWN:
            if( _active_menu == SELECTION_MENU ) {
                _ts->point_next();
            } else {
                _active_selection++;
            }
        break;

        case SDLK_z:
            execute_active_selection();
        break;

        case SDLK_x:
            navigate_back_action();
        break;

        case SDLK_c:
            switch_next_active_character();
        break;

        default:
        break;
    }

    if( _active_menu == MAIN_MENU ) {
        if( _active_selection > (int) (sizeof(MAIN_MENU_LIST) / sizeof(string)) - 1 ) {
            _active_selection = 0;
        } else if( _active_selection < 0 ) {
            _active_selection = 1;
        }
    } else if( _active_menu == SKILL_MENU ) {
        if( _active_selection >= _active_character->get_skill_count() ) {
            _active_selection = 0;
        } else if( _active_selection < 0 ) {
            _active_selection = _active_character->get_skill_count() - 1;
        }
    }
}

bool Menu::is_active() {
    return _is_active;
}

Character* Menu::get_active_character() {
    return _active_character;
}

void Menu::set_active_character(Character* c)
{
    _active_character = c;
    _is_active = true;
}

void Menu::update_active_character()
{
    if( _is_active && ( !(_active_character->is_ready()) || !(_active_character->is_alive()) ) ) {
        reset_menu();
    }

    if( !_is_active ) {
        for( Character* c : _characters ) {
            if( c->is_alive() && c->is_ready() ) {
                cout << "Choose movement for character: " << c->get_name() << endl;
                set_active_character( c );
                break;
            }
        }
    }
}

void Menu::switch_next_active_character()
{
    if( _active_character != NULL ) {

        Uint8 index;

        for( Uint8 i = 0; i < _characters.size(); i++ ) {
            if( _characters[i] == _active_character ) {
                index = i;
                break;
            }
        }

        while( true ) {

            if( ++index >= _characters.size() ) {
                index = 0;
            }

            Character* c = _characters[index];

            if( c == _active_character ) {
                break;
            }

            if( c != _active_character && c->is_ready() && c->is_alive() ) {
                reset_menu();
                cout << "Active Characters switched to " << c->get_name() << endl;
                set_active_character( c );
                break;
            }
        }
    }
}
