#include "../includes/game.h"

t_ball ft_ball_constructor(Vector2 pos, Vector2 vel, Vector2 acel, int r)
{
  return ((t_ball){pos, vel, acel, r});
}

void ft_update_ball(t_ball *ball)
{
  ball->vel = Vector2Add(ball->vel, ball->acel);
  ball->pos = Vector2Add(ball->pos, ball->vel);
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

void ft_init_game(t_ball *ball)
{
  InitWindow(WIDTH, HEIGHT, "My first game");
  SetTargetFPS(60);
  ft_init_ball(ball);
}

void ft_input_handler(t_ball *ball)
{
  if (IsKeyDown(KEY_RIGHT))
    ball->pos.x += 1;
  if (IsKeyDown(KEY_LEFT))
    ball->pos.x -= 1;
  if (IsKeyDown(KEY_UP))
    ball->pos.y -= 1;
  if (IsKeyDown(KEY_DOWN))
    ball->pos.y += 1;
}

void ft_event_handler(t_ball *ball)
{
  ft_input_handler(ball);
}

void ft_physics_update(t_ball *ball)
{
  ft_update_ball(ball);
}

void ft_render_update(t_ball *ball)
{
  const char *msg = "Testing my first window! and see if dinamic recentering works";

  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawText(msg, (WIDTH / 2) - strlen(msg) * 5, (HEIGHT / 2) - 10, 20, LIGHTGRAY);
  DrawCircleV(ball->pos, ball->r, RED);
  EndDrawing();
}

void ft_game(t_ball *ball)
{
    ft_event_handler(ball);
    ft_physics_update(ball);
    ft_render_update(ball);
}

int  main(void)
{
  t_game game;

  ft_init_game(&game);
  while (!WindowShouldClose())
    ft_game(&test);
  CloseWindow();
  return (0);
}
