#ifndef WIND_H
#define WIND_H

#include "raylib.h"
#include <math.h>

typedef struct s_wind {
    Rectangle area;
    float base_force;
    float timer;
    float speed_factor;
    float state_duration;
    int direction; 
    bool active;
}              t_wind;

void mx_init_wind(t_wind *wind);
void mx_apply_wind(t_wind wind, Vector2 *next_pos);
void mx_draw_wind_zone(t_wind *wind);
void mx_update_wind(t_wind *wind, Vector2 player_pos);

#endif
