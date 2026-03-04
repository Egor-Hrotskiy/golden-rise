#include "raylib.h"
#include "main.h"

void mx_init_spike(Texture2D spike, t_eobject *object){
    const int height = spike.height;
    const int width = spike.width;

    object->y_end = object->y_start + height - 20;
    object->x_start += 6;
    object->x_end = object->x_start + (width * object->size.x) - 7;
    object->does_damage = 1;
    object->active = true;
}

void mx_draw_spike(Texture2D spike, const t_eobject *object) {
    const int width = spike.width;
    int pos_x = object->x_start;

    for (int i = 0; i < object->size.x; i++) {
        DrawTexture(spike, pos_x, object->y_start, WHITE);
        pos_x += width;
    }
}
