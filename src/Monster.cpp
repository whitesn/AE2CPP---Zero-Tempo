#include "Monster.h"

Monster::Monster(string name, int max_hp, int initial_cooldown, int atk,
                     int def, Sprite* sprite, ActionSprite* action_sprite, SDL_Texture* dead_sprite ) :
         Creature( name, max_hp, initial_cooldown, atk, def, sprite, action_sprite, dead_sprite )
{
    //ctor
    srand( time(NULL) );
}

Monster::~Monster()
{
    //dtor
}

void Monster::think( vector<Creature*>* characters, vector<Creature*>* monsters )
{
    if( is_ready() ) {

        int index = rand() % get_skill_count();
        Skill* s = get_skill(index);
        vector<Creature*> c_copy( *characters );
        vector<Creature*> m_copy( *monsters );
        vector<Creature*>* targets;

        if( s->is_positive_skill() ) {
            targets = &m_copy;
        } else {
            targets = &c_copy;
        }

        for( size_t i = 0; i < (*targets).size(); )
        {
            if( !((*targets)[i]->is_alive()) ) {
                (*targets).erase( (*targets).begin() + i );
            } else {
                i++;
            }
        }

        if( s->is_aoe ) {
            skill( index, *targets );
        } else {
            vector<Creature*> single_target = { (*targets)[rand() % (*targets).size()] };
            skill( index, single_target );
        }
    }
}

void Monster::render()
{
    Creature::render();

    Sprite* m = get_sprite();
    SDL_Renderer* r = m->renderer;

    // Status Ailment Indicator
    int sa_x = m->pos_x - STATUS_AILMENT_RIGHT_MARGIN;

    for( size_t i = 0; i < get_ail_statuses().size(); i++ ) {
        StatusAilments* sa = get_ail_statuses()[i];
        SDL_Texture* ail_sprite = sa->get_ailment_sprite( r );

        int w, h, resized_w, resized_h;
        SDL_Rect cropper, opt;

        SDL_QueryTexture( ail_sprite, NULL, NULL, &w, &h );
        resized_w = STATUS_AILMENT_ICON_RESIZE_SCALING * w;
        resized_h = STATUS_AILMENT_ICON_RESIZE_SCALING * h;
        int x = m->pos_x - STATUS_AILMENT_RIGHT_MARGIN - resized_w;
        int y = m->pos_y + (i * (STATUS_ICONS_MONSTER_MARGIN + resized_h));
        cropper = { 0, 0, w, h };
        opt = { x, y, resized_w, resized_h };
        SDL_RenderCopy( r, ail_sprite, &cropper, &opt );

        sa_x = x;
    }

    // Status Buffs Indicator
    for( size_t i = 0; i < get_buff_statuses().size(); i++ ) {
        StatusBuff* sb = get_buff_statuses()[i];
        SDL_Texture* buff_sprite = sb->get_buff_sprite( r );

        int w, h, resized_w, resized_h;
        SDL_Rect cropper, opt;
        SDL_QueryTexture( buff_sprite, NULL, NULL, &w, &h );
        resized_w = STATUS_BUFF_ICON_RESIZE_SCALING * w;
        resized_h = STATUS_BUFF_ICON_RESIZE_SCALING * h;
        int x = sa_x - STATUS_BUFF_AIL_MONSTER_MARGIN - resized_w;
        int y = m->pos_y + (i * (STATUS_ICONS_MONSTER_MARGIN + resized_h));
        cropper = { 0, 0, w, h };
        opt = { x, y, resized_w, resized_h };
        SDL_RenderCopy( r, buff_sprite, &cropper, &opt );
    }

    int x = Helper::get_centered_horizontal_pos( m->pos_x, HP_CD_BAR_WIDTH, m->width );
    int y = m->pos_y + m->height + BAR_MARGIN;

    // The Base BG Bar
    SDL_Rect bar = { x, y, HP_CD_BAR_WIDTH, HP_CD_BAR_HEIGHT * 2 };
    Helper::set_draw_color( r, BASE_BG_COLOR );
    SDL_RenderFillRect( r, &bar );

    // HP Bar
    bar.w = ((double) get_hp() / get_max_hp()) * HP_CD_BAR_WIDTH;
    bar.h = HP_CD_BAR_HEIGHT;
    if( (double) bar.w / HP_CD_BAR_WIDTH * 100 < LOW_HP_PERCENTAGE ) {
        Helper::set_draw_color( r, HP_BAR_LOW_COLOR );
    } else {
        Helper::set_draw_color( r, HP_BAR_COLOR );
    }
    SDL_RenderFillRect( r, &bar );

    // Cooldown Bar
    bar.y = bar.y + HP_CD_BAR_HEIGHT;
    bar.w = ((double) get_cooldown() / COOLDOWN_BAR_MAX_MS) * HP_CD_BAR_WIDTH;
    if( bar.w > HP_CD_BAR_WIDTH ) {
        bar.w = HP_CD_BAR_WIDTH;
    }
    Helper::set_draw_color( r, COOLDOWN_BAR_COLOR );
    SDL_RenderFillRect( r, &bar );

}
