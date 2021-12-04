#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "buzzer.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

void main()
{
  configureClocks(); // initialize clocks
  lcd_init(); // initialize display
  switch_init(); // initialize switches
  buzzer_init(); // initialize buzzer

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  // clear the screen in case something is already there
  clearScreen(COLOR_BLACK);
  
  // start(); // draw dinasour, cactus and scores
  
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      movement();
    }
    or_sr(0x10);	/**< CPU OFF */
  }
}
