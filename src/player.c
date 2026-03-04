#include "player.h"
#include "raylib.h"
#include "main.h"
extern Sound jumpSound;
extern Sound footstepSound;
extern t_settings settings;
extern Sound money_sound;
extern Sound damage_sound;

static void check_collisions(Vector2 *next_pos, Player *player, t_envs objects, bool *on_ground, e_game_state *game_state) {
    for (int i = 0; i < objects.size; i++) {
        t_eobject *obj = &objects.objects[i];
        if (next_pos->x + 20.0f < obj->x_start || next_pos->x - 20.0f > obj->x_end)
            continue;
        if (!obj->active)
            continue;
        if (next_pos->x + 20 > obj->x_start && next_pos->x - 20 < obj->x_end &&
            next_pos->y + 34 > obj->y_start && next_pos->y - 34 < obj->y_end) {
            if (obj->does_damage == 4) {
                if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W)) && player->can_double_jump) {
                    if (settings.sound_on)
                        PlaySound(jumpSound);
                    player->jump_speed = -15.0f;
                    player->coyote_timer = 0;
                    player->jump_buffer_timer = 0;
                    player->can_double_jump = false;
                }
                continue;
            }
            else if (obj->does_damage == 3) {
                if (obj->checkpoint_number > player->max_checkpoint)
                        player->max_checkpoint = obj->checkpoint_number;
                    player->current_checkpoint = obj->checkpoint_number;
                    player->score += player->current_score;
                    player->current_score = 0;
                    player->health_points = player->max_health;
                    player->respawned_objects = (t_respawns){ .indexes = {-1, -1, -1, -1, -1, -1}, .size = 0 };
                    mx_save_game(player_name, player->score, player->current_checkpoint, player->max_checkpoint, player->max_health, current_slot);
                if (IsKeyPressed(KEY_F)) {
                    player->position.x = obj->x_end + 25;
                    if (obj->checkpoint_number == 4)
                        *game_state = WIN;
                    else 
                        *game_state = CHECKPOINT;
                    
                    break;
                }
                continue;
            }
            if (obj->does_damage == 2) {
                PlaySound(money_sound);
                player->current_score += 200;
                player->respawned_objects.indexes[player->respawned_objects.size++] = i;
                obj->active = false;
                continue; 
            }
            if (obj->does_damage == 1 && player->inv_time < 0.1f) {
                PlaySound(damage_sound);
                player->health_points -= 1;
                player->jump_speed = -12.0f;
                player->knockback_x = (player->position.x < (obj->x_start + obj->x_end) / 2) ? -15.0f : 15.0f;
                player->stun_timer = 0.6f;
                player->inv_time = 0.7f;
                continue;
            }
            else if (player->position.y + 34 > obj->y_start) { 
                if (player->position.x + 20 <= obj->x_start) {
                    next_pos->x = obj->x_start - 20;
                    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W)) {
                        if (settings.sound_on)
                            PlaySound(jumpSound);
                        player->jump_speed = -13.0f;
                        player->knockback_x = -10.0f;
                        player->stun_timer = 0.175f;
                        player->can_double_jump = true;
                    }
                }
                else if (player->position.x - 20 >= obj->x_end) {
                    next_pos->x = obj->x_end + 20;
                    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W)) {
                        if (settings.sound_on)
                            PlaySound(jumpSound);
                        player->jump_speed = -12.0f;
                        player->knockback_x = 10.0f;
                        player->stun_timer = 0.2f;
                        player->can_double_jump = true; 
                    }
                }
            }
            if (player->position.y + 34 <= obj->y_start) {
                next_pos->y = obj->y_start - 34;
                player->jump_speed = 0;
                *on_ground = true;
                player->can_double_jump = true;
            }
            else if (player->position.y - 34 >= obj->y_end) {
                next_pos->y = obj->y_end + 34;
                player->jump_speed = 0;
            }
            else if (player->position.x + 20 <= obj->x_start)
                next_pos->x = obj->x_start - 20;
            else if (player->position.x - 20 >= obj->x_end)
                next_pos->x = obj->x_end + 20;
        }
    }
}


static void update_jump(Player *player, Vector2 *next_pos, bool *on_ground) {
    if (next_pos->y >= GetScreenHeight()) {
        player->health_points = 0;
        return;
    }

    player->position = *next_pos;
    player->is_grounded = *on_ground;

    if (player->is_grounded) 
        player->coyote_timer = 0.08f;

    if (player->jump_buffer_timer > 0 && (player->is_grounded || player->coyote_timer > 0)) {
        if (settings.sound_on)
            PlaySound(jumpSound);
        player->jump_speed = -15.0f;
        player->is_grounded = false;
        player->coyote_timer = 0;
        player->jump_buffer_timer = 0;
    }
}

void mx_update_player(Player *player, t_envs objects, Texture2D *sprites, e_game_state *game_state, t_wind current_wind) {
    const float jump_buffer_time = 0.3f;
    float gravity = 45.0f;
    float horizontal_speed = 480.0f;
    
    float delta_time = GetFrameTime();
    float prev_pos = player->position.x;
    Vector2 next_pos = player->position;

    mx_apply_wind(current_wind, &next_pos);
    if (player->coyote_timer > 0)
        player->coyote_timer -= delta_time;
    if (player->inv_time > 0)
        player->inv_time -= delta_time;
    if (player->stun_timer > 0) {
        player->stun_timer -= delta_time;
        next_pos.x += player->knockback_x * (delta_time * 60);
        player->knockback_x *= powf(0.9f, delta_time * 60); 
    }
    else {
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) 
            next_pos.x += horizontal_speed * delta_time;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) 
            next_pos.x -= horizontal_speed * delta_time;    
        player->knockback_x = 0;
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W))
            player->jump_buffer_timer = jump_buffer_time;
    }

    if (player->jump_buffer_timer > 0)
        player->jump_buffer_timer -= delta_time;
    player->jump_speed += gravity * delta_time;
    next_pos.y += player->jump_speed * (delta_time * 60); 

    bool on_ground = false;
    check_collisions(&next_pos, player, objects, &on_ground, game_state);

    if (player->is_grounded && (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)) && settings.sound_on) {
        if (!IsSoundPlaying(footstepSound))
            PlaySound(footstepSound);
    }
    else
        StopSound(footstepSound);

    update_jump(player, &next_pos, &on_ground);

    if (prev_pos - next_pos.x > 0.1f)
        player->texture = sprites[TEX_PLAYER_LEFT];
    else if (next_pos.x - prev_pos > 0.1f)
        player->texture = sprites[TEX_PLAYER_RIGHT];
    else
        player->texture = sprites[TEX_PLAYER_DEFAULT];
}

void mx_draw_player(Player player) {
    Color color = (player.stun_timer > 0.2f) ? RED : WHITE;
    DrawTexture(player.texture, player.position.x - player.texture.width / 2, player.position.y - player.texture.height / 2, color);
}

void mx_update_camera(Camera2D *camera, Player *player) {
    if (player->snap_camera) {
        camera->target = player->position;
        player->snap_camera = false;
        return;
    }
    float lerp_speed = 0.03f;

    camera->target.x += (player->position.x - camera->target.x) * lerp_speed;
    camera->target.y += (player->position.y - camera->target.y) * lerp_speed;
}
