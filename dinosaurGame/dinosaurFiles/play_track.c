#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "frequency.h"
#include "switches.h"
#include "draw_shapes.h"
#include "play_track.h"

static int songIndex = 0;
int songArraySize = 4;

void
play_track(void)
{
  songIndex = (songIndex + 1) % songArraySize;
  buzzer_set_period(freq1[songIndex]);
}
