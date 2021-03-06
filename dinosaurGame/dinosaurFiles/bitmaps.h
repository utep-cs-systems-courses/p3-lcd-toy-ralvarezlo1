#ifndef _BITMAPS_H_
#define _BITMAPS_H_

/* face down - left -> for bit = 8000; bit >>= 1
const unsigned int dinasour_bitmap[16] = {
  0x0000, 0xE800, 0xEA00, 0xEB00, 0xBFFD, 0xFFFF, 0xFFFD, 0xFFFF, 0x0030, 0x0060, 0x00C0, 0x0180, 0x0300, 0x0600, 0x0C00, 0x0000
};
*/

/* face up - right */
const unsigned int dinosaur_bitmap[16] = {
  0x0000, 0x0030, 0x0060, 0x00C0, 0x0180, 0x0300, 0x0600, 0x0C00, 0xFFFF, 0xBFFF, 0xFFFF, 0xBFFD, 0x00D7, 0x0057, 0x0017, 0x0000
};

const unsigned int cactus_bitmap[16] = {
  0x0000, 0x0000, 0x0000, 0x0300, 0x0630, 0x0C60, 0xFFF8, 0xFFFE, 0xFFFE, 0xFFF8, 0x0C60, 0x0630, 0x0300, 0x0000, 0x0000, 0x0000
};

#endif
