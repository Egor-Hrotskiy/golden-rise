#include "raylib.h"
#include "main.h"

void mx_draw_restart(Texture2D *sprites) {
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    const int center_x = screen_width / 2;

    const int x_restart_btn = center_x + 80; 
    const int y_restart_btn = screen_height / 2;

    const int x_exit_btn = center_x - 300;
    const int y_exit_btn = y_restart_btn;

    float text_width = (float)sprites[TEX_LOST_TXT].width;
    int x_text = center_x - (int)text_width / 2;
    int y_text = y_restart_btn - (int)sprites[TEX_LOST_TXT].height - 60; 

    DrawRectangle(0, 0, screen_width, screen_height, Fade(BLACK, 0.6f));
    DrawTexture(sprites[TEX_LOST_TXT], x_text, y_text, WHITE);

    DrawTexture(sprites[TEX_RESTART_BTN], x_restart_btn, y_restart_btn, WHITE);
    DrawTexture(sprites[TEX_EXIT_BTN_LARGE], x_exit_btn, y_exit_btn, WHITE);
}

void mx_update_restart(e_game_state *game_state, Texture2D *sprites) {
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();
    const int center_x = screen_width / 2;
    const int mouse_x = GetMouseX();
    const int mouse_y = GetMouseY();

    const int x_restart_btn = center_x + 80; 
    const int y_restart_btn = screen_height / 2;
    const int x_exit_btn = center_x - 300;
    const int y_exit_btn = y_restart_btn;

    if (IsKeyPressed(KEY_R)) *game_state = LEVELS;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (mouse_x > x_restart_btn && mouse_x < x_restart_btn + sprites[TEX_RESTART_BTN].width && 
            mouse_y > y_restart_btn && mouse_y < y_restart_btn + sprites[TEX_RESTART_BTN].height) {
            *game_state = LEVELS;
        }
        else if (mouse_x > x_exit_btn && mouse_x < x_exit_btn + sprites[TEX_EXIT_BTN_LARGE].width && 
                 mouse_y > y_exit_btn && mouse_y < y_exit_btn + sprites[TEX_EXIT_BTN_LARGE].height) {
            *game_state = MENU;
        }
    }
}
