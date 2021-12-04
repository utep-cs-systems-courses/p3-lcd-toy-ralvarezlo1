#ifndef switches_included
#define switches_included

#define SW1 BIT3		/* switch1 is p1.3 */
#define SW2 BIT0                /* switch2 is p2.0 */
#define SW3 BIT1                /* switch3 is p2.1 */
#define SW4 BIT2                /* switch4 is p2.2 */
#define SW5 BIT3                /* switch5 is p2.3 */
#define SWITCHES SW1
#define SWITCHESB (SW2 | SW3 | SW4 | SW5)
/* only 1 switch on MSP430 board and 4 extra in the Edukit Boosterpack */

void switch_init(void);
void switch_interrupt_handler(void);
extern char switch_state_down, switch_state_changed;

#endif // included
