#ifndef _DRAW_SHAPES_H_
#define _DRAW_SHAPES_H_

#include <lcdutils.h>

typedef struct Dinosaur_st {
  int dx;
  int dy;
  int old_dx;
  int old_dy;
  u_int color;   /* dinosaur color */
  u_int b_color; /* background color */
  u_int up;	 /* tells the dinasour to go up(1)  or down(0) */
} Dinosaur;

typedef struct Cactus_st {
  int cx;
  int cy;
  int old_cx;
  int old_cy;
  u_int color; 	 /* cactus color */
  u_int b_color; /* background color */
} Cactus;

extern Dinosaur din1;
extern int dy;
extern int old_dy;

short redrawScreen;

extern u_int playing; // The game is ongoing
extern u_int new_game; // Start a new game

extern u_int dinosaur_jump; // Makes the dinasour jump
extern u_int dinosaur_down; // Makes the dinasour go down (faster)

extern u_int score;
extern u_int highscore;
extern const u_int score_col;
extern const u_int highscore_col;

/* draws a score */
void show_score(u_int score, u_int score_col);

/* draws a rectangle */
void draw_rectangle(void);
/* draws an equaleral triangle by starting at the top with a 
   width of 1 and increasing the width by 1
   for every row */
void draw_triangle(void);
/* draws a circle using bresenham's algorithm */
void draw_circle(void);
/* draws a dinasour */
void draw_dinosaur(int dx, int dy, u_int color);
/* draws a cactus */
void draw_cactus(int cx, int cy, u_int color);
/* draws a bird */
void draw_bird(void);

/* handles the dinasour, updates its position and draws it in its new location */
void moving_dinosaur(void);
/* handles a single cactus, updates its position and draws it in its new location */
void moving_cactus(void);

/* verifies if something hit the dinosaur */
void dinosaur_damage(void);

/* initializes the game positions */
void start(void);

/* handles erasing and updating all the shapes */
void movement(void);

#endif // _DRAW_SHAPES_H_
