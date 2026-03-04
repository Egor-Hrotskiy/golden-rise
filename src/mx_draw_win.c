#include "raylib.h"
#include "main.h"

void mx_draw_win(Texture2D *sprites) {
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();
    const int x_start = screen_width / 2 - 100;
    const int y_start = screen_height / 2 - 150;
    

    DrawRectangle(0, 0, screen_width, screen_height, Fade(BLACK, 0.66f));
  
    int win_txt_x = screen_width / 2 - sprites[TEX_WIN_TXT].width / 2;

    int win_txt_y = y_start - sprites[TEX_WIN_TXT].height - 50; 
    
    DrawTexture(sprites[TEX_WIN_TXT], win_txt_x, win_txt_y, WHITE);
    
    DrawTexture(sprites[TEX_FINISH_BTN], x_start, y_start, WHITE);
    DrawTexture(sprites[TEX_PREV_BTN], x_start, y_start + 250, WHITE);
}

void mx_update_win(e_game_state *game_state, Player *player, t_envs env_objects) {
    const int x_start = GetScreenWidth() / 2 - 100;
    const int y_start = GetScreenHeight() / 2 - 150; 
    const int mouse_x = GetMouseX();
    const int mouse_y = GetMouseY();
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (mouse_x > x_start - 3 && mouse_x < x_start - 3 + 340 && 
            mouse_y > y_start && mouse_y < y_start + 180) {
                player->jump_speed = 0;
                player->position = (Vector2){env_objects.objects[player->current_checkpoint].x_start, env_objects.objects[player->current_checkpoint].y_start};
                *game_state = MENU;
        }
        else if (mouse_x > x_start - 3 && mouse_x < x_start - 3 + 340 && 
                 mouse_y > y_start + 250 && mouse_y < y_start + 250 + 180) {
            player->current_checkpoint--;
            player->jump_speed = 0;
            player->position = (Vector2){env_objects.objects[player->current_checkpoint].x_start, env_objects.objects[player->current_checkpoint].y_start};
            *game_state = LEVELS;        
        }
    }
}
