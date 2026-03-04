#include "main.h"
#include <stdio.h>
#include <string.h>

int current_slot = 1;
char player_name[11] = "\0";
int letter_count = 0;
int saved_score = 0;
char loaded_name[11] = "None";

void mx_save_game(const char *name, int score, int checkpoint, int max_checkpoint, int max_health, int slot) {
    char fileName[20];
    sprintf(fileName, "resource/save%d.txt", slot);
    FILE *file = fopen(fileName, "w");
    if (file != NULL) {
        fprintf(file, "%s %d %d %d %d", name, score, checkpoint, max_checkpoint, max_health);
        fclose(file);
    }
}

void mx_clear_all_saves(void) {
    for (int i = 1; i <= 3; i++) {
        mx_save_game("None", 0, 0, 0, 3, i);
    }
}

void mx_load_game(Player *player, int slot) {
    char fileName[20];
    sprintf(fileName, "resource/save%d.txt", slot);
    FILE *file = fopen(fileName, "r");

    if (file != NULL) {
        if (fscanf(file, "%10s %d %d %d %d", 
            player_name, 
            &player->score, 
            &player->current_checkpoint, 
            &player->max_checkpoint, 
            &player->max_health) != 5) {
            strcpy(player_name, "None");
            player->score = 0;
            player->current_checkpoint = 0;
            player->max_checkpoint = 0;
            player->max_health = 3;
        }
        fclose(file);
    } 
    else {
        strcpy(player_name, "None");
        player->score = 0;
        player->current_checkpoint = 0;
        player->max_checkpoint = 0;
        player->max_health = 3;
    }
    player->respawned_objects.size = 0;
    for (int i = 0; i < 6; i++) {
        player->respawned_objects.indexes[i] = -1;
    }
    player->health_points = player->max_health;
    player->jump_speed = 0;
    player->stun_timer = 0;
}

void mx_update_save_menu(e_game_state *game_state, Player *player, t_envs env_objects) {
    Vector2 mouse = GetMousePosition();
    int centerX = GetScreenWidth() / 2;

    if (IsKeyPressed(KEY_C)) {
        mx_clear_all_saves();
    }

    Rectangle newSaveRect = { (float)(centerX - 150), 230.0f, 300.0f, 100.0f };

    for (int i = 0; i < 3; i++) {
        Rectangle slotRect = { (float)(centerX - 375), (float)(400 + (i * 100)), 750.0f, 80.0f };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, slotRect)) {
            current_slot = i + 1;
            mx_load_game(player, current_slot);
            TraceLog(LOG_INFO, "%i, %i, %i,\n", player->current_checkpoint, player->max_checkpoint, player->max_health);
            if (strcmp(player_name, "None") != 0) {
                player->position = (Vector2){env_objects.objects[player->current_checkpoint].x_start, env_objects.objects[player->current_checkpoint].y_start};
                player->snap_camera = true;
                *game_state = LEVELS;
            } 
            else {
                player->current_checkpoint = 0;
                player->max_checkpoint = 0; 
                player->score = 0;
                player->max_health = 3;
                player->health_points = 3;
                letter_count = 0;
                player_name[0] = '\0';
                *game_state = CHARACTER_CREATION;
            }
        }
    }

    Rectangle backRect = { (float)(centerX - 110), (float)(GetScreenHeight() - 200), 220.0f, 180.0f };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, newSaveRect)) *game_state = CHARACTER_CREATION;
        if (CheckCollisionPointRec(mouse, backRect)) *game_state = MENU;
    }
}

void mx_draw_save_menu(Texture2D *sprites) {
    DrawTexture(sprites[TEX_BG_MENU], 0, 0, WHITE);
    int centerX = GetScreenWidth() / 2;
    Player temp_p = { 0 };
    char temp_name[11];

    DrawTexture(sprites[TEX_SAVES_TITLE], centerX - (sprites[TEX_SAVES_TITLE].width / 2), 50, WHITE);
    DrawTexture(sprites[TEX_NEW_SAVE], centerX - (sprites[TEX_NEW_SAVE].width / 2), 230, WHITE);
    DrawText("Press 'C' to clear all saves", centerX - 130, 350, 20, GRAY);

    for (int i = 0; i < 3; i++) {
        mx_load_game(&temp_p, i + 1);
        strcpy(temp_name, player_name);
        int yPos = 400 + (i * 100);
        Color rectColor = (current_slot == i + 1) ? Fade(MAROON, 0.3f) : Fade(LIGHTGRAY, 0.5f);
        DrawRectangle(centerX - 375, yPos, 750, 80, rectColor);
        DrawText(player_name, centerX - 350, yPos + 25, 25, MAROON);
        DrawText(TextFormat("Score: %d | Checkpoint: %d", temp_p.score, temp_p.current_checkpoint), centerX - 30, yPos + 25, 25, DARKGRAY);
    }
    mx_load_game(&temp_p, current_slot);
}

void mx_init_new_player(Player *player, t_envs env_objects) {
    player->score = 0;
    player->current_score = 0;
    player->current_checkpoint = 0;
    player->max_checkpoint = 0;
    player->health_points = 3;
    player->max_health = 3;
    player->jump_speed = 0;
    player->stun_timer = 0;
    player->inv_time = 0;
    player->position = (Vector2){env_objects.objects[0].x_start, env_objects.objects[0].y_start};
    player->snap_camera = true;
    player->respawned_objects.size = 0;
    for(int i=0; i<6; i++) 
        player->respawned_objects.indexes[i] = -1;
    for (int i = 0; i < env_objects.size; i++)
        if (env_objects.objects[i].type == MONEY)
            env_objects.objects[i].active = true;
}

void mx_update_char_creation(e_game_state *game_state, Player *player, t_envs env_objects) {
    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (letter_count < 10)) {
            player_name[letter_count] = (char)key;
            player_name[letter_count + 1] = '\0';
            letter_count++;
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (letter_count > 0) {
            letter_count--;
            player_name[letter_count] = '\0';
        }
    }
    if (IsKeyPressed(KEY_ENTER) && letter_count > 0) {
        mx_init_new_player(player, env_objects);
        mx_save_game(player_name, 0, 0, 0, 3, current_slot);
        *game_state = LEVELS;
    }
}

void mx_draw_char_creation(Texture2D *sprites) {
    DrawTexture(sprites[TEX_BG_MENU], 0, 0, WHITE);
    int centerX = GetScreenWidth() / 2;
    DrawText(TextFormat("SLOT %d", current_slot), centerX - 40, 150, 20, MAROON);
    DrawText("Enter name:", centerX - 70, 200, 25, GRAY);
    DrawRectangle(centerX - 160, 250, 320, 50, LIGHTGRAY);
    DrawText(player_name, centerX - 140, 260, 30, MAROON);
}
