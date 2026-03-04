#include "raylib.h"
#include "main.h"

void mx_init_checkpoint(Texture2D *sprites, t_eobject *object) {
    const int height = sprites[TEX_CHECKPOINT].height;
    const int width = sprites[TEX_CHECKPOINT].width;

    object->y_end = object->y_start + height;
    object->x_end = object->x_start + width;
    object->does_damage = 3;
    object->active = true;
}


void mx_draw_checkpoint(Texture2D *sprites, const t_eobject *object) {
    DrawTexture(sprites[TEX_CHECKPOINT], object->x_start, object->y_start, WHITE);
}
