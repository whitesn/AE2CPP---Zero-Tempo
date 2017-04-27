#include "MainWindow.h"

bool MainWindow::quit_game = false;
bool MainWindow::resource_loaded = false;
bool MainWindow::has_selected_level = false;
int MainWindow::WINDOW_WIDTH = 0;
int MainWindow::WINDOW_HEIGHT = 0;
int MainWindow::MENU_WIDTH = 0;
SDL_Renderer* MainWindow::_renderer = NULL;
TTF_Font* MainWindow::_font = NULL;
SDL_Texture* MainWindow::_bg = NULL;
SDL_Texture* MainWindow::_logo = NULL;
ZeroTempo_main::LEVEL MainWindow::active_level;
map<Button::ButtonType,Button*> MainWindow::buttons;
Mix_Music* MainWindow::_bg_music = NULL;

MainWindow::MainWindow()
{
    //ctor
}

MainWindow::~MainWindow()
{
    /*
    TTF_CloseFont( _font );
    _font = NULL;

    SDL_DestroyTexture( _bg );
    _bg = NULL;

    SDL_DestroyTexture( _logo );
    _logo = NULL;

    Mix_FreeMusic( _bg_music );
    _bg_music = NULL;
    */
}

Button::Button()
{

}

bool Button::is_hovered( int x, int y )
{
    _is_hovered = x >= _pos.x && x <= (_pos.x + BUTTON_WIDTH) && y >= _pos.y && y <= (_pos.y + BUTTON_HEIGHT);
    return _is_hovered;
}

Button::Button( SDL_Renderer* r, ButtonType bt, TTF_Font* font )
{
    this->bt = bt;
    this->_font = font;
    this->_renderer = r;
    this->_is_hovered = false;

    string text;
    SDL_Color text_color = { 255, 255, 255, 255 };

    int padding_left = (double) MENUS_BLOCK_LEFT_MARGIN / 100 * MainWindow::WINDOW_WIDTH;
    int padding_top = (double) MENU_PADDING_TOP / 100 * MainWindow::WINDOW_HEIGHT;
    int x = padding_left + (double) MENUS_BLOCK_LEFT_MARGIN / 100 * MainWindow::WINDOW_WIDTH;
    int y = padding_top;

    switch( bt ) {
    case GUIDE:
        text = "HOW TO PLAY?";
        break;

    case LEVEL:
        text = "LEVEL: ";
        break;

    case PLAY:
        text = "PLAY";
        break;

    case EXIT:
        text = "EXIT";
        break;

    case NONE:
        break;
    }

    SDL_Surface* s = TTF_RenderText_Blended( _font, text.c_str(), text_color );
    if( s == NULL ) {
        Helper::error();
    }

    BUTTON_WIDTH = s->w;
    BUTTON_HEIGHT = s->h;

    _button = SDL_CreateTextureFromSurface( _renderer, s );
    if( _button == NULL ) {
        Helper::error();
    }

    switch( bt ) {
    case GUIDE:
        y += 0 * (BUTTON_HEIGHT + MENU_BUTTON_MARGIN);
        break;

    case LEVEL:
        y += 1 * (BUTTON_HEIGHT + MENU_BUTTON_MARGIN);
        break;

    case PLAY:
        y += 2 * (BUTTON_HEIGHT + MENU_BUTTON_MARGIN);
        break;

    case EXIT:
        y += 3 * (BUTTON_HEIGHT + MENU_BUTTON_MARGIN);
        break;

    case NONE:
        break;
    }

    _pos = { x, y };
}

Button::~Button()
{
    SDL_DestroyTexture( _button );
}

void Button::render()
{
    SDL_Rect cropper, opt;

    if( _is_hovered ) {
        SDL_Color text_color = { 255, 255, 255, 255 };

        SDL_Surface* s = TTF_RenderText_Blended( _font, ">", text_color );
        SDL_Texture* t = SDL_CreateTextureFromSurface( _renderer, s );

        cropper = { 0, 0, s->w, s->h };
        opt = { _pos.x - MENU_HOVER_SYMBOL_MARGIN, _pos.y, s->w, s->h };
        SDL_RenderCopy( _renderer, t, &cropper, &opt );

        SDL_FreeSurface( s );
        SDL_DestroyTexture( t );
    }

    if( bt == LEVEL ) {

        string difficulty;
        SDL_Color text_color;

        switch( MainWindow::active_level ) {
        case ZeroTempo_main::HARD:
            difficulty = "HARD";
            text_color = { 228, 133, 133, 255 };
            break;

        case ZeroTempo_main::HARDER:
            difficulty = "HARDER";
            text_color = { 228, 133, 133, 255 };
            break;

        case ZeroTempo_main::HARDEST:
            difficulty = "HARDEST";
            text_color = { 228, 133, 133, 255 };
            break;

        case ZeroTempo_main::IMPOSSIBLE:
            difficulty = "IMPOSSIBLE";
            text_color = { 228, 133, 133, 255 };
            break;
        }

        SDL_Surface* s = TTF_RenderText_Blended( _font, difficulty.c_str(), text_color );
        SDL_Texture* t = SDL_CreateTextureFromSurface( _renderer, s );

        cropper = { 0, 0, s->w, s->h };
        opt = { _pos.x + BUTTON_WIDTH + MENU_LEVEL_TEXT_MARGIN, _pos.y, s->w, s->h };
        SDL_RenderCopy( _renderer, t, &cropper, &opt );

        SDL_FreeSurface( s );
        SDL_DestroyTexture( t );
    }

    cropper = { 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
    opt = { _pos.x, _pos.y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy( _renderer, _button, &cropper, &opt );
}

bool is_mouse_event( SDL_Event* e )
{
    return e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP;
}

void MainWindow::load_resources()
{
    _font = TTF_OpenFont( MENU_FONT_PATH.c_str(), MAIN_WINDOW_FONT_SIZE );
    if( _font == NULL ) {
        Helper::error();
    }

    TTF_SetFontStyle( _font, TTF_STYLE_NORMAL );
    TTF_SetFontHinting( _font, TTF_HINTING_NONE );
    TTF_SetFontKerning( _font, 0 );

    _bg = Helper::load_texture( _renderer, MAIN_WINDOW_BG_PATH );
    _logo = Helper::load_texture( _renderer, MAIN_WINDOW_LOGO_PATH );

    buttons[Button::GUIDE] = new Button( _renderer, Button::GUIDE, _font );
    buttons[Button::LEVEL] = new Button( _renderer, Button::LEVEL, _font );
    buttons[Button::PLAY] = new Button( _renderer, Button::PLAY, _font );
    buttons[Button::EXIT] = new Button( _renderer, Button::EXIT, _font );

    _bg_music = Mix_LoadMUS( MAIN_WINDOW_MUSIC_PATH.c_str() );
    if( _bg_music == NULL ) {
        Helper::error();
    }

    resource_loaded = true;
}

void MainWindow::render()
{
    SDL_RenderClear( _renderer );

    SDL_Rect cropper, opt;

    // Background
    int bg_w, bg_h;
    SDL_QueryTexture( _bg, NULL, NULL, &bg_w, &bg_h );
    cropper = { 0, 0, bg_w, bg_h };
    opt = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderCopy( _renderer, _bg, &cropper, &opt );

    // Logo
    int logo_w, logo_h;
    int resized_w, resized_h;
    SDL_QueryTexture( _logo, NULL, NULL, &logo_w, &logo_h );

    if( logo_w > LOGO_MAX_WIDTH ) {
        double resize_scaling = (double) LOGO_MAX_WIDTH / 100 * WINDOW_WIDTH / logo_w;
        resized_w = resize_scaling * logo_w;
        resized_h = resize_scaling * logo_h;
    } else {
        resized_w = logo_w;
        resized_h = logo_h;
    }

    cropper = { 0, 0, logo_w, logo_h };
    opt = { WINDOW_WIDTH - resized_w - LOGO_TOP_MARGIN,
            0 + LOGO_TOP_MARGIN, resized_w, resized_h };

    SDL_RenderCopy( _renderer, _logo, &cropper, &opt );

    // Menu
    int menu_x = (double) MENUS_BLOCK_LEFT_MARGIN / 100 * WINDOW_WIDTH;
    int menu_w = (double) MAIN_MENU_CONTAINER_WIDTH / 100 * WINDOW_WIDTH;
    menu_w = (menu_w < MAIN_MENU_MIN_CONTAINER_WIDTH) ? MAIN_MENU_MIN_CONTAINER_WIDTH : menu_w;
    MENU_WIDTH = menu_w;

    SDL_Rect menu_bg = { menu_x, 0, menu_w, WINDOW_HEIGHT };
    SDL_SetRenderDrawBlendMode( _renderer, SDL_BLENDMODE_BLEND );
    SDL_SetRenderDrawColor( _renderer, 0, 0, 0, 200 );
    SDL_RenderFillRect( _renderer, &menu_bg );
    SDL_SetRenderDrawBlendMode( _renderer, SDL_BLENDMODE_NONE );

    // Menu Buttons
    buttons[Button::GUIDE]->render();
    buttons[Button::LEVEL]->render();
    buttons[Button::PLAY]->render();
    buttons[Button::EXIT]->render();

    SDL_RenderPresent( _renderer );
}

void MainWindow::increment_level() {
    if( active_level == ZeroTempo_main::HARD ) {
        active_level = ZeroTempo_main::HARDER;
    } else if ( active_level == ZeroTempo_main::HARDER ) {
        active_level = ZeroTempo_main::HARDEST;
    } else if ( active_level == ZeroTempo_main::HARDEST ) {
        active_level = ZeroTempo_main::IMPOSSIBLE;
    } else {
        active_level = ZeroTempo_main::HARD;
    }
}

void MainWindow::handle_button_events( SDL_Event* e )
{
    int x, y;
    SDL_GetMouseState( &x, &y );

    Button::ButtonType active_button = Button::NONE;
    active_button = (buttons[Button::GUIDE]->is_hovered( x, y )) ? Button::GUIDE : active_button;
    active_button = (buttons[Button::LEVEL]->is_hovered( x, y )) ? Button::LEVEL : active_button;
    active_button = (buttons[Button::PLAY]->is_hovered( x, y )) ? Button::PLAY : active_button;
    active_button = (buttons[Button::EXIT]->is_hovered( x, y )) ? Button::EXIT : active_button;

    switch( active_button ) {
    case Button::GUIDE:
        if( e->type == SDL_MOUSEBUTTONDOWN ) {
            ShellExecute( NULL, "open", "help.html", NULL, NULL, SW_SHOWNORMAL);
        }
        break;

    case Button::LEVEL:
        if( e->type == SDL_MOUSEBUTTONDOWN ) {
            increment_level();
        }
        break;

    case Button::PLAY:
        if( e->type == SDL_MOUSEBUTTONDOWN ) {
            has_selected_level = true;
            quit_game = false;
        }
        break;

    case Button::EXIT:
        if( e->type == SDL_MOUSEBUTTONDOWN ) {
            quit_game = true;
        }
        break;

    default:
        break;
    }
}

void MainWindow::show( SDL_Renderer* r, int width, int height )
{
    active_level = ZeroTempo_main::HARD;
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    _renderer = r;

    if( !resource_loaded ) {
        load_resources();
    }

    if( Mix_PlayMusic( _bg_music, -1 ) == -1 ) {
        cout << Mix_GetError();
        Helper::error();
    }

    SDL_Event e;
    while( !has_selected_level && !quit_game )
    {
        while( SDL_PollEvent(&e) != 0 )
        {
            if( e.type == SDL_QUIT ) {
                quit_game = true;
            } else if( is_mouse_event(&e) ) {
                handle_button_events(&e);
            }
        }

        render();
    }

    Mix_HaltMusic();
}
