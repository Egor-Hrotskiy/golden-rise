#include "raylib.h"
#include "main.h"

void mx_update_menu(e_game_state *game_state, Texture2D *sprites) {
    const int x_start = GetScreenWidth() / 2 - 150;
    const int y_start = GetScreenHeight() / 2 - 150;
    const int mouse_x = GetMouseX();
    const int mouse_y = GetMouseY();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (mouse_x > x_start && mouse_x < x_start + sprites[TEX_PLAY_BTN_SMALL].width &&
        mouse_y > y_start && mouse_y < y_start + sprites[TEX_PLAY_BTN_SMALL].height)
            *game_state = SAVE_MENU;
        else if (mouse_x > x_start + 10 && mouse_x < x_start + 10 + sprites[TEX_SETTINGS_BTN].width 
                 && mouse_y > y_start + 200 && mouse_y < y_start + 200 + sprites[TEX_SETTINGS_BTN].height)
            *game_state = SETTINGS;
        else if (mouse_x > x_start && mouse_x < x_start + sprites[TEX_EXIT_BTN_SMALL].width &&
                 mouse_y > y_start + 400 && mouse_y < y_start + 400 + sprites[TEX_EXIT_BTN_SMALL].height)
            *game_state = QUIT;
    }
}

void mx_draw_menu(Texture2D *sprites) {
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();
    const int x_start = screen_width / 2 - 150;
    const int y_start = screen_height / 2 - 150;

    DrawTexture(sprites[TEX_BG_MENU], 0, 0, WHITE);
    DrawRectangle(0, 0, screen_width, screen_height, Fade(BLACK, 0.66f));

    int title_x = screen_width / 2 - sprites[TEX_GAME_TITLE].width / 2;
    int title_y = y_start - sprites[TEX_GAME_TITLE].height - 20; 
    
    DrawTexture(sprites[TEX_GAME_TITLE], title_x, title_y, WHITE);

    DrawTexture(sprites[TEX_PLAY_BTN_SMALL], x_start, y_start, WHITE);
    DrawTexture(sprites[TEX_SETTINGS_BTN], x_start + 4, y_start + 200, WHITE);
    DrawTexture(sprites[TEX_EXIT_BTN_SMALL], x_start, y_start + 400, WHITE);
}

void mx_draw_hp(Texture2D *sprites, int count) {
    int padding = 20; 
    int gap = 10;
    int icon_width = sprites[TEX_HEALTH_POINT].width;
    int total_width = (count * icon_width) + ((count - 1) * gap);
    int start_X = GetScreenWidth() - padding - total_width;
    int pos_Y = padding; 

    for (int i = 0; i < count; i++) {
        int current_X = start_X + (i * (icon_width + gap));
        DrawTexture(sprites[TEX_HEALTH_POINT], current_X, pos_Y, WHITE);
    }
}
