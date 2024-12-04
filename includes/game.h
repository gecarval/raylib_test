#ifndef GAME_H
# define GAME_H

# include "raylib.h"
# include "raymath.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>


// MACROS
# define WIDTH 800
# define HEIGHT 600

// DATA STRUCTURES
typedef struct s_ball
{
  Vector2 pos;
  Vector2 vel;
  Vector2 acel;
  int     r;
} t_ball;

// MAIN GAME ENGINE DATA STRUCTURE
typedef struct s_game
{
  double_t delta_time;
  unsigned int frame_count;
  unsigned int fps;
  unsigned int score;
  t_ball ball[4];
} t_game;

// FUNCTION PROTOTYPES

#endif

