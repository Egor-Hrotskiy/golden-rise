#include "raylib.h"
#include "main.h"

void mx_init_money(Texture2D *sprites, t_eobject *object) {
    const int height = sprites[TEX_MONEY].height;
    const int width = sprites[TEX_MONEY].width;

    object->y_end = object->y_start + height;
    object->x_end = object->x_start + width;
    object->does_damage = 2;
    object->active = true;
}

void mx_update_money(const t_eobject *object, Texture2D *sprites) {
    if (!object->active)
        return;
    float floating = sinf(GetTime() * 3.0f) * 5.0f;
    DrawTexture(sprites[TEX_MONEY], object->x_start, object->y_start + floating, WHITE);
}
