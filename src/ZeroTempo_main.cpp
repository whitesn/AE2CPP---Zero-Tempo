#include "ZeroTempo_main.h"
#include "MainWindow.h"

ZeroTempo_main::ZeroTempo_main()
{
    srand( time(NULL) );
    _quit = false;
    _window = NULL;
    _renderer = NULL;
    _map = NULL;
    _menu = NULL;
    _psb = NULL;
    _ts = NULL;
    _bg_music = NULL;
}

ZeroTempo_main::~ZeroTempo_main()
{
    //dtor
}

void ZeroTempo_main::initialize_skills_map()
{
    SKILL_MAPS[BASH] = new Skill( "Bash", 20, 4000, 2000, true, false, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "sword_basic.wav" );
    SKILL_MAPS[QUICK_ATTACK] = new Skill( "Quick Attack", 20, 4000, 600, false, false, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "sword_basic.wav" );
    SKILL_MAPS[HEAVY_DROP] = new Skill( "Heavy Drop", 40, 6000, 4000, false, false, false, StatusAilments::SLOW, 80, StatusBuff::NONE, SOUND_EFFECT_PATH + "heavy_drop.wav");
    SKILL_MAPS[PROVOKE] = new Skill( "Provoke", 0, 5000, 500, false, false, false, StatusAilments::SLOW, 80, StatusBuff::NONE, SOUND_EFFECT_PATH + "provoke.wav" );
    SKILL_MAPS[FROST_BOLT] = new Skill( "Frost Bolt", 35, 6000, 5000, false, false, false, StatusAilments::FREEZE, 60, StatusBuff::NONE, SOUND_EFFECT_PATH + "frost_bolt.wav" );
    SKILL_MAPS[DISPEL] = new Skill( "Dispel", 0, 4200, 1500, true, false, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "dispel.wav" );
    SKILL_MAPS[CYCLONE] = new Skill( "Cyclone", 30, 7500, 6000, false, true, false, StatusAilments::FREEZE, 40, StatusBuff::NONE, SOUND_EFFECT_PATH + "cyclone.wav" );
    SKILL_MAPS[MEDITATE] = new Skill( "Meditate", 0, 4000, 2500, false, false, true, StatusAilments::NONE, 0, StatusBuff::CONCENTRATED, SOUND_EFFECT_PATH + "meditate.wav" );
    SKILL_MAPS[HEAL] = new Skill( "Heal", -30, 5500, 3000, false, false, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "heal.wav" );
    SKILL_MAPS[SANCTUARY] = new Skill( "Sanctuary", -25, 8000, 7200, false, true, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "sanctuary.wav" );
    SKILL_MAPS[BARRIER] = new Skill( "Barrier", 0, 4500, 3000, false, false, false, StatusAilments::NONE, 0, StatusBuff::BARRIER, SOUND_EFFECT_PATH + "barrier.wav" );
    SKILL_MAPS[VENOM_SLASH] = new Skill( "Venom Slash", 22, 5000, 2500, false, false, false, StatusAilments::POISON, 50, StatusBuff::NONE, SOUND_EFFECT_PATH + "venom_slash.wav" );
    SKILL_MAPS[HEAVY_GRAVITY] = new Skill ( "Heavy Gravity", 28, 7000, 5500, false, true, false, StatusAilments::SLOW, 50, StatusBuff::NONE, SOUND_EFFECT_PATH + "heavy_gravity.wav" );
    SKILL_MAPS[MAGNETIC_FIELD] = new Skill( "Magnetic Field", 32, 7000, 6500, true, true, false, StatusAilments::SLOW, 30, StatusBuff::NONE, SOUND_EFFECT_PATH + "magnetic_field.wav" );
    SKILL_MAPS[CURSED_FIRE] = new Skill( "Cursed Fire", 18, 7500, 6000, false, true, false, StatusAilments::POISON, 40, StatusBuff::NONE, SOUND_EFFECT_PATH + "cursed_fire.wav" );
    SKILL_MAPS[SKYNET_BLOW] = new Skill( "Skynet Blow", 28, 6000, 3800, true, false, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "skynet_blow.wav" );
    SKILL_MAPS[JACK_FROST] = new Skill( "Jack Frost", 36, 8000, 5000, false, true, false, StatusAilments::FREEZE, 30, StatusBuff::NONE, SOUND_EFFECT_PATH + "jack_frost.wav" );
    SKILL_MAPS[LEX_DIVINA] = new Skill( "Lex Divina", 0, 1500, 2800, true, false, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "lex_divina.wav" );
    SKILL_MAPS[REFLECT_SHIELD] = new Skill( "Reflect Shield", 0, 5000, 6000, false, false, false, StatusAilments::NONE, 0, StatusBuff::REFLECT, SOUND_EFFECT_PATH + "reflect_shield.wav" );
    SKILL_MAPS[RECOVERY] = new Skill( "Recovery", 0, 3000, 3000, false, false, false, StatusAilments::NONE, 0, StatusBuff::RECOVERY, SOUND_EFFECT_PATH + "recovery.wav" );
    SKILL_MAPS[STATIC_LIGHTNING] = new Skill( "Static Lightning", 30, 10000, 10000, true, true, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "static_lightning.wav" );
    SKILL_MAPS[TETRA_VORTEX] = new Skill( "Tetra Vortex", 32, 12000, 5000, false, true, false, StatusAilments::SLOW, 40, StatusBuff::NONE, SOUND_EFFECT_PATH + "tetra_vortex.wav" );
    SKILL_MAPS[METEOR] = new Skill( "Meteor", 30, 8000, 5000, false, true, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "meteor.wav" );
    SKILL_MAPS[INCREASE_AGILITY] = new Skill( "Increase Agility", 0, 4000, 4000, false, false, false, StatusAilments::NONE, 0, StatusBuff::AGILITY_UP, SOUND_EFFECT_PATH + "increase_agi.wav" );
    SKILL_MAPS[DECREASE_AGILITY] = new Skill( "Decrease Agility", 0, 5000, 5000, false, false, false, StatusAilments::SLOW, 100, StatusBuff::NONE, SOUND_EFFECT_PATH + "decrease_agi.wav" );
    SKILL_MAPS[SONIC_BLOW] = new Skill( "Sonic Blow", 38, 6500, 4500, true, false, false, StatusAilments::NONE, 0, StatusBuff::NONE, SOUND_EFFECT_PATH + "sonic_blow.wav" );
}

void ZeroTempo_main::initialize_character_skills()
{
    SKILL_DEFS knight_skills[] = { BASH, HEAVY_DROP, PROVOKE, SKYNET_BLOW, VENOM_SLASH };
    SKILL_DEFS wizard_skills[] = { FROST_BOLT, HEAVY_GRAVITY, CYCLONE, DISPEL, MEDITATE };
    SKILL_DEFS priest_skills[] = { HEAL, SANCTUARY, BARRIER, LEX_DIVINA, REFLECT_SHIELD, INCREASE_AGILITY, RECOVERY };

    CHARACTER_SKILLS[KNIGHT] = vector<SKILL_DEFS> ( knight_skills, knight_skills + sizeof(knight_skills) / sizeof(SKILL_DEFS) );
    CHARACTER_SKILLS[WIZARD] = vector<SKILL_DEFS> ( wizard_skills, wizard_skills + sizeof(wizard_skills) / sizeof(SKILL_DEFS) );
    CHARACTER_SKILLS[PRIEST] = vector<SKILL_DEFS> ( priest_skills, priest_skills + sizeof(priest_skills) / sizeof(SKILL_DEFS) );
}

void ZeroTempo_main::load_monster_db()
{
    M_IDLE_FRAME_COUNTS[BANSHEE] = 6;
    M_IDLE_FRAME_COUNTS[THANATOS] = 6;
    M_IDLE_FRAME_COUNTS[DRACULA] = 6;

    M_ACTION_FRAME_COUNTS[BANSHEE] = 5;
    M_ACTION_FRAME_COUNTS[THANATOS] = 7;
    M_ACTION_FRAME_COUNTS[DRACULA] = 6;

    M_SPRITE_PATH[BANSHEE] = "sprites/mobs/banshee/idle.png";
    M_SPRITE_PATH[THANATOS] = "sprites/mobs/thanatos/idle.png";
    M_SPRITE_PATH[DRACULA] = "sprites/mobs/dracula/idle.png";

    M_ACTION_SPRITE_PATH[BANSHEE] = "sprites/mobs/banshee/action.png";
    M_ACTION_SPRITE_PATH[THANATOS] = "sprites/mobs/thanatos/action.png";
    M_ACTION_SPRITE_PATH[DRACULA] = "sprites/mobs/dracula/action.png";

    M_DEAD_SPRITE_PATH[BANSHEE] = "sprites/mobs/banshee/dead.png";
    M_DEAD_SPRITE_PATH[THANATOS] = "sprites/mobs/thanatos/dead.png";
    M_DEAD_SPRITE_PATH[DRACULA] = "sprites/mobs/dracula/dead.png";

    M_NAMES[BANSHEE] = "Banshee";
    M_NAMES[THANATOS] = "Thanatos";
    M_NAMES[DRACULA] = "Dracula";

    M_HP[BANSHEE] = 12000;
    M_HP[THANATOS] = 13000;
    M_HP[DRACULA] = 12500;

    M_INIT_CD[BANSHEE] = 7800;
    M_INIT_CD[THANATOS] = 6000;
    M_INIT_CD[DRACULA] = 9000;

    M_ATK[BANSHEE] = 55;
    M_ATK[THANATOS] = 58;
    M_ATK[DRACULA] = 65;

    M_DEF[BANSHEE] = 45;
    M_DEF[THANATOS] = 55;
    M_DEF[DRACULA] = 45;

    M_SKILLS[BANSHEE] = { CURSED_FIRE, STATIC_LIGHTNING, INCREASE_AGILITY, DECREASE_AGILITY, HEAL };
    M_SKILLS[THANATOS] = { BASH, TETRA_VORTEX, SKYNET_BLOW, SONIC_BLOW, VENOM_SLASH };
    M_SKILLS[DRACULA] = { FROST_BOLT, JACK_FROST, MAGNETIC_FIELD, METEOR, CYCLONE };
}

void ZeroTempo_main::initialize_characters()
{
    int pos_x = (double) POS_CHARACTERS_X / 100 * WINDOW_WIDTH;
    int pos_y;

    // Knight Character
    pos_y = (double) POS_CREATURES_Y / 100 * WINDOW_HEIGHT;
    Sprite* knight_sprite = new Sprite( SPRITE_KNIGHT_FRAMES, pos_x, pos_y,
                                        SPRITE_KNIGHT_PATH, _renderer );

    ActionSprite* knight_action_sprite = new ActionSprite( SPRITE_KNIGHT_ACTION_FRAMES, pos_x, pos_y,
                                                           SPRITE_KNIGHT_ACTION_PATH, _renderer );

    SDL_Texture* knight_dead_texture = Helper::load_texture( _renderer, SPRITE_KNIGHT_DEAD );

    Character* knight = new Character( KNIGHT_NAME, KNIGHT_MAX_HP, KNIGHT_INITIAL_COOLDOWN,
                                       KNIGHT_ATK, KNIGHT_DEF, knight_sprite, knight_action_sprite, knight_dead_texture );

    for( Uint8 i = 0; i < CHARACTER_SKILLS[KNIGHT].size(); i++ ) {
        knight->add_skill(SKILL_MAPS[CHARACTER_SKILLS[KNIGHT][i]]);
    }

    // Wizard Character
    pos_y = pos_y + ((double) CREATURES_MARGIN / 100 * WINDOW_HEIGHT);
    Sprite* wizard_sprite = new Sprite( SPRITE_WIZARD_FRAMES, pos_x, pos_y,
                                        SPRITE_WIZARD_PATH, _renderer );

    ActionSprite* wizard_action_sprite = new ActionSprite( SPRITE_WIZARD_ACTION_FRAMES, pos_x, pos_y,
                                                     SPRITE_WIZARD_ACTION_PATH, _renderer );

    SDL_Texture* wizard_dead_texture = Helper::load_texture( _renderer, SPRITE_WIZARD_DEAD );

    Character* wizard = new Character( WIZARD_NAME, WIZARD_MAX_HP, WIZARD_INITIAL_COOLDOWN,
                                       WIZARD_ATK, WIZARD_DEF, wizard_sprite, wizard_action_sprite, wizard_dead_texture );

    for( Uint8 i = 0; i < CHARACTER_SKILLS[WIZARD].size(); i++ ) {
        wizard->add_skill(SKILL_MAPS[CHARACTER_SKILLS[WIZARD][i]]);
    }

    // Priest Character
    pos_y = pos_y + ((double) CREATURES_MARGIN / 100 * WINDOW_HEIGHT);
    Sprite* priest_sprite = new Sprite( SPRITE_PRIEST_FRAMES, pos_x, pos_y,
                                        SPRITE_PRIEST_PATH, _renderer );

    ActionSprite* priest_action_sprite = new ActionSprite( SPRITE_PRIEST_ACTION_FRAMES, pos_x, pos_y,
                                                           SPRITE_PRIEST_ACTION_PATH, _renderer );

    SDL_Texture* priest_dead_texture = Helper::load_texture( _renderer, SPRITE_PRIEST_DEAD );

    Character* priest = new Character( PRIEST_NAME, PRIEST_MAX_HP, PRIEST_INITIAL_COOLDOWN,
                                       PRIEST_ATK, PRIEST_DEF, priest_sprite, priest_action_sprite, priest_dead_texture );

    for( Uint8 i = 0; i < CHARACTER_SKILLS[PRIEST].size(); i++ ) {
        priest->add_skill(SKILL_MAPS[CHARACTER_SKILLS[PRIEST][i]]);
    }

    // Adding characters to the vector
    _characters.push_back( knight );
    _characters.push_back( wizard );
    _characters.push_back( priest );
}

void ZeroTempo_main::initialize_monsters( MONSTER* ms, int num )
{
    for( Uint8 i = 0; i < num && i < MAX_PARTY_NUMBERS; i++ ) {

        MONSTER m = ms[i];

        int pos_x = (double) POS_MONSTERS_X / 100 * WINDOW_WIDTH;
        int pos_y = (double) POS_CREATURES_Y / 100 * WINDOW_HEIGHT + double(i * CREATURES_MARGIN) / 100 * WINDOW_HEIGHT;

        Sprite* s = new Sprite( M_IDLE_FRAME_COUNTS[m], pos_x, pos_y, M_SPRITE_PATH[m], _renderer );
        ActionSprite* as = new ActionSprite( M_ACTION_FRAME_COUNTS[m], pos_x, pos_y, M_ACTION_SPRITE_PATH[m], _renderer );
        SDL_Texture* dt = Helper::load_texture( _renderer, M_DEAD_SPRITE_PATH[m] );
        Monster* mon = new Monster( M_NAMES[m], M_HP[m], M_INIT_CD[m], M_ATK[m], M_DEF[m], s, as, dt );

        for( SKILL_DEFS def : M_SKILLS[m] ) {
            mon->add_skill( SKILL_MAPS[def] );
        }

        _monsters.push_back( mon );
    }
}

void ZeroTempo_main::reset_creatures()
{
    for( Character* c : _characters )
    {
        cout << "Reset Character: " << c->get_name() << endl;
        c->reset_state();
    }

    for( Monster* m : _monsters )
    {
        cout << "Reset Monster: " << m->get_name() << endl;
        m->reset_state();
    }
}

void ZeroTempo_main::load_monsters( LEVEL level )
{
    _monsters.clear();

    int number;
    MONSTER ms[MAX_PARTY_NUMBERS];

    switch( level ) {
    case HARD:
        ms[0] = BANSHEE;
        ms[1] = BANSHEE;
        number = 2;
        break;

    case HARDER:
        ms[0] = THANATOS;
        ms[1] = BANSHEE;
        number = 2;
        break;

    case HARDEST:
        ms[0] = DRACULA;
        ms[1] = BANSHEE;
        number = 2;
        break;

    case IMPOSSIBLE:
        ms[0] = BANSHEE;
        ms[1] = THANATOS;
        ms[2] = DRACULA;
        number = 3;
        break;
    }

    initialize_monsters( ms, number );
    reset_creatures();
    _ts->set_monsters_list( _monsters );
}

void ZeroTempo_main::close()
{
    if( _window != NULL ) {
        SDL_DestroyWindow( _window );
        _window = NULL;
    }

    if( _renderer != NULL ) {
        SDL_DestroyRenderer( _renderer );
        _renderer = NULL;
    }

    if( _map != NULL ) {
        delete( _map );
        _map = NULL;
    }

    for( Character* c : _characters ) {
        if( c != NULL ) {
            delete( c );
        }
    }

    for( Monster* m : _monsters ) {
        if( m != NULL ) {
            delete( m );
        }
    }

    if( _menu != NULL ) {
        delete( _menu );
        _menu = NULL;
    }

    if( _psb != NULL ) {
        delete( _psb );
        _psb = NULL;
    }

    if( _bg_music != NULL ) {
        Mix_FreeMusic( _bg_music );
        _bg_music = NULL;
    }

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void ZeroTempo_main::init()  {

    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        Helper::error();
    }

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
        Helper::error();
    }

    _window = SDL_CreateWindow( WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP );
    if( _window == NULL ) {
        Helper::error();
    }

    SDL_GetWindowSize( _window, &WINDOW_WIDTH, &WINDOW_HEIGHT );

    _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE );
    if( _renderer == NULL ) {
        Helper::error();
    }

    SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0 );

    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(flags) & flags) ) {
        Helper::error();
    }

    if( TTF_Init() < 0 ) {
        Helper::error();
    }

    if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ) {
        cout << "SDL_Mixer Error : " << Mix_GetError() << endl;
        Helper::error();
    }

    initialize_skills_map();
    initialize_character_skills();
    initialize_characters();
    load_monster_db();
}

void ZeroTempo_main::load_media()
{
    _map = new Map( MAP_PATH, _renderer, WINDOW_WIDTH, WINDOW_HEIGHT );
    _psb = new PartyStatusBox( _renderer, _characters, WINDOW_WIDTH, WINDOW_HEIGHT );
    _ts = new TargetSelection( _renderer, TARGET_SELECTOR_POINTER_PATH, _characters, _monsters );
    _menu = new Menu( _renderer, _ts, _characters, _psb->PARTY_STATUS_BOX_X + _psb->PARTY_STATUS_BOX_WIDTH,
                      _psb->PARTY_STATUS_BOX_Y, WINDOW_WIDTH, WINDOW_HEIGHT );

    _bg_music = Mix_LoadMUS( BG_MUSIC_PATH.c_str() );
    if( _bg_music == NULL ) {
        Helper::error();
    }
}

void ZeroTempo_main::reload_objects()
{
    _map->render();

    for( Uint8 i = 0; i < _characters.size(); i++ ) {
        _characters[i]->render();
    }

    for( Uint8 i = 0; i < _monsters.size(); i++ ) {
        _monsters[i]->render();
    }

    _psb->render( _menu->get_active_character() );
    _menu->render();
    _ts->render();
}

void ZeroTempo_main::game_handling()
{
    _menu->update_active_character();

    for( Character* c : _characters ) {
        if( c->is_alive() ) {
            c->move();
        }
    }

    for( Monster* m : _monsters ) {
        if( m->is_alive() ) {
            m->think( (vector<Creature*>*) &_characters, (vector<Creature*>*) &_monsters );
            m->move();
        }
    }

    if( !exists_alive_character() ) {
        game_over();
    }

    if( !exists_alive_monster() ) {
        game_over();
    }
}

void ZeroTempo_main::render_blackout_screen( string text )
{
    SDL_Rect shape = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_SetRenderDrawBlendMode( _renderer, SDL_BLENDMODE_BLEND );
    SDL_SetRenderDrawColor( _renderer, 0, 0, 0, 200 );
    SDL_RenderFillRect( _renderer, &shape );
    SDL_SetRenderDrawBlendMode( _renderer, SDL_BLENDMODE_NONE );

    TTF_Font* font;
    SDL_Texture* game_over_text;
    int t_width, t_height;

    font = TTF_OpenFont( MAIN_SCREEN_FONT_PATH.c_str(), GAME_OVER_TEXT_SIZE );
    if( font == NULL ) {
        cout << "TTF_Error: " << TTF_GetError() << endl;
        Helper::error();
    }

    SDL_Color t_color = { 255, 255, 255, 100 };
    SDL_Surface* s = TTF_RenderText_Solid( font, text.c_str(), t_color );

    if( s == NULL ) {
        Helper::error();
    }

    game_over_text = SDL_CreateTextureFromSurface( _renderer, s );
    if( game_over_text == NULL ) {
        Helper::error();
    }

    t_width = s->w;
    t_height = s->h;
    SDL_FreeSurface( s );
    s = NULL;

    SDL_Rect cropper, opt;
    cropper = { 0, 0, t_width, t_height };
    opt = { Helper::get_centered_horizontal_pos(0, t_width, WINDOW_WIDTH),
            Helper::get_centered_vertical_pos(0, t_height, WINDOW_HEIGHT),
            t_width, t_height };

    SDL_RenderCopy( _renderer, game_over_text, &cropper, &opt );

    TTF_CloseFont( font );
    SDL_DestroyTexture( game_over_text );
    font = NULL;
    game_over_text = NULL;
}

void ZeroTempo_main::game_over()
{
    _menu->reset_menu();

    for( Character* c : _characters )
    {
        c->break_cast();
    }

    for( Monster* m : _monsters )
    {
        m->break_cast();
    }

    bool exit = false;

    SDL_Event e;

    while( !exit ) {
        while( SDL_PollEvent(&e) != 0 ) {
            if( e.type == SDL_QUIT ){
                exit = true;
                _quit = true;
            } else if( e.type == SDL_KEYDOWN ) {
                switch( e.key.keysym.sym ) {
                    case SDLK_q:
                        _quit = false;
                        _game_over = true;
                        exit = true;
                    break;


                    case SDLK_ESCAPE:
                        _quit = true;
                        _game_over = true;
                        exit = true;
                    break;

                    case SDLK_r:
                        reset_creatures();
                        _game_over = false;
                        exit = true;
                    break;

                    default:
                    break;
                }
            }
        }

        SDL_RenderClear( _renderer );
        reload_objects();
        render_blackout_screen("Press 'ESC' to exit game, 'R' to retry, 'Q' to back to main menu.");
        SDL_RenderPresent( _renderer );
    }
}

void ZeroTempo_main::start_game()
{
    SDL_Event e;
    _game_over = false;
    bool pause = false;

    Mix_PlayMusic( _bg_music, -1 );

    while( !_game_over && running() ) {
        while( SDL_PollEvent(&e) != 0 ) {
            if( e.type == SDL_QUIT ){
                _quit = true;
            } else if( e.type == SDL_KEYDOWN ) {
                if( e.key.keysym.sym == SDLK_ESCAPE ) {
                    pause = !pause;

                    if( pause ) {
                        for( Monster* m : _monsters ) {
                            m->pause();
                        }

                        for( Character* c : _characters ) {
                            c->pause();
                        }
                    } else {
                        for( Monster* m : _monsters ) {
                            m->unpause();
                        }

                        for( Character* c : _characters ) {
                            c->unpause();
                        }
                    }
                } else if( pause && e.key.keysym.sym == SDLK_q ) {
                    _game_over = true;
                } else if( !pause && _menu->is_active() ) {
                    _menu->handle_events(e);
                }
            }
        }

        if( !pause ) {
            game_handling();
        }

        SDL_RenderClear( _renderer );
        reload_objects();
        if( pause ) {
            render_blackout_screen( "Press 'ESC' to continue or 'Q' to go back to Main Menu" );
        }
        SDL_RenderPresent( _renderer );
    }

    free_monsters();
    Mix_HaltMusic();
}

bool ZeroTempo_main::exists_alive_character()
{
    for( Character* c : _characters ) {
        if( c->is_alive() ) {
            return true;
        }
    }
    return false;
}

bool ZeroTempo_main::exists_alive_monster()
{
    for( Monster* m : _monsters ) {
        if( m->is_alive() ) {
            return true;
        }
    }
    return false;
}

void ZeroTempo_main::free_monsters()
{
    for( size_t i = 0; i < _monsters.size(); ) {
        delete( _monsters[i] );
        _monsters.erase( _monsters.begin() + i );
    }
}

void ZeroTempo_main::main_window()
{
    MainWindow::show( _renderer, WINDOW_WIDTH, WINDOW_HEIGHT );
}

bool ZeroTempo_main::running()
{
    return !_quit;
}

int main( int argc, char* args[] ) {

    ZeroTempo_main* game_handler = new ZeroTempo_main();

    game_handler->init();
    game_handler->load_media();

    while( game_handler->running() ) {
        MainWindow::has_selected_level = false;
        game_handler->main_window();

        if( MainWindow::quit_game ) {
            break;
        }

        game_handler->load_monsters( MainWindow::active_level );
        game_handler->start_game();
    }

    game_handler->close();
    delete( game_handler );
    return 0;
}
