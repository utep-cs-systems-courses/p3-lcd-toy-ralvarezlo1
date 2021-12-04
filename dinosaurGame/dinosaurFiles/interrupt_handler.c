#include <msp430.h>
#include "switches.h"

/* Switches are on P1 (S2), but 
   so are other devices */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      // did a button cause this interrupt?
    P1IFG &= ~SWITCHES;		      // clear pending sw interrupts
    switch_interrupt_handler();	      // single handler for all switches
  }
}

/* Switches are on P2 (S0, 1, 2 & 3), but 
   so are other devices */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHESB) {      // did a button cause this interrupt?
    P2IFG &= ~SWITCHESB;      // clear pending sw interrupts
    switch_interrupt_handler();      // single handler for all switches
  }
}
