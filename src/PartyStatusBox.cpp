#include "PartyStatusBox.h"

PartyStatusBox::PartyStatusBox(SDL_Renderer* r, vector<Character*> characters,
                               int screen_width, int screen_height)
{
    _renderer = r;
    _characters = characters;

    _cur_hp_color = { 82, 155, 76, 255 };
    _cur_low_hp_color = { 155, 70, 70, 255 };
    _cur_cooldown_color = { 61, 116, 184, 255 };
    _base_bg_color = { 200, 200, 200, 255 };

    load_texture();

    PARTY_STATUS_BOX_WIDTH = (double) PARTY_STATUS_BOX_RELATIVE_WIDTH / 100 * screen_width;
    PARTY_STATUS_BOX_HEIGHT = (double) PARTY_STATUS_BOX_RELATIVE_HEIGHT / 100 * screen_height;
    PARTY_STATUS_BOX_X = PARTY_STATUS_BOX_SCREEN_MARGIN;
    PARTY_STATUS_BOX_Y = screen_height - PARTY_STATUS_BOX_SCREEN_MARGIN - PARTY_STATUS_BOX_HEIGHT;
}

void PartyStatusBox::load_texture() {

    _bg = Helper::load_texture( _renderer, PARTY_STATUS_BOX_PATH );
    _font = TTF_OpenFont( PARTY_STATUS_BOX_FONTS_PATH.c_str(), PARTY_STATUS_BOX_TEXT_SIZE );

    if( _font == NULL ) {
        Helper::error();
    }

    _text_color = { 255, 255, 255, 255 };
    SDL_QueryTexture( _bg, NULL, NULL, &PARTY_STATUS_BOX_ORI_WIDTH, &PARTY_STATUS_BOX_ORI_HEIGHT );
}


PartyStatusBox::~PartyStatusBox()
{
    SDL_DestroyTexture( _bg );
    TTF_CloseFont( _font );
}

void PartyStatusBox::add_name_label( Character* c, int block_height, bool is_active, int* pos_y )
{
    SDL_Rect cropper, opt;
    string display_name = c->get_name();
    display_name = ( is_active ) ? "> " + display_name : display_name;
    SDL_Surface* text_surface = TTF_RenderText_Blended( _font, display_name.c_str(), _text_color );
    if( text_surface == NULL ) {
        Helper::error();
    }

    SDL_Texture* name_texture = SDL_CreateTextureFromSurface( _renderer, text_surface );
    if( name_texture == NULL ) {
        Helper::error();
    }

    cropper = { 0, 0, text_surface->w, text_surface->h };

    double resize_scaling = ((double) PARTY_STATUS_BOX_NAME_HEIGHT / 100 * block_height) / text_surface->h;
    int text_width = text_surface->w * resize_scaling;
    int text_height = text_surface->h * resize_scaling;
    opt = { 0, 0, text_width, text_height };

    SDL_RenderCopy( _renderer, name_texture, &cropper, &opt );
    SDL_DestroyTexture( name_texture );

    *pos_y = text_height;

    SDL_FreeSurface( text_surface );

    // Ailment Statuses
    int ail_last_pos_x = text_width + NAME_ICON_MARGIN;

    for( size_t i = 0; i < (c->get_ail_statuses()).size(); i++ ) {
        StatusAilments* sa = c->get_ail_statuses()[i];
        SDL_Texture* ail_sprite = sa->get_ailment_sprite(_renderer);
        int w, h;
        SDL_QueryTexture( ail_sprite, NULL, NULL, &w, &h );
        cropper = { 0, 0, w, h };
        resize_scaling = ((double) PARTY_STATUS_BOX_NAME_HEIGHT / 100 * block_height) / h;
        w *= resize_scaling;
        h *= resize_scaling;
        int x = text_width + (i * (STATUS_ICON_PARTY_BOX_MARGIN + w)) + NAME_ICON_MARGIN;
        int y = Helper::get_centered_vertical_pos( 0, h, text_height );
        opt = { x, y, w, h };
        SDL_RenderCopy( _renderer, ail_sprite, &cropper, &opt );
        ail_last_pos_x = x + w + AIL_BUFF_STATUS_ICON_MARGIN;
    }

    // Buff Statuses
    for( size_t i = 0; i < (c->get_buff_statuses()).size(); i++ ) {
        StatusBuff* sb = c->get_buff_statuses()[i];
        SDL_Texture* buff_sprite = sb->get_buff_sprite(_renderer);
        int w, h;
        SDL_QueryTexture( buff_sprite, NULL, NULL, &w, &h );
        cropper = { 0, 0, w, h };
        resize_scaling = ((double) PARTY_STATUS_BOX_NAME_HEIGHT / 100 * block_height) / h;
        w *= resize_scaling;
        h *= resize_scaling;
        int y = Helper::get_centered_vertical_pos( 0, h, text_height );
        opt = { ail_last_pos_x + ((int) (i * (STATUS_ICON_PARTY_BOX_MARGIN + w))), y, w, h };
        SDL_RenderCopy( _renderer, buff_sprite, &cropper, &opt );
    }
}

void PartyStatusBox::add_hp_block( Character* c, int block_width, int block_height, int l_posy, int* pos_y )
{
    SDL_Rect cropper, opt;

    int bar_width = (double) PARTY_STATUS_BOX_BAR_WIDTH / 100 * block_width;
    int bar_height = (double) PARTY_STATUS_BOX_BAR_HEIGHT / 100 * block_height;
    int hp_block_y = l_posy + PARTY_STATUS_BOX_NAME_BAR_MARGIN;

    // Base BG Color
    SDL_Rect shape = { 0, hp_block_y, bar_width, bar_height };
    Helper::set_draw_color( _renderer, _base_bg_color );
    SDL_RenderFillRect( _renderer, &shape );

    // Current HP Color
    shape.w = (double) c->get_hp() / c->get_max_hp() * bar_width;
    if( (double) shape.w / bar_width * 100 < LOW_HP_PERCENTAGE ) {
        Helper::set_draw_color( _renderer, _cur_low_hp_color );
    } else {
        Helper::set_draw_color( _renderer, _cur_hp_color );
    }
    SDL_RenderFillRect( _renderer, &shape );

    *pos_y = hp_block_y + bar_height;

    // HP Desc
    string hp_label = "[" + Helper::to_string(c->get_hp()) + " / " + Helper::to_string(c->get_max_hp()) + "]";
    SDL_Surface* text_surface = TTF_RenderText_Solid( _font, hp_label.c_str(), _text_color );
    if( text_surface == NULL ) {
        Helper::error();
    }

    SDL_Texture* desc = SDL_CreateTextureFromSurface( _renderer, text_surface );
    if( desc == NULL ) {
        Helper::error();
    }

    cropper = { 0, 0, text_surface->w, text_surface->h };
    int label_posx = bar_width + PARTY_STATUS_BOX_DESC_MARGIN;
    int label_posy = l_posy;

    double resize_scaling = (double) bar_height / text_surface->h;

    opt = { label_posx, label_posy, (int) (text_surface->w * resize_scaling), (int) (text_surface->h * resize_scaling) };
    SDL_RenderCopy( _renderer, desc, &cropper, &opt );
    SDL_FreeSurface( text_surface );
    SDL_DestroyTexture( desc );
}

void PartyStatusBox::add_cd_block( Character* c, int block_width, int block_height, int hp_posy )
{
    SDL_Rect cropper, opt;

    int bar_width = (double) PARTY_STATUS_BOX_BAR_WIDTH / 100 * block_width;
    int bar_height = (double) PARTY_STATUS_BOX_BAR_HEIGHT / 100 * block_height;

    // Base BG BAR
    SDL_Rect shape = { 0, hp_posy, bar_width, bar_height };
    Helper::set_draw_color( _renderer, _base_bg_color );
    SDL_RenderFillRect( _renderer, &shape );

    // Current CD Bar
    shape.w = (double) c->get_cooldown() / COOLDOWN_BAR_MAX_MS * bar_width;
    shape.w = ( shape.w > bar_width ) ? bar_width : shape.w;
    Helper::set_draw_color( _renderer, _cur_cooldown_color );
    SDL_RenderFillRect( _renderer, &shape );

    // Desc (in millisecs)
    string cd_label = Helper::to_string(c->get_cooldown()) + " ms";
    SDL_Surface* text_surface = TTF_RenderText_Solid( _font, cd_label.c_str(), _text_color );
    if( text_surface == NULL ) {
        Helper::error();
    }

    SDL_Texture* desc = SDL_CreateTextureFromSurface( _renderer, text_surface );
    if( desc == NULL ) {
        Helper::error();
    }

    int label_posx = bar_width + PARTY_STATUS_BOX_DESC_MARGIN;
    int label_posy = hp_posy;

    double resize_scaling = (double) bar_height / text_surface->h;

    cropper = { 0, 0, text_surface->w, text_surface->h };
    opt = { label_posx, label_posy, (int) (text_surface->w * resize_scaling), (int) (text_surface->h * resize_scaling) };
    SDL_RenderCopy( _renderer, desc, &cropper, &opt );

    SDL_FreeSurface( text_surface );
    SDL_DestroyTexture( desc );
}

void PartyStatusBox::render( Character* active_character )
{
    SDL_Rect cropper, opt;
    cropper = { 0, 0, PARTY_STATUS_BOX_ORI_WIDTH, PARTY_STATUS_BOX_ORI_HEIGHT };
    opt = { PARTY_STATUS_BOX_X, PARTY_STATUS_BOX_Y, PARTY_STATUS_BOX_WIDTH, PARTY_STATUS_BOX_HEIGHT };
    SDL_RenderCopy( _renderer, _bg, &cropper, &opt );

    SDL_Texture* char_block[3];

    int char_block_x = Helper::get_centered_horizontal_pos( PARTY_STATUS_BOX_X, (double) CHAR_BLOCK_WIDTH / 100 * PARTY_STATUS_BOX_WIDTH, PARTY_STATUS_BOX_WIDTH );
    int char_block_y = Helper::get_centered_vertical_pos( PARTY_STATUS_BOX_Y, (double) CHAR_BLOCK_HEIGHT / 100 * 3 * PARTY_STATUS_BOX_HEIGHT, PARTY_STATUS_BOX_HEIGHT );
    int block_width = (double) CHAR_BLOCK_WIDTH / 100 * PARTY_STATUS_BOX_WIDTH;
    int block_height = (double) CHAR_BLOCK_HEIGHT / 100 * PARTY_STATUS_BOX_HEIGHT;

    for( Uint8 i = 0; i < _characters.size(); i++ ) {

        Character* c = _characters[i];
        char_block[i]= SDL_CreateTexture( _renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                          block_width, block_height );

        SDL_SetRenderTarget( _renderer, char_block[i] );

        SDL_SetTextureBlendMode( char_block[i], SDL_BLENDMODE_BLEND );
        SDL_SetRenderDrawColor( _renderer, 0, 0, 0, 0 );
        SDL_RenderClear( _renderer );

        int label_pos_y;
        int hp_pos_y;

        bool is_active_char = active_character == c;
        add_name_label( c, block_height, is_active_char, &label_pos_y );
        add_hp_block( c, block_width, block_height, label_pos_y, &hp_pos_y );
        add_cd_block( c, block_width, block_height, hp_pos_y );

        SDL_SetRenderTarget( _renderer, NULL );

        cropper = { 0, 0, block_width, block_height };
        int pos_y = char_block_y + ( i * block_height );
        opt = { char_block_x, pos_y, block_width, block_height };
        SDL_RenderCopy( _renderer, char_block[i], &cropper, &opt );

        SDL_DestroyTexture( char_block[i] );
    }

    SDL_SetRenderTarget( _renderer, NULL );
}
