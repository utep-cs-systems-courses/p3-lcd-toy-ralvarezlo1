#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
/* #include "frequency.h" */
#include "switches.h"
#include "draw_shapes.h"
#include "play_track.h"

int mute = 0;

// game switches state machine
void game_controls()
{
  /* static int songIndex = 0; */
  /* int songArraySize = 4; */
  /* songIndex = (songIndex + 1) % songArraySize; */

  /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
  switch (switch_state_down) {
  case 1: /* reset highscore */
    highscore = 0;
    switch_state_down = 0;
    break;
  case 2: /* jump */
    dinosaur_jump = 1;
    switch_state_down = 0;
    break;
  case 3: /* jump booster */
    dinosaur_down = 1;
    switch_state_down = 0;
    break;
  case 4: /* start/pause */
    dinosaur_jump = 0;
    dinosaur_down = 0;
    mute = playing;
    playing = 1 - playing;
    switch_state_down = 0;
    break;
  case 5: /* mute */
    mute = 1 - mute;
    switch_state_down = 0;
    break;
  default: /* continue */
    continue_game();
    /* if (din1.dy >= 128 && din1.old_dy < din1.dy) { */
    /* if (dy >= 128 && old_dy < dy) { */
    /*   dinosaur_down = 0; */
    /*   dinosaur_jump = 0; */
    /* } */
    /* if (mute == 0) { */
    /*   /\* buzzer_set_period(freq1[songIndex]); *\/ */
    /*   play_track(); */
    /* } else { */
    /*   buzzer_set_period(0); */
    /* } */
    break;
  }
}
