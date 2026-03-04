#include "main.h"
#include "wind.h"
extern Sound wind_sound;
extern t_settings settings;

void mx_init_wind(t_wind *wind) {
    float sh = GetScreenHeight() / 1.15;
    float x_start = GetScreenWidth() * -0.15f;
    float y_start = sh * -2.690f;
    float width = GetScreenWidth() * 1.0f;  
    float height = (sh * -1.40f) - (sh * -2.690f);
    wind->area = (Rectangle){ x_start, y_start, width, height };
    wind->base_force = 100.0f;
    wind->timer = 0.0f;
    wind->state_duration = 4.5f;
    wind->direction = -1;
    wind->active = true;
}

void mx_update_wind(t_wind *wind, Vector2 player_pos) {
    if (!wind->active) {
        if (IsSoundPlaying(wind_sound)) 
            StopSound(wind_sound);
        return;
    }

    wind->timer += GetFrameTime();

    if (wind->timer >= wind->state_duration) {
        wind->timer = 0;
        wind->direction *= -1;
    }
    
    if (CheckCollisionPointRec(player_pos, wind->area)) {
        float progress = wind->timer / wind->state_duration;
        float intensity = sinf(progress * PI);
        
        SetSoundVolume(wind_sound, intensity);

        if (intensity > 0.01f && !IsSoundPlaying(wind_sound) && settings.sound_on) {
            PlaySound(wind_sound);
        }
    } 
    else if (IsSoundPlaying(wind_sound))
        StopSound(wind_sound);
}

void mx_apply_wind(t_wind wind, Vector2 *next_pos) {
    if (!wind.active) 
        return;

    if (CheckCollisionPointRec(*next_pos, wind.area)) {
        float progress = wind.timer / wind.state_duration;
        float intensity = sinf(progress * PI);
        next_pos->x += (float)wind.direction * wind.base_force * intensity * GetFrameTime();
    }
}
