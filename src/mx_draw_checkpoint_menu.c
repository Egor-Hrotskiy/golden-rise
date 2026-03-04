#include "raylib.h"
#include "main.h"


void mx_draw_checkpoint_menu(Texture2D *sprites) {
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();
    const int x_start = screen_width / 2 - 150;
    const int y_start = screen_height / 2 - 250;

    DrawRectangle(0, 0, screen_width, screen_height, Fade(BLACK, 0.66f));

    DrawTexture(sprites[TEX_PREV_BTN], x_start - 400, y_start, WHITE);
    DrawTexture(sprites[TEX_BUY_BTN], x_start, y_start, WHITE);
    DrawTexture(sprites[TEX_NEXT_BTN], x_start + 404, y_start, WHITE);
    DrawTexture(sprites[TEX_BACK_BTN_SMALL], x_start, y_start + 400, WHITE);
}

void mx_update_checkpoint_menu(e_game_state *game_state, Player *player, t_envs env_objects) {
    Vector2 mouse = GetMousePosition();
    
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();
    const int x_start = screen_width / 2 - 150;
    const int y_start = screen_height / 2 - 250;

    const int btn_width = 220;
    const int btn_height = 180;

    if (mouse.x >= x_start - 400 && mouse.x <= (x_start - 400) + btn_width &&
        mouse.y >= y_start && mouse.y <= y_start + btn_height) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (player->current_checkpoint - 1 >= 0) {
                player->current_checkpoint--;
                mx_save_game(player_name, player->score, player->current_checkpoint, player->max_checkpoint, player->max_health, current_slot);
            }
        }
    }
    if (mouse.x >= x_start && mouse.x <= x_start + btn_width &&
        mouse.y >= y_start && mouse.y <= y_start + btn_height) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (player->score >= 800) {
                player->score -= 800;
                player->max_health++;
                player->health_points++;
                mx_save_game(player_name, player->score, player->current_checkpoint, player->max_checkpoint, player->max_health, current_slot);
            }
        }
    }

    if (mouse.x >= x_start + 404 && mouse.x <= (x_start + 404) + btn_width &&
        mouse.y >= y_start && mouse.y <= y_start + btn_height) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (player->current_checkpoint + 1 <= player->max_checkpoint) {
                player->current_checkpoint++;
                player->snap_camera = true;
                mx_save_game(player_name, player->score, player->current_checkpoint, player->max_checkpoint, player->max_health, current_slot);
            }
        }
    }
    if (mouse.x >= x_start && mouse.x <= x_start + btn_width &&
        mouse.y >= y_start + 400 && mouse.y <= (y_start + 400) + btn_height) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            player->jump_speed = 0;
            player->position = (Vector2){env_objects.objects[player->current_checkpoint].x_start, env_objects.objects[player->current_checkpoint].y_start};
            *game_state = LEVELS;
            mx_save_game(player_name, player->score, player->current_checkpoint, player->max_checkpoint, player->max_health, current_slot);
        }
    }
    if (IsKeyPressed(KEY_B)) {
        player->jump_speed = 0;
        player->position = (Vector2){env_objects.objects[player->current_checkpoint].x_start, env_objects.objects[player->current_checkpoint].y_start};
        player->snap_camera = true;
        *game_state = LEVELS;
        mx_save_game(player_name, player->score, player->current_checkpoint, player->max_checkpoint, player->max_health, current_slot);
    }
}
