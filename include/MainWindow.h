#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SDL.h>
#include <windows.h>
#include "ZeroTempo_main.h"
#include "Helper.h"

const string MAIN_WINDOW_FONT_PATH = "fonts/Roboto-Regular.ttf";
const string MAIN_WINDOW_LOGO_PATH = "sprites/main_menu/logo.png";
const string MAIN_WINDOW_BG_PATH = "sprites/main_menu/ragnarok-online_00448465.jpg";

const int LOGO_TOP_MARGIN = 40; // pixels

const int MAIN_WINDOW_FONT_SIZE = 50; // pixels
const int MENUS_BLOCK_LEFT_MARGIN = 8; // percent

const int MAIN_MENU_MIN_CONTAINER_WIDTH = 640; // pixels
const int MAIN_MENU_CONTAINER_WIDTH = 30; // percent

const int MENU_PADDING_TOP = 20; // percent
const int MENU_PADDING_LEFT = 10; // percent
const int MENU_HOVER_SYMBOL_MARGIN = 60; // pixels
const int MENU_BUTTON_MARGIN = 60; // pixels
const int MENU_LEVEL_TEXT_MARGIN = 15; // pixels

const string MAIN_WINDOW_MUSIC_PATH = "audio/main_window.mp3";

const int LOGO_MAX_WIDTH = 33; // percent

class Button
{
    public:
        enum ButtonType { GUIDE, LEVEL, PLAY, EXIT, NONE };
        Button();
        Button( SDL_Renderer* r, ButtonType bt, TTF_Font* font );
        ~Button();
        int BUTTON_WIDTH;
        int BUTTON_HEIGHT;
        void render();
        void handle_event( SDL_Event* e );
        bool is_hovered( int x, int y );

    private:
        ButtonType bt;
        SDL_Renderer* _renderer;
        SDL_Texture* _button;
        TTF_Font* _font;
        SDL_Point _pos;
        bool _is_hovered;

};

class MainWindow
{
    public:
        typedef ZeroTempo_main::LEVEL LEVEL;
        static bool quit_game;
        static bool resource_loaded;
        static int WINDOW_WIDTH;
        static int WINDOW_HEIGHT;
        static int MENU_WIDTH;
        static LEVEL active_level;
        static bool has_selected_level;
        MainWindow();
        virtual ~MainWindow();
        static void show( SDL_Renderer* r,
                          int width, int height );

    private:
        static SDL_Renderer* _renderer;
        static TTF_Font* _font;
        static SDL_Texture* _bg;
        static SDL_Texture* _logo;
        static Mix_Music* _bg_music;
        static map<Button::ButtonType,Button*> buttons;
        static void render();
        static void load_resources();
        static void increment_level();
        static void handle_button_events( SDL_Event* e );

    protected:

};

#endif // MAINWINDOW_H
