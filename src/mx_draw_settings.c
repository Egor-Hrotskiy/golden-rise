#include "main.h"
extern Music menuMusic;

void mx_update_settings(e_game_state *game_state, t_settings *settings) {
    Vector2 mouse = GetMousePosition();

    int btnSize = 180;
    int backSize = 250;
    int spacing = 120;
    int rightOffset = 20;
    int shiftRight = 70;

    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2 - 180;

    Rectangle soundRect = { (float)(centerX - backSize - spacing/2 + shiftRight), (float)centerY, (float)backSize, (float)btnSize };
    Rectangle musicRect = { (float)(centerX + spacing/2), (float)centerY, (float)backSize, (float)btnSize };
    Rectangle backRect = { (float)(centerX - backSize / 2 + rightOffset), (float)(centerY + btnSize + 40), (float)backSize, (float)btnSize };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, soundRect)) settings->sound_on = !settings->sound_on;
        if (CheckCollisionPointRec(mouse, musicRect)) { 
            settings->music_on = !settings->music_on;
            if (settings->music_on) 
                SetMusicVolume(menuMusic, 0.6f);
            else 
                SetMusicVolume(menuMusic, 0.0f);
        }
        if (CheckCollisionPointRec(mouse, backRect)) *game_state = MENU;
    }
}
void mx_draw_settings(Texture2D *sprites, t_settings settings) {
    DrawTexture(sprites[TEX_BG_MENU], 0, 0, WHITE);
    
    int btnSize = 180;
    int backSize = 250;
    int spacing = 120;
    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2 - 180;

    int rightOffset = 20; 

    DrawTexture(sprites[settings.sound_on ? TEX_SOUND_ON : TEX_SOUND_OFF], centerX - btnSize - spacing/2, centerY, WHITE);
    DrawTexture(sprites[settings.music_on ? TEX_MUSIC_ON : TEX_MUSIC_OFF], centerX + spacing/2, centerY, WHITE);
    DrawTexture(sprites[TEX_BACK_BTN], (centerX - backSize / 2) + rightOffset, centerY + btnSize + 40, WHITE);
}
