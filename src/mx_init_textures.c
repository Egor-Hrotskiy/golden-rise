#include "raylib.h"
#include "main.h"

void mx_init_textures(Texture2D *sprites) {
    const t_texture textures[] = {
    {"resource/dirt_default.png",    false, 0, 0},
    {"resource/spike.png",           false, 0, 0},
    {"resource/green_platform_left.png", true , 32, 32},
    {"resource/green_platform_right.png", true , 32, 32},
    {"resource/play_button.png",     true, 340, 180},
    {"resource/play_button.png",     true, 290, 180},
    {"resource/player_default.png",  true, 70, 70},
    {"resource/settings_button.png", true, 290, 180},
    {"resource/exit_button.png",     true, 340, 180},
    {"resource/exit_button.png",     true, 290, 180},
    {"resource/background_menu.jpg", true, GetScreenWidth(), GetScreenHeight()},
    {"resource/health_point.png",    true, 80, 80},
    {"resource/player_left.png",     true, 70, 70},
    {"resource/player_right.png",    true, 70, 70}, 
    {"resource/restart_button.png", true, 180, 180},
    {"resource/money_default.png", true, 70, 35},
    {"resource/sound_default.png", true, 250, 180}, 
    {"resource/sound_off.png", true, 250, 180},
    {"resource/music_default.png", true, 250, 180},
    {"resource/music_off.png", true, 250, 180}, 
    {"resource/back_button.png", true, 250, 180}, 
    {"resource/first_background.jpeg", true, GetScreenWidth(), GetScreenHeight()},
    {"resource/piggybank.png", true, 100, 100}, 
    {"resource/next_button.png", true, 220, 180}, 
    {"resource/previous_button.png", true, 220, 180},
    {"resource/buy_button.png", true, 220, 180},
    {"resource/back_button.png", true, 220, 180}, 
    {"resource/green_platform_center.png", true, 32, 32}, 
    {"resource/blue_platform_left.png", true, 32, 32},
    {"resource/blue_platform_right.png", true, 32, 32}, 
    {"resource/blue_platform_center.png", true, 32, 32}, 
    {"resource/dirt_default_mountain.png", true, 32, 32}, 
    {"resource/second_background.png", true, GetScreenWidth(), GetScreenHeight()}, 
    {"resource/double_coin.png", true, 64, 64}, 
    {"resource/gold_platform_left.png", true, 32, 32}, 
    {"resource/gold_platform_right.png", true, 32, 32},
    {"resource/gold_platform_center.png", true, 32, 32},
    {"resource/third_background.jpeg", true, GetScreenWidth(), GetScreenHeight()}, 
    {"resource/sky_dirt_default.png", true, 32, 32}, 
    {"resource/pause.png", true, 400, 200}, 
    {"resource/you_lost.png", true, 400, 200},
    {"resource/finish.png", true, 220, 180},
    {"resource/saves.png", true, 400, 150},
    {"resource/new_save.png", true, 300, 100},
    {"resource/golden_rise.png", true, 600, 200},
    {"resource/you_win.png", true, 450, 200}
    };
    const int textures_size = sizeof(textures) / sizeof(t_texture);
    
    for (int i = 0; i < textures_size; i++) {
        if (textures[i].resize == true) {
            Image temp = LoadImage(textures[i].source);
            ImageAlphaCrop(&temp, 0.0f);
            ImageResizeNN(&temp, textures[i].x_size, textures[i].y_size);
            sprites[i] = LoadTextureFromImage(temp);
            UnloadImage(temp);
        }
        else 
            sprites[i] = LoadTexture(textures[i].source); 
    }
}
