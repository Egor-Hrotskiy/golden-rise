#include "raylib.h"
#include "main.h"

void mx_init_double_coin(Texture2D *sprites, t_eobject *object) {
    const int height = sprites[TEX_DOUBLE_COIN].height;
    const int width = sprites[TEX_DOUBLE_COIN].width;

    object->y_end = object->y_start + height + 30;
    object->x_end = object->x_start + width + 30;
    object->does_damage = 4;
    object->active = true;
}

void mx_update_double_coin(const t_eobject *object, Texture2D *sprites) {
    if (!object->active)
        return;
    DrawTexture(sprites[TEX_DOUBLE_COIN], object->x_start, object->y_start, WHITE);
}
