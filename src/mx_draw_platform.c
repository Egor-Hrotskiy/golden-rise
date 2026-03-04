#include "raylib.h"
#include "main.h"

void mx_init_platform(Texture2D platform_block, t_eobject *object) {
    const int height = platform_block.height;
    const int width = platform_block.width;
    
    object->y_end = object->y_start + (height * object->size.y);
    object->x_end = object->x_start + (width * object->size.x);
    object->does_damage = 0;
    object->active = true;
}

void mx_draw_platform(Texture2D *sprites, const t_eobject *object) {
    const int width = sprites[TEX_DIRT_DEFAULT].width;
    const int height = sprites[TEX_DIRT_DEFAULT].height;
    bool isVertical = object->size.y > object->size.x;
    bool is_second_level = object->y_start <= GetScreenHeight() * - 0.9 - 190;
    bool is_third_level = object->y_start <= (GetScreenHeight() / 1.15f) * -2.842f - 100.0f;

    for (int y = 0; y < object->size.y; y++) {
        for (int x = 0; x < object->size.x; x++) {
            int pos_x = object->x_start + (x * width);
            int pos_y = object->y_start + (y * height);
            Texture2D dirt_texture = is_second_level? (is_third_level? sprites[TEX_SKY_DIRT_DEFAULT] : sprites[TEX_MOUNTAIN_DIRT_DEFAULT]) : sprites[TEX_DIRT_DEFAULT];
            Texture2D left_platform = is_second_level?  (is_third_level? sprites[TEX_GOLD_PLATFORM_LEFT] : sprites[TEX_BLUE_PLATFORM_LEFT]) : sprites[TEX_GREEN_PLATFORM_LEFT];
            Texture2D right_platform = is_second_level? (is_third_level? sprites[TEX_GOLD_PLATFORM_RIGHT] : sprites[TEX_BLUE_PLATFORM_RIGHT]) : sprites[TEX_GREEN_PLATFORM_RIGHT];
            Texture2D center_platform = is_second_level? (is_third_level? sprites[TEX_GOLD_PLATFORM_CENTER] : sprites[TEX_BLUE_PLATFORM_CENTER]) : sprites[TEX_GREEN_PLATFORM_CENTER];
            float rotation = 0.0f;
            bool useRotation = false;

            if (!isVertical) {
                if (y == 0) {
                    if (x == 0) 
                        dirt_texture = left_platform;
                    else if (x == object->size.x - 1) 
                        dirt_texture = right_platform;
                    else 
                        dirt_texture = center_platform;
                }
            } 
            else {
                bool isLeftEdge = (x == 0);
                bool isRightEdge = (x == object->size.x - 1);

                if (isLeftEdge && (object->size.x >= 3 || object->direction <= 0)) {
                    useRotation = true;
                    if (y == 0) dirt_texture = right_platform;
                    else if (y == object->size.y - 1) dirt_texture = left_platform;
                    else dirt_texture = center_platform;
                    rotation = -90.0f; 
                } 
                else if (isRightEdge && (object->size.x >= 3 || object->direction > 0)) {
                    useRotation = true;
                    if (y == 0) dirt_texture = left_platform;
                    else if (y == object->size.y - 1) dirt_texture = right_platform;
                    else dirt_texture = center_platform;
                    rotation = 90.0f;
                }
            }

            if (useRotation) {
                Rectangle source = { 0.0f, 0.0f, (float)dirt_texture.width, (float)dirt_texture.height };
                Rectangle dest = { (float)pos_x, (float)pos_y, (float)width, (float)height };
                Vector2 origin = { (float)width / 2, (float)height / 2 };
                dest.x += origin.x; 
                dest.y += origin.y;
                DrawTexturePro(dirt_texture, source, dest, origin, rotation, WHITE);
            }
            else
                DrawTexture(dirt_texture, pos_x, pos_y, WHITE);
        }
    }
}
