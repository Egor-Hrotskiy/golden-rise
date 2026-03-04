#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "wind.h"
#include <math.h>


typedef enum {
    MENU,
    LEVELS, 
    PAUSE,
    QUIT, 
    RESTART, 
    SETTINGS, 
    SAVE_MENU,
    CHARACTER_CREATION,
    GAMEPLAY,
    CHECKPOINT, 
    WIN
} e_game_state;

typedef enum {
    VERTICAL_SPIKE,
    HORIZONTAL_SPIKE, 
    PLATFORM, 
    MONEY, 
    PIGGYBANK,
    DOUBLE_COIN
}      e_object_type;

typedef struct s_env_object {
    int x_end;
    int x_start;
    int y_end;
    int y_start;
    int does_damage;
    bool active;
    e_object_type type;
    Vector2 size;
    int direction;
    int checkpoint_number;
}              t_eobject;

typedef struct s_env_objects {
    t_eobject *objects;
    int size;
}              t_envs;

typedef struct s_respawn_indexes {
    int indexes[6];
    int size;
}              t_respawns;

typedef struct Player {
    Vector2 position;
    float speed;
    float jump_speed;
    bool is_grounded;
    Texture2D texture;
    float stun_timer;
    float knockback_x;
    int health_points;
    float inv_time;
    float jump_buffer_timer;
    float coyote_timer;
    int current_score;
    int score;
    t_respawns respawned_objects;
    int current_checkpoint;
    int max_checkpoint;
    int max_health;
    bool can_double_jump;
    bool snap_camera;
}              Player;

void mx_update_player(Player *player, t_envs objects, Texture2D *sprites, e_game_state *game_state, t_wind current_wind);
void mx_draw_player(Player player);
void mx_update_camera(Camera2D *camera, Player *player);

#endif
