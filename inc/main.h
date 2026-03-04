#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <string.h>
#include "player.h"
#include <math.h>

extern char player_name[11];
extern int current_slot;


typedef enum {
    TEX_DIRT_DEFAULT = 0,
    TEX_SPIKE,
    TEX_GREEN_PLATFORM_LEFT,
    TEX_GREEN_PLATFORM_RIGHT,
    TEX_PLAY_BTN_LARGE,
    TEX_PLAY_BTN_SMALL,
    TEX_PLAYER_DEFAULT,
    TEX_SETTINGS_BTN,
    TEX_EXIT_BTN_LARGE,
    TEX_EXIT_BTN_SMALL,
    TEX_BG_MENU,
    TEX_HEALTH_POINT,
    TEX_PLAYER_LEFT,
    TEX_PLAYER_RIGHT,
    TEX_RESTART_BTN,
    TEX_MONEY,
    TEX_SOUND_ON, 
    TEX_SOUND_OFF,
    TEX_MUSIC_ON, 
    TEX_MUSIC_OFF,
    TEX_BACK_BTN, 
    TEX_FIRST_BG,
    TEX_CHECKPOINT,
    TEX_NEXT_BTN,
    TEX_PREV_BTN,
    TEX_BUY_BTN,
    TEX_BACK_BTN_SMALL,
    TEX_GREEN_PLATFORM_CENTER,
    TEX_BLUE_PLATFORM_LEFT,
    TEX_BLUE_PLATFORM_RIGHT,
    TEX_BLUE_PLATFORM_CENTER,
    TEX_MOUNTAIN_DIRT_DEFAULT,
    TEX_SECOND_BG,
    TEX_DOUBLE_COIN,
    TEX_GOLD_PLATFORM_LEFT,
    TEX_GOLD_PLATFORM_RIGHT,
    TEX_GOLD_PLATFORM_CENTER,
    TEX_THIRD_BG,
    TEX_SKY_DIRT_DEFAULT,
    TEX_PAUSE_TXT,
    TEX_LOST_TXT,
    TEX_FINISH_BTN,
    TEX_SAVES_TITLE,
    TEX_NEW_SAVE,
    TEX_GAME_TITLE,
    TEX_WIN_TXT,
    TEX_COUNT
}      e_texture_id;

typedef struct s_texture {
    char *source;
    bool resize;
    int x_size;
    int y_size;
}              t_texture;

typedef struct s_settings {
    bool sound_on;
    bool music_on;
}             t_settings;

void mx_draw_platform(Texture2D *sprites, const t_eobject *object);
void mx_draw_spike(Texture2D spike, const t_eobject *object);
void mx_update_pause(e_game_state *game_state, Texture2D *sprites);
void mx_draw_pause(Texture2D *sprites);
void mx_draw_player(Player player);
void mx_init_platform(Texture2D platform_block, t_eobject *object);
void mx_init_spike(Texture2D spike, t_eobject *object);
void mx_draw_menu(Texture2D *sprites);
void mx_draw_hp(Texture2D *sprites, int count);
void mx_init_textures(Texture2D *sprites);
void mx_update_menu(e_game_state *game_state, Texture2D *sprites);
void mx_draw_restart(Texture2D *sprites);
void mx_update_restart(e_game_state *game_state, Texture2D *sprites);
void mx_init_money(Texture2D *sprites, t_eobject *object);
void mx_update_money(const t_eobject *object, Texture2D *sprites);
void mx_update_settings(e_game_state *game_state, t_settings *settings);
void mx_draw_settings(Texture2D *sprites, t_settings settings);
void mx_draw_objects(Texture2D *sprites, t_envs env_objects, Player *my_player, e_game_state game_state, Camera2D camera);
void mx_init_objects(t_envs *env_objects, Texture2D *sprites);
void mx_init_checkpoint(Texture2D *sprites, t_eobject *object);
void mx_draw_checkpoint(Texture2D *sprites, const t_eobject *object);
void mx_draw_checkpoint_menu(Texture2D *sprites);
void mx_update_checkpoint_menu(e_game_state *game_state, Player *player, t_envs env_objects);
void mx_init_double_coin(Texture2D *sprites, t_eobject *object);
void mx_update_double_coin(const t_eobject *object, Texture2D *sprites);
void mx_update_win(e_game_state *game_state, Player *player, t_envs env_objects);
void mx_draw_win(Texture2D *sprites);
void mx_update_save_menu(e_game_state *game_state, Player *player, t_envs env_objects);
void mx_draw_save_menu(Texture2D *sprites);
void mx_update_char_creation(e_game_state *game_state, Player *player, t_envs env_objects);
void mx_save_game(const char *name, int score, int checkpoint, int max_checkpoint, int max_health, int slot); 
void mx_load_game(Player *player, int slot); 
void mx_draw_char_creation(Texture2D *sprites);

#endif
