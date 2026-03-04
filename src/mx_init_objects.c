#include "main.h"
#include "raylib.h"

void mx_init_objects(t_envs *env_objects, Texture2D *sprites) {
    int sw = GetScreenWidth() / 1.3;
    int sh = GetScreenHeight() / 1.15;

    env_objects->size = 90;
    env_objects->objects = malloc(sizeof(t_eobject) * env_objects->size);
    t_eobject *obj = env_objects->objects;
    
    for(int i = 0; i < env_objects->size; i++) {
        obj[i].active = true;
        obj[i].does_damage = 0;
    }
    obj[0] = (t_eobject){.x_start = (sw / 2) - 130, .y_start = sh - 240, .type = PIGGYBANK, .checkpoint_number = 0};
    obj[1] = (t_eobject){.x_start = sw * - 0.01 + 20, .y_start = sh * - 0.9 - 180, .type = PIGGYBANK, .checkpoint_number = 1};
    obj[2] = (t_eobject){.x_start = sw * 0.308, .y_start = sh * - 2.842 - 50, .type = PIGGYBANK, .checkpoint_number = 2};
    obj[3] = (t_eobject){.x_start = sw * - 0.239, .y_start = sh * - 5.68, .size = {1, 1}, .type = PIGGYBANK, .checkpoint_number = 3};
    obj[4] = (t_eobject){.x_start = sw * 0.65, .y_start = sh * - 6.615, .size = {1, 1}, .type = PIGGYBANK, .checkpoint_number = 4};
    obj[5] = (t_eobject){.x_start = sw * 0.35, .y_start = sh * 0.15, .size = {5, 1}, .type = PLATFORM};
    obj[6] = (t_eobject){.x_start = sw * 0.38, .y_start = sh * 0.15 - 25, .size = {2, 0}, .type = VERTICAL_SPIKE};
    obj[7] = (t_eobject){.x_start = sw * 0.05, .y_start = sh * 0.08, .size = {2, 9}, .type = PLATFORM, .direction = 1};
    obj[8] = (t_eobject){.x_start = sw * 0.18, .y_start = sh * 0.35, .size = {6, 1}, .type = PLATFORM};
    obj[9] = (t_eobject){.x_start = sw * 0.4, .y_start = sh * 0.5, .size = {8, 2}, .type = PLATFORM};
    obj[10] = (t_eobject){.x_start = sw * 0.45, .y_start = sh * 0.5 - 25, .size = {2, 0}, .type = VERTICAL_SPIKE};
    obj[11] = (t_eobject){.x_start = sw * 0.56, .y_start = sh * 0.08, .size = {5, 1}, .type = PLATFORM};
    obj[12] = (t_eobject){.x_start = sw * 0.56, .y_start = sh * 0.08 - 25, .size = {2, 0}, .type = VERTICAL_SPIKE};
    obj[13] = (t_eobject){.x_start = sw * 0.77, .y_start = sh * 0.37, .size = {3, 5}, .type = PLATFORM};
    obj[14] = (t_eobject){.x_start = sw * 0.85, .y_start = sh * 0.66, .size = {1, 1}, .type = MONEY};
    obj[15] = (t_eobject){.x_start = (sw / 2) - 250, .y_start = sh - 140, .size = {15, 2}, .type = PLATFORM};
    obj[16] = (t_eobject){.x_start = sw * 0.70, .y_start = sh * - 0.35, .size = {2, 9}, .type = PLATFORM};
    obj[17] = (t_eobject){.x_start = sw * 0.13, .y_start = sh * 0.70, .size = {6, 1}, .type = PLATFORM};
    obj[18] = (t_eobject){.x_start = sw * 0.49, .y_start = sh * - 0.26, .size = {5, 1}, .type = PLATFORM};
    obj[19] = (t_eobject){.x_start = sw * 0.34, .y_start = sh * - 0.32, .size = {5, 1}, .type = PLATFORM};
    obj[20] = (t_eobject){.x_start = sw * 0.21, .y_start = sh * - 1.0, .size = {2, 17}, .type = PLATFORM, .direction = 1};
    obj[21] = (t_eobject){.x_start = sw * 0.35, .y_start = sh * - 1.0, .size = {2, 15}, .type = PLATFORM};
    obj[22] = (t_eobject){.x_start = sw * 0.395, .y_start = sh * - 1.0, .size = {10, 1}, .type = PLATFORM};
    obj[23] = (t_eobject){.x_start = sw * - 0.01, .y_start = sh * - 1.0, .size = {10, 1}, .type = PLATFORM};
    obj[24] = (t_eobject){.x_start = sw * - 0.045, .y_start = sh * 0.62, .size = {6, 1}, .type = PLATFORM};
    obj[25] = (t_eobject){.x_start = sw * - 0.18, .y_start = sh * 0.4, .size = {6, 1}, .type = PLATFORM};
    obj[26] = (t_eobject){.x_start = sw * - 0.01, .y_start = sh * 0.62 - 25, .size = {2, 0}, .type = VERTICAL_SPIKE};
    obj[27] = (t_eobject){.x_start = sw * - 0.25, .y_start = sh * 0.65, .size = {6, 1}, .type = PLATFORM};
    obj[28] = (t_eobject){.x_start = sw * - 0.25, .y_start = sh * 0.65 - 25, .size = {2, 0}, .type = VERTICAL_SPIKE};
    obj[29] = (t_eobject){.x_start = sw * - 0.17, .y_start = sh * 0.58, .size = {1, 1}, .type = MONEY};
    obj[30] = (t_eobject){.x_start = sw * 0.050, .y_start = sh * 0.016, .size = {1, 1}, .type = MONEY};
    obj[31] = (t_eobject){.x_start = (sw / 2) + 110, .y_start = sh - 220, .size = {1, 1}, .type = MONEY};
    obj[32] = (t_eobject){.x_start = sw * 0.69, .y_start = sh * 0.7, .size = {10, 3}, .type = PLATFORM};
    obj[33] = (t_eobject){.x_start = sw * 0.65, .y_start = sh * - 1.498, .size = {1, 15}, .type = PLATFORM};
    obj[34] = (t_eobject){.x_start = sw * 0.38, .y_start = sh * - 1.50, .size = {6, 1}, .type = PLATFORM};
    obj[35] = (t_eobject){.x_start = sw * 0.15, .y_start = sh * - 1.64, .size = {6, 1}, .type = PLATFORM};
    obj[36] = (t_eobject){.x_start = sw * - 0.033, .y_start = sh * - 1.82, .size = {6, 2}, .type = PLATFORM};
    obj[37] = (t_eobject){.x_start = sw * - 0.16, .y_start = sh * - 1.69, .size = {3, 3}, .type = PLATFORM};
    obj[38] = (t_eobject){.x_start = sw * - 0.119, .y_start = sh * - 1.75, .size = {1, 1}, .type = MONEY};
    obj[39] = (t_eobject){.x_start = sw * 0.015, .y_start = sh * - 1.82 - 25, .size = {2, 0}, .type = VERTICAL_SPIKE};
    obj[40] = (t_eobject){.x_start = sw * 0.28, .y_start = sh * - 2.267, .size = {2, 8}, .type = PLATFORM};
    obj[41] = (t_eobject){.x_start = sw * 0.095, .y_start = sh * - 2.408, .size = {2, 8}, .type = PLATFORM, .direction = 1};
    obj[42] = (t_eobject){.x_start = sw * 0.46, .y_start = sh * - 2.337, .size = {4, 1}, .type = PLATFORM};
    obj[43] = (t_eobject){.x_start = sw * 0.65, .y_start = sh * - 2.458, .size = {6, 1}, .type = PLATFORM};
    obj[44] = (t_eobject){.x_start = sw * 0.700, .y_start = sh * - 2.46 - 25, .size = {2, 0}, .type = VERTICAL_SPIKE};
    obj[45] = (t_eobject){.x_start = sw * 0.755, .y_start = sh * - 2.52, .size = {1, 1}, .type = MONEY};
    obj[46] = (t_eobject){.x_start = sw * 0.095, .y_start = sh * - 2.700, .size = {2, 8}, .type = PLATFORM, .direction = 1};
    obj[47] = (t_eobject){.x_start = sw * 0.308, .y_start = sh * - 2.790, .size = {9, 1}, .type = PLATFORM};
    obj[48] = (t_eobject){.x_start = sw * 0.78, .y_start = sh * 0.70 - 25, .size = {2, 0}, .type = VERTICAL_SPIKE};
    obj[49] = (t_eobject){.x_start = sw * 0.377, .y_start = sh * - 2.842, .size = {1, 1}, .type = MONEY};
    obj[50] = (t_eobject){.x_start = sw * 0.62, .y_start = sh * - 2.948, .size = {4, 1}, .type = PLATFORM};
    obj[51] = (t_eobject){.x_start = sw * 0.46, .y_start = sh * - 3.09, .size = {4, 1}, .type = PLATFORM};
    obj[52] = (t_eobject){.x_start = sw * 0.241, .y_start = sh * - 3.343, .size = {2, 6}, .type = PLATFORM, .direction = 1};
    obj[53] = (t_eobject){.x_start = sw * 0.632, .y_start = sh * - 3.570, .size = {2, 6}, .type = PLATFORM};
    obj[54] = (t_eobject){.x_start = sw * 0.250, .y_start = sh * - 3.932, .size = {2, 8}, .type = PLATFORM, .direction =1};
    obj[55] = (t_eobject){.x_start = sw * 0.635, .y_start = sh * - 4.311, .size = {2, 8}, .type = PLATFORM};
    obj[56] = (t_eobject){.x_start = sw * 0.445, .y_start = sh * - 3.382, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[57] = (t_eobject){.x_start = sw * 0.445, .y_start = sh * - 3.639, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[58] = (t_eobject){.x_start = sw * 0.460, .y_start = sh * - 3.986, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[59] = (t_eobject){.x_start = sw * 0.488, .y_start = sh * - 4.415, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[60] = (t_eobject){.x_start = sw * 0.315, .y_start = sh * - 4.471, .size = {2, 1}, .type = PLATFORM};
    obj[61] = (t_eobject){.x_start = sw * 0.600, .y_start = sh * - 5.060, .size = {8, 8}, .type = PLATFORM};
    obj[62] = (t_eobject){.x_start = sw * 0.434, .y_start = sh * - 4.678, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[63] = (t_eobject){.x_start = sw * 0.737, .y_start = sh * - 5.138, .size = {1, 1}, .type = MONEY};
    obj[64] = (t_eobject){.x_start = sw * 0.417, .y_start = sh * - 5.163, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[65] = (t_eobject){.x_start = sw * 0.285, .y_start = sh * - 5.201, .size = {2, 1}, .type = PLATFORM};
    obj[66] = (t_eobject){.x_start = sw * 0.159, .y_start = sh * - 5.308, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[67] = (t_eobject){.x_start = sw * 0.0015, .y_start = sh * - 5.380, .size = {2, 1}, .type = PLATFORM};
    obj[68] = (t_eobject){.x_start = sw * - 0.247, .y_start = sh * - 5.569, .size = {8, 8}, .type = PLATFORM};
    obj[69] = (t_eobject){.x_start = sw * 0.098, .y_start = sh * - 5.658, .size = {2, 1}, .type = PLATFORM};
    obj[70] = (t_eobject){.x_start = sw * - 0.239, .y_start = sh * - 5.653, .size = {1, 1}, .type = MONEY};
    obj[71] = (t_eobject){.x_start = sw * 0.293, .y_start = sh * - 5.769, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[72] = (t_eobject){.x_start = sw * 0.49, .y_start = sh * - 5.840, .size = {2, 1}, .type = PLATFORM};
    obj[73] = (t_eobject){.x_start = sw * 0.654, .y_start = sh * - 6.044, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[74] = (t_eobject){.x_start = sw * 0.49, .y_start = sh * - 6.103, .size = {2, 1}, .type = PLATFORM};
    obj[75] = (t_eobject){.x_start = sw * 0.326, .y_start = sh * - 6.219, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[76] = (t_eobject){.x_start = sw * 0.156, .y_start = sh * - 6.270, .size = {2, 1}, .type = PLATFORM};
    obj[77] = (t_eobject){.x_start = sw * 0.351, .y_start = sh * - 6.415, .size = {1, 1}, .type = DOUBLE_COIN};
    obj[78] = (t_eobject){.x_start = sw * 0.54, .y_start = sh * - 6.501, .size = {15, 1}, .type = PLATFORM};
    obj[79] = (t_eobject){.x_start = sw * 0.20, .y_start = sh * 0.13, .size = {4, 1}, .type = PLATFORM};
    obj[80] = (t_eobject){.x_start = sw * 0.24, .y_start = sh * 0.13 - 25, .size = {2, 0}, .type = VERTICAL_SPIKE};
    for (int i = 0; i < env_objects->size; i++) {
        t_eobject *current_object = &env_objects->objects[i];
        if (current_object->type == VERTICAL_SPIKE)
            mx_init_spike(sprites[TEX_SPIKE], current_object);
        else if (current_object->type == PIGGYBANK)
            mx_init_checkpoint(sprites, current_object);
        else if (current_object->type == PLATFORM)
            mx_init_platform(sprites[TEX_DIRT_DEFAULT], current_object);
        else if (current_object->type == MONEY)
            mx_init_money(sprites, current_object);
        else if (current_object->type == DOUBLE_COIN)
            mx_init_double_coin(sprites, current_object);
    }
}

void mx_draw_objects(Texture2D *sprites, t_envs env_objects, Player *my_player, e_game_state game_state, Camera2D camera) {
    float view_width = (GetScreenWidth() / 2.0f) / camera.zoom;
    float view_height = (GetScreenHeight() / 2.0f) / camera.zoom;
    for (int i = 0; i < env_objects.size; i++) {
        t_eobject current_object = env_objects.objects[i];
        bool is_off_screen = (current_object.x_end  < camera.target.x - view_width || current_object.x_start > camera.target.x + view_width 
                              || current_object.y_end < camera.target.y - view_height || current_object.y_start > camera.target.y + view_height);
        if (is_off_screen) 
            continue;
        if (current_object.type == VERTICAL_SPIKE)
            mx_draw_spike(sprites[TEX_SPIKE], &current_object);
        else if (current_object.type == PIGGYBANK)
            mx_draw_checkpoint(sprites, &current_object);
        else if (current_object.type == PLATFORM)
            mx_draw_platform(sprites, &current_object);
        else if (current_object.type == MONEY)
            mx_update_money(&current_object, sprites);
        else if (current_object.type == DOUBLE_COIN)
            mx_update_double_coin(&current_object, sprites);
    }
    
    if (game_state != RESTART)
        mx_draw_player(*my_player);
}
