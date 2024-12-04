#include "../includes/game.h"

t_ball ft_ball_constructor(Vector2 pos, Vector2 vel, Vector2 acel, int r)
{
  return ((t_ball){pos, vel, acel, r});
}

void ft_init_ball(t_ball *ball)
{
  ball->pos.x = WIDTH / 2;
  ball->pos.y = HEIGHT / 2;
  ball->vel.x = 0;
  ball->vel.y = 0;
  ball->acel.x = 0;
  ball->acel.y = 0;
  ball->r = 10;
}

void ft_ball_constraints(t_ball *ball)
{
  if (ball->pos.x < 0)
    ball->pos.x = 1;
  if (ball->pos.x > WIDTH)
    ball->pos.x = WIDTH - 1;
  if (ball->pos.y < 0)
    ball->pos.y = 1;
  if (ball->pos.y > HEIGHT)
    ball->pos.y = HEIGHT - 1;
}

void ft_bounce_ball(t_ball *ball)
{
  if (ball->pos.x < 0 || ball->pos.x > WIDTH)
    ball->vel.x *= -1;
  if (ball->pos.y < 0 || ball->pos.y > HEIGHT)
    ball->vel.y *= -1;
}

void ft_update_ball(t_ball *ball, t_game *game)
{
  ball->vel = Vector2Add(ball->vel, ball->acel);
  ball->pos = Vector2Add(ball->pos, Vector2Multiply(ball->vel, (Vector2){game->delta_time, game->delta_time}));
  ft_bounce_ball(ball);
  ft_ball_constraints(ball);
  game->score++;
}

void ft_ball_input_handler(t_ball *ball)
{
  if (IsKeyDown(KEY_W))
    ball->acel.y = -2;
  else if (IsKeyDown(KEY_S))
    ball->acel.y = 2;
  else
    ball->acel.y = 0;
  if (IsKeyDown(KEY_A))
    ball->acel.x = -2;
  else if (IsKeyDown(KEY_D))
    ball->acel.x = 2;
  else
    ball->acel.x = 0;
}

void ft_follow_player(t_ball *ball, Vector2 player)
{
  ball->acel = Vector2Subtract(player, ball->pos);
  ball->acel = Vector2Normalize(ball->acel);
  ball->acel = Vector2Scale(ball->acel, 0.1);
}

void ft_input_handler(t_game *game)
{
  ft_ball_input_handler(&game->ball[0]);
}

void ft_event_handler(t_game *game)
{
  game->delta_time = GetFrameTime();
  game->frame_count++;
  game->fps = 1.0 / game->delta_time;
  ft_input_handler(game);
}

void ft_physics_update(t_game *game)
{
  for (int i = 0; i < 4; i++)
  {
    ft_update_ball(&game->ball[i], game);
    if (i > 0)
      ft_follow_player(&game->ball[i], game->ball[0].pos);
  }
}

void ft_render_ui(t_game *game)
{
  const char *msg = "Testing my first window! and see if dinamic recentering works";
  const char *player = "gecarval";

  DrawText(msg, (WIDTH / 2) - strlen(msg) * 5, (HEIGHT / 2) - 10, 20, LIGHTGRAY);
  DrawFPS(10, 10);
  DrawText(TextFormat("FPS: %i", game->fps), 10, 30, 20, LIGHTGRAY);
  DrawText(TextFormat("Score: %i", game->score), 10, 50, 20, LIGHTGRAY);
  DrawText(TextFormat("Delta Time: %f", game->delta_time), 10, 70, 20, LIGHTGRAY);
  DrawText(TextFormat("Frame count: %i", game->frame_count), 10, 90, 20, LIGHTGRAY);
  DrawText(player, game->ball[0].pos.x - (strlen(player) * 5), game->ball[0].pos.y - 40, 20, RED);
}

void ft_render_game_objects(t_game *game)
{
  for (int i = 0; i < 4; i++)
    DrawCircle(game->ball[i].pos.x, game->ball[i].pos.y, game->ball[i].r, RED);
}

void ft_render_update(t_game *game)
{
  BeginDrawing();
  ClearBackground(RAYWHITE);
  ft_render_ui(game);
  ft_render_game_objects(game);
  EndDrawing();
}

void ft_init_game(t_game *game)
{
  InitWindow(WIDTH, HEIGHT, "My first game");
  SetTargetFPS(60);
  for (int i = 0; i < 4; i++)
    game->ball[i] = ft_ball_constructor((Vector2){WIDTH / 2, HEIGHT / 2},
        (Vector2){4 * i, 4 * i}, (Vector2){0, 0}, 10);
}

void ft_game_loop(t_game *game)
{
  ft_event_handler(game);
  ft_physics_update(game);
  ft_render_update(game);
}

int  main(void)
{
  t_game game;

  ft_init_game(&game);
  while (!WindowShouldClose())
    ft_game_loop(&game);
  CloseWindow();
  return (0);
}
