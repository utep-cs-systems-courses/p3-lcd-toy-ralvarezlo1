#include <msp430.h>
#include "switches.h"
#include "buzzer.h"

char switch_state_down = 0, switch_state_changed;

/* update the interrupt sense bits so 
   interrupts are fired when a switch changes
   position */
static char
switch_update_interrupt_sense1() // MSP430
{
  char p1val = P1IN;
  P1IES |= (p1val & SWITCHES);  // if switch up, sense down
  P1IES &= (p1val | ~SWITCHES); // if switch down, sense up
  return p1val;
}

static char 
switch_update_interrupt_sense2() // BoosterPack
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHESB);	// if switch up, sense down
  P2IES &= (p2val | ~SWITCHESB);	// if switch down, sense up
  return p2val;
}

/* setup switches */
void 
switch_init()
{
  P1REN |=  SWITCHES;           // enables resistors for switches MSP430
  P2REN |=  SWITCHESB;		// enables resistors for switches BoosterPack
  P1IE  |=  SWITCHES;           // enable interrupts from switches MSP430
  P2IE  |=  SWITCHESB;		// enable interrupts from switches BoosterPack
  P1OUT |=  SWITCHES;           // turn on switches so we can read them MSP430
  P2OUT |=  SWITCHESB;		// turn on switches so we can read them BoosterPack
  P1DIR &= ~SWITCHES;           // set switch pins to input MSP430
  P2DIR &= ~SWITCHESB;		// set switch pins to input BoosterPack
  switch_update_interrupt_sense1(); // MSP430
  switch_update_interrupt_sense2(); // BoosterPack
  //led_update();
}

void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense1();
  char p2val = switch_update_interrupt_sense2();
  // Switch reads 0 when down, we want to reverse
  // that so the state variable is 1 when down
  switch_state_down = (p1val & SW1) ? switch_state_down : 1;
  switch_state_down = (p2val & SW2) ? switch_state_down : 2;
  switch_state_down = (p2val & SW3) ? switch_state_down : 3;
  switch_state_down = (p2val & SW4) ? switch_state_down : 4;
  switch_state_down = (p2val & SW5) ? switch_state_down : 5;
}
