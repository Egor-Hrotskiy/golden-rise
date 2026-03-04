#include "raylib.h"
#include "main.h"
Sound jumpSound;
Sound wind_sound;
Sound footstepSound;
Sound death_sound;
Sound money_sound;
Music menuMusic;
Sound damage_sound;
t_settings settings = { true, true };


static void respawn_objects(t_respawns *objects, t_envs env_objects) {
    for (int i = 0; i < objects->size; i++) {
        if (objects->indexes[i] != -1)
            env_objects.objects[objects->indexes[i]].active = true;
        objects->indexes[i] = -1;
    }
    objects->size = 0;
}

static void update_level(t_envs env_objects, Player *my_player, e_game_state *game_state, Texture2D *sprites, t_wind *current_wind) {
    if (*game_state == LEVELS) {
        mx_update_wind(current_wind, my_player->position);
        mx_update_player(my_player, env_objects, sprites, game_state, *current_wind);
        if (my_player->health_points <= 0) {
            PlaySound(death_sound);
            respawn_objects(&my_player->respawned_objects, env_objects);
            *game_state = RESTART;
            my_player->position = (Vector2){env_objects.objects[my_player->current_checkpoint].x_start, env_objects.objects[my_player->current_checkpoint].y_start};
            my_player->health_points = 3;
            my_player->jump_speed = 0;
            my_player->stun_timer = 0;
            my_player->health_points = my_player->max_health;
            my_player->inv_time = 0;
            my_player->current_score = 0;
            my_player->snap_camera = true;
        }
    }
}

static void draw_level(Texture2D *sprites, t_envs env_objects, Player *my_player, e_game_state *game_state, Camera2D camera) {
    BeginMode2D(camera);
    mx_draw_objects(sprites, env_objects, my_player, *game_state, camera);
    EndMode2D();
    if (*game_state == LEVELS)
        mx_draw_hp(sprites, my_player->health_points);
    else if (*game_state == PAUSE)
        mx_draw_pause(sprites);
}

static void shift_background(Player my_player, Texture2D *sprites) {
    float screen_height = (float)GetScreenHeight();
    float player_y = my_player.position.y;
    
    float fade_1_start = screen_height * -0.9f - 300.0f; 
    float fade_1_end = screen_height * -0.9f - 400.0f;
    float alpha_1 = (player_y - fade_1_start) / (fade_1_end - fade_1_start);
    alpha_1 = fmaxf(0.0f, fminf(1.0f, alpha_1));

    float base_calc = (screen_height / 1.15f) * -2.842f;
    float fade_2_start = base_calc + 80.0f;
    float fade_2_end = base_calc + 10.0f;
    float alpha_2 = (player_y - fade_2_start) / (fade_2_end - fade_2_start);
    alpha_2 = fmaxf(0.0f, fminf(1.0f, alpha_2));

    if (alpha_1 < 1.0f) {
        DrawTexture(sprites[TEX_FIRST_BG], 0, 0, WHITE);
        if (alpha_1 > 0.0f)
            DrawTexture(sprites[TEX_SECOND_BG], 0, 0, Fade(WHITE, alpha_1));
    } 
    else if (alpha_2 < 1.0f) {
        DrawTexture(sprites[TEX_SECOND_BG], 0, 0, WHITE);
        if (alpha_2 > 0.0f)
            DrawTexture(sprites[TEX_THIRD_BG], 0, 0, Fade(WHITE, alpha_2));
    } 
    else
        DrawTexture(sprites[TEX_THIRD_BG], 0, 0, WHITE);
}

static void shift_music(Player my_player, Music menu_music, Music second_music, Music third_music) {
    UpdateMusicStream(menu_music);
    UpdateMusicStream(second_music);
    UpdateMusicStream(third_music);

    float screen_height = (float)GetScreenHeight();
    float player_y = my_player.position.y;

    float fade_1_start = screen_height * -0.9f - 100.0f; 
    float fade_1_end = screen_height * -0.9f - 300.0f;
    float alpha_1 = (player_y - fade_1_start) / (fade_1_end - fade_1_start);
    alpha_1 = fmaxf(0.0f, fminf(1.0f, alpha_1));

    float base_calc = (screen_height / 1.15f) * -2.842f;
    float fade_2_start = base_calc + 80.0f;
    float fade_2_end = base_calc + 10.0f;
    float alpha_2 = (player_y - fade_2_start) / (fade_2_end - fade_2_start);
    alpha_2 = fmaxf(0.0f, fminf(1.0f, alpha_2));

    if (settings.music_on) {
        if (alpha_1 < 1.0f) {
            SetMusicVolume(menu_music, 1.0f - alpha_1);
            SetMusicVolume(second_music, alpha_1);
            SetMusicVolume(third_music, 0.0f);
        } 
        else {
            SetMusicVolume(menu_music, 0.0f);
            SetMusicVolume(second_music, 1.0f - alpha_2);
            SetMusicVolume(third_music, alpha_2);
        }
    } 
    else {
        SetMusicVolume(menu_music, 0.0f);
        SetMusicVolume(second_music, 0.0f);
        SetMusicVolume(third_music, 0.0f);
    }
}

int main(void) {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_FULLSCREEN_MODE);
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Golden Rise");
    t_envs env_objects;
    env_objects.size = 0;
    Texture2D *sprites = malloc(sizeof(Texture2D) * TEX_COUNT);
    
    mx_init_textures(sprites);
    mx_init_objects(&env_objects, sprites);
    float centerX = (float)GetScreenWidth() / 2.0f * 1.3;
    float groundY = (float)GetScreenHeight() - 200.0f * 1.3;
    Player my_player = { {centerX, groundY}, 8.0f, 0.0f, true, sprites[TEX_PLAYER_DEFAULT], 0, 0, 3, 0, 0, 0, 0, 0, {{-1, -1, -1, -1, -1, -1}, 0}, 0, 0, 3, true, true};
    my_player.position = (Vector2){env_objects.objects[my_player.current_checkpoint].x_start, env_objects.objects[my_player.current_checkpoint].y_start};
    my_player.snap_camera = true;
    Camera2D camera = { 0 };
    camera.target = my_player.position;
    camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.9f;
    my_player.snap_camera = true;
    my_player.position = (Vector2){env_objects.objects[my_player.current_checkpoint].x_start, env_objects.objects[my_player.current_checkpoint].y_start};;
    e_game_state game_state = MENU;
    SetAudioStreamBufferSizeDefault(8192);
    InitAudioDevice();
    Music third_music = LoadMusicStream("resource/third_music.mp3");
    Music win_music = LoadMusicStream("resource/win_music.mp3");
    Music second_music = LoadMusicStream("resource/second_music.mp3");
    menuMusic = LoadMusicStream("resource/background_music.mp3");
    jumpSound = LoadSound("resource/jump.wav");
    wind_sound = LoadSound("resource/wind_sound.mp3");
    footstepSound = LoadSound("resource/footsteps.wav");
    death_sound = LoadSound("resource/death.wav");
    money_sound = LoadSound("resource/money.wav");
    damage_sound = LoadSound("resource/damage_sound.wav");
    PlayMusicStream(second_music);
    SetMusicVolume(second_music, 0.6f);
    PlayMusicStream(menuMusic);
    SetMusicVolume(menuMusic, 0.6f);
    PlayMusicStream(third_music);
    SetMusicVolume(third_music, 0.6f);
    PlayMusicStream(win_music);
    SetMusicVolume(win_music, 0.6f);
    t_wind level_wind;
    mx_init_wind(&level_wind);

    while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_P))
        game_state = (game_state == LEVELS) ? PAUSE : (game_state == PAUSE ? LEVELS : game_state);
    if (game_state != LEVELS && IsKeyPressed(KEY_M))
        game_state = (game_state == PAUSE) ? MENU : (game_state == MENU ? PAUSE : game_state);
    if (game_state == QUIT) 
        break;
    switch (game_state) {
        case QUIT:
            break;
        case GAMEPLAY:
            break;
        case LEVELS:
            HideCursor();
            shift_music(my_player, menuMusic, second_music, third_music);
            mx_update_camera(&camera, &my_player); 
            update_level(env_objects, &my_player, &game_state, sprites, &level_wind);
            break;
       case MENU:
            ShowCursor();
            UpdateMusicStream(menuMusic);
            mx_update_menu(&game_state, sprites);
            break;
        case SAVE_MENU:
            ShowCursor();
            UpdateMusicStream(menuMusic);
            mx_update_save_menu(&game_state, &my_player, env_objects);
            break;
        case CHARACTER_CREATION:
            DrawTexture(sprites[TEX_BG_MENU], 0, 0, WHITE); 
            mx_update_char_creation(&game_state, &my_player, env_objects);
            break;
        case PAUSE:
            UpdateMusicStream(menuMusic);
            mx_update_pause(&game_state, sprites);
            ShowCursor();
            break;
        case RESTART:
            UpdateMusicStream(menuMusic);
            ShowCursor();
            mx_update_restart(&game_state, sprites);
            break;
        case SETTINGS:
            UpdateMusicStream(menuMusic);
            ShowCursor();
            mx_update_settings(&game_state, &settings);
            break;
        case CHECKPOINT:
            UpdateMusicStream(menuMusic);
            ShowCursor();
            mx_update_checkpoint_menu(&game_state, &my_player, env_objects);
            break;
        case WIN:
            if (settings.music_on) 
                UpdateMusicStream(win_music);
            ShowCursor();
            mx_save_game(player_name, my_player.score, my_player.current_checkpoint, my_player.max_checkpoint, my_player.max_health, current_slot);
            mx_update_win(&game_state, &my_player, env_objects);
            break;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (game_state) {
        case QUIT:
            break;
        case GAMEPLAY:
            break;
        case LEVELS:
        case PAUSE:
            shift_background(my_player, sprites);
            draw_level(sprites, env_objects, &my_player, &game_state, camera);
            break;
        case MENU:
                mx_draw_menu(sprites);
                break;
        case SAVE_MENU:
                mx_draw_save_menu(sprites);
            break;
        case CHARACTER_CREATION: 
                mx_draw_char_creation(sprites); 
            break; 
        case RESTART:
            DrawTexture(sprites[TEX_FIRST_BG], 0, 0, WHITE);
            draw_level(sprites, env_objects, &my_player, &game_state, camera);
            mx_draw_restart(sprites);
            break;
        case SETTINGS:
            mx_draw_settings(sprites, settings);
            break;
        case CHECKPOINT:
            shift_background(my_player, sprites);
            draw_level(sprites, env_objects, &my_player, &game_state, camera);
            mx_draw_checkpoint_menu(sprites);
            break;
        case WIN:
            shift_background(my_player, sprites);
            draw_level(sprites, env_objects, &my_player, &game_state, camera);
            mx_draw_win(sprites);
        default: 
            break;
    }
    EndDrawing();
}
    free(env_objects.objects);
    for (int i = 0; i < TEX_COUNT; i++)
    UnloadTexture(sprites[i]);
    free(sprites);
    UnloadMusicStream(win_music);
    UnloadMusicStream(second_music);
    UnloadMusicStream(menuMusic);
    UnloadSound(jumpSound);
    UnloadSound(wind_sound);
    UnloadSound(money_sound);
    UnloadSound(death_sound);
    UnloadSound(damage_sound);
    UnloadSound(footstepSound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
