#include "raylib.h"
#include "main.h"

void mx_draw_pause(Texture2D *sprites) {
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();
    
    const int x_btn = screen_width / 2 - 200;
    const int y_play_btn = screen_height / 2 - 50;
    
    float stretch_factor = 1.5f; 
    float original_w = (float)sprites[TEX_PAUSE_TXT].width;
    float original_h = (float)sprites[TEX_PAUSE_TXT].height;
    
    float final_w = original_w * stretch_factor;
    float final_h = original_h;
    int x_text = screen_width / 2 - (int)final_w / 2;
    int y_text = y_play_btn - (int)final_h - 60;

    DrawRectangle(0, 0, screen_width, screen_height, Fade(BLACK, 0.66f));
    
    Rectangle source = { 0.0f, 0.0f, original_w, original_h };
    Rectangle dest = { (float)x_text, (float)y_text, final_w, final_h };
    Vector2 origin = { 0, 0 };

    DrawTexturePro(sprites[TEX_PAUSE_TXT], source, dest, origin, 0.0f, WHITE);

    DrawTexture(sprites[TEX_PLAY_BTN_LARGE], x_btn, y_play_btn, WHITE);
    DrawTexture(sprites[TEX_EXIT_BTN_LARGE], x_btn, y_play_btn + 250, WHITE);
}

void mx_update_pause(e_game_state *game_state, Texture2D *sprites) {
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();
    const int mouse_x = GetMouseX();
    const int mouse_y = GetMouseY();

    const int x_btn = screen_width / 2 - 200;
    const int y_play_btn = screen_height / 2 - 50;
    const int y_exit_btn = y_play_btn + 250;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (mouse_x > x_btn && mouse_x < x_btn + sprites[TEX_PLAY_BTN_LARGE].width && 
            mouse_y > y_play_btn && mouse_y < y_play_btn + sprites[TEX_PLAY_BTN_LARGE].height) {
            *game_state = LEVELS;
        }
        else if (mouse_x > x_btn && mouse_x < x_btn + sprites[TEX_EXIT_BTN_LARGE].width && 
                 mouse_y > y_exit_btn && mouse_y < y_exit_btn + sprites[TEX_EXIT_BTN_LARGE].height) {
            *game_state = MENU;
        }
    }
}
