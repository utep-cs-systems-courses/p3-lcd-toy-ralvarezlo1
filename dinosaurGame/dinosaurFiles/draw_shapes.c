#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "bitmaps.h"
#include "draw_shapes.h"

// global vars for the dinosaur and cactus
Dinosaur din1;
Cactus cac1;

u_int playing = 1; // The game is ongoing
u_int new_game = 1; // Start a new game
int dy;
int old_dy;

u_int dinosaur_jump = 0; // Makes the dinasour jump
u_int dinosaur_down = 0; // Makes the dinasour go down (faster)

short redrawScreen = 1;

u_int background_color = COLOR_WHITE;
u_int dinosaur_color = COLOR_BLACK;
u_int cactus_color = COLOR_GREEN;
const u_int score_col = 0;
const u_int highscore_col = 60;
const u_int score_row = 10;
const u_int char_width = 6;
const u_int score_color = COLOR_BLUE;

u_int score = 1;
u_int highscore = 0;

/* draws a score */
void show_score(u_int score, u_int score_col)
{
  int comp = 1;
  int score_dig = score;
  while (comp <= score_dig) comp *= 10;
  comp /= 10;
  
  for (int i = 0; comp > 0; i++){
    drawChar5x7((score_col + (char_width * i)), score_row, '0' + score_dig/comp, score_color, background_color);
    score_dig %= comp;
    comp /= 10;
  }
}

void
draw_rectangle(void)
{
  int height = 40;
  int width  = 40;
  int row = 40, col = screenWidth / 2;
  int left_col = col - (width / 2);
  int top_row  = row - (height / 2);

  /* u_int blue = 16, green = 0, red = 31; */
  u_int color = COLOR_WHITE;

  fillRectangle(left_col, row, width, height, color);
}


void
draw_triangle(void)
{
  int height = 40;
  int row = 80, col = screenWidth / 2;

  int step = 0;

  int blue = 31, green = 0, red = 31;

  u_int color = (blue << 11) | (green << 5) | red;

  // draw a n equilateral triangle
  // starts at the top and works down
  // at the first row the width is 1, second 2 and so on
  for (step = 0; step < height; step++) {
    // left side of triangle
    u_char start_col = col - (step / 2);
    // right side of triangle
    u_char end_col   = col + (step / 2);
    u_char width     = end_col - start_col;
    fillRectangle(col - (step / 2), row+step, width, 1, color);
  }
}


void
drawHorizontalLine(u_int x_start, u_int x_end, u_int y, u_int colorBGR)
{
  u_int length = x_end - x_start;
  // set the draw area from the start of the line to the end
  // height is 1 since its a line
  lcd_setArea(x_start, y, x_end, y);
  for (u_int i = 0; i < length; i++) {
    lcd_writeColor(colorBGR);
  }
  
}

void
drawLines(u_int x_coord, u_int y_coord, u_int x_point, u_int y_point, u_int color)
{
  // bottom
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord + y_point, color);
  // top
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord - y_point, color);
  // and the middle two
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord + x_point, color);
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord - x_point, color);
					  
}

void
draw_circle(void)
{
  int x_coord = screenWidth / 2;
  int y_coord = 50;
  int r = 10;
  // first point will be the very top;
  int x_point = 0;
  int y_point = r;
  int decision = 3 - (2 * r);

  u_int color = COLOR_RED;

  drawLines(x_coord, y_coord, x_point, y_point, color);

  while (y_point >= x_point) {
    // move x over one
    x_point++;

    // check decision point
    if (decision > 0) {
      // move y down one
      y_point--;
      decision = decision + 4 * (x_point - y_point) + 10;
    } else {
      decision = decision + 4 * x_point + 6;
    }
    drawLines(x_coord, y_coord, x_point, y_point, color);
  }
}

void
draw_dinosaur(int dx, int dy, u_int color)
{
  /* int dx = 10, dy = 128; // dinosaur x and y */
  /* dx = din1.dx; dy = din1.dy; // dinosaur x and y*/

  int row, col;

  // unsigned int color = COLOR_BLACK;

  /*
bit 0x0001 starts right; therefore bit <<= 1
bit 0x8000 starts left;  therefore bit >>= 1
 */
  unsigned int bit = 1;
  for (row = 0; row < 32; row++) {
    for (col = 0; col < 32; col++) {
      if (dinosaur_bitmap[col/2] & bit) {
	drawPixel(col + dx, row + dy, color);
      }
    }
    if (row % 2 ==1) bit <<= 1;
  }
}

void
draw_cactus(int cx, int cy, u_int color)
{
  /* int cx = 120, cy = 128; // cactus x and y */
  //cx = cac1.cx; cy = cac1.cy; // cactus x and y
  int row, col;

  // unsigned int color = COLOR_GREEN;

  /*
bit 0x0001 starts right; therefore bit <<= 1
bit 0x8000 starts left;  therefore bit >>= 1
 */
  unsigned int bit = 1;
  for (row = 0; row < 32; row++) {
    for (col = 0; col < 32; col++) {
      if (cactus_bitmap[col/2] & bit) {
	drawPixel(col + cx, row + cy, color);
      }
    }
    if (row % 2 ==1) bit <<= 1;
  }
}

/* handles the dinasour, updates its position and draws it in its new location */
void moving_dinosaur(void)
{
  if (din1.dy <= LONG_EDGE_PIXELS - 80) { //80
    din1.up = 0;
  } else if (din1.dy == LONG_EDGE_PIXELS - 32) { //128
    din1.up = 1;
  }
  din1.old_dy = din1.dy;
  if (din1.up == 0) {
    if (dinosaur_down && din1.dy < 120) {
      din1.dy+= 8;
    } else {
      din1.dy+= 1;
    }
  } else {
    if (dinosaur_down) {
      din1.dy-= 16;
    } else {
      din1.dy-= 4;
    }
  }
  draw_dinosaur(din1.old_dx, din1.old_dy, din1.b_color);
  draw_dinosaur(din1.dx, din1.dy, din1.color);
}

/* handles a single cactus, updates its position and draws it in its new location */
void moving_cactus(void)
{
  cac1.old_cx = cac1.cx;
  cac1.cx-=2;
  if (cac1.cx <= -32) {
    cac1.cx = 120;
  }
  draw_cactus(cac1.old_cx, cac1.old_cy, cac1.b_color);
  draw_cactus(cac1.cx, cac1.cy, cac1.color);
}

/* verifies if something hit the dinosaur */
void dinosaur_damage(void)
{
  //   dinosaur before cactus   &&   dinosaur after cactus
  if ((cac1.cx <= din1.dx + 22) && (cac1.cx >= din1.dx - 12)) {
    // dinasour is not high enough to void the cactus
    if ((din1.dy + 30) >= cac1.cy) {
      new_game = 1;
      playing = 0;
    }
  }
}

/* initializes the game positions */
void start(void)
{
  // change background to white
  clearScreen(COLOR_WHITE);

  // set values for the dinosaur
  din1.dx = 10;
  din1.dy = 128;
  din1.old_dx = din1.dx;
  din1.old_dy = din1.dy;
  din1.color = dinosaur_color;
  din1.b_color = background_color;
  din1.up = 1;
  draw_dinosaur(din1.dx, din1.dy, din1.color);

  // set values for the cactus
  cac1.cx = 120;
  cac1.cy = 128;
  cac1.old_cx = cac1.cx;
  cac1.old_cy = cac1.cy;
  cac1.color = cactus_color;
  cac1.b_color = background_color;
  draw_cactus(cac1.cx, cac1.cy, cac1.color);

  // display score
  show_score(score, score_col);
  show_score(highscore, highscore_col);
}

/* handles erasing and updating all the shapes */
void movement(void)
{
  dy = din1.dy;
  old_dy = din1.old_dy;

  if (new_game == 1) {
    start();
    if (score > highscore) highscore = score;
    show_score(highscore, highscore_col);
    new_game = 0;
    score = 0;
  } else {
    if (dinosaur_jump) {
      moving_dinosaur();
    }
    moving_cactus();
    dinosaur_damage();
    show_score(score, score_col);
  }
  if (playing == 0) {
    draw_circle();
  } else {
    draw_rectangle();
  }
}
