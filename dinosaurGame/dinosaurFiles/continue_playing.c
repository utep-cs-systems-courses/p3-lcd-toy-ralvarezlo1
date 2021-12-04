#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
/* #include "frequency.h" */
#include "switches.h"
#include "draw_shapes.h"
#include "play_track.h"
#include "continue_playing.h"
#include "game_states.h"

void
continue_game(void)
{
  /* if (din1.dy >= 128 && din1.old_dy < din1.dy) { */
  if (dy >= 128 && old_dy < dy) {
    dinosaur_down = 0;
    dinosaur_jump = 0;
  }
  if (mute == 0) {
    /* buzzer_set_period(freq1[songIndex]); */
    play_track();
  } else {
    buzzer_set_period(0);
  }
}
