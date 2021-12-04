# makefile configuration
COMMON_OBJECTS		= draw_shapes.o buzzer.o switches.o interrupt_handler.o wdt_handler.o wdInterruptHandler.o play_track.o continue_playing.o
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		        = -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c #or msp430-eld-as

all: dinosaur_game.elf

#additional rules for files
dinosaur_game.elf: ${COMMON_OBJECTS} game_states.o dinosaur_game.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

dinosaur_game_s.elf: ${COMMON_OBJECTS} game_states_s.o dinosaur_game.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

# ${COMMON_OBJECTS}: buzzer.h frequency.h switches.h led_sequence.h

load: dinosaur_game.elf
	msp430loader.sh $^

load_s: dinosaur_game_s.elf
	msp430loader.sh $^

draw_shapes.o: draw_shapes.h bitmaps.h
#interrupt_handler.o: switches.h
#buzzer.o: ../timerLib/libTimer.h buzzer.h
#wdInterruptHandler.o: ../timerLib/libTimer.h buzzer.h frequency.h switches.h draw_shapes.h

clean:
	rm -f *.o *.elf
