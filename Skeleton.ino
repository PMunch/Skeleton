#include <Arduboy2.h>
#include "src/Images.h"
#include "src/Sequences.h"

Arduboy2 arduboy;  

uint16_t idx = 0;

void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.initRandomSeed();

}
    

void loop() {

  if (!(arduboy.nextFrame())) return;
  
  arduboy.pollButtons();
  arduboy.setCursor(0,0);
  //arduboy.print(idx);

  uint16_t x = idx * 28;
  uint8_t headX = pgm_read_byte(&Sequence[x++]);
  uint8_t headY = pgm_read_byte(&Sequence[x++]);
  uint8_t torsoX = pgm_read_byte(&Sequence[x++]);
  uint8_t torsoY = pgm_read_byte(&Sequence[x++]);
  uint8_t armLeft1_x = pgm_read_byte(&Sequence[x++]);
  uint8_t armLeft1_y = pgm_read_byte(&Sequence[x++]);
  uint8_t armLeft1_i = pgm_read_byte(&Sequence[x++]);
  uint8_t armLeft2_x = pgm_read_byte(&Sequence[x++]);
  uint8_t armLeft2_y = pgm_read_byte(&Sequence[x++]);
  uint8_t armLeft2_i = pgm_read_byte(&Sequence[x++]);
  uint8_t armRight1_x = pgm_read_byte(&Sequence[x++]);
  uint8_t armRight1_y = pgm_read_byte(&Sequence[x++]);
  uint8_t armRight1_i = pgm_read_byte(&Sequence[x++]);
  uint8_t armRight2_x = pgm_read_byte(&Sequence[x++]);
  uint8_t armRight2_y = pgm_read_byte(&Sequence[x++]);
  uint8_t armRight2_i = pgm_read_byte(&Sequence[x++]);

  uint8_t legLeft1_x = pgm_read_byte(&Sequence[x++]);
  uint8_t legLeft1_y = pgm_read_byte(&Sequence[x++]);
  uint8_t legLeft1_i = pgm_read_byte(&Sequence[x++]);
  uint8_t legLeft2_x = pgm_read_byte(&Sequence[x++]);
  uint8_t legLeft2_y = pgm_read_byte(&Sequence[x++]);
  uint8_t legLeft2_i = pgm_read_byte(&Sequence[x++]);
  uint8_t legRight1_x = pgm_read_byte(&Sequence[x++]);
  uint8_t legRight1_y = pgm_read_byte(&Sequence[x++]);
  uint8_t legRight1_i = pgm_read_byte(&Sequence[x++]);
  uint8_t legRight2_x = pgm_read_byte(&Sequence[x++]);
  uint8_t legRight2_y = pgm_read_byte(&Sequence[x++]);
  uint8_t legRight2_i = pgm_read_byte(&Sequence[x++]);

  Sprites::drawSelfMasked(headX, headY, Images::Head, 0);
  Sprites::drawSelfMasked(torsoX, torsoY, Images::Torso, 0);

  //arm l
  Sprites::drawSelfMasked(armLeft1_x, armLeft1_y, Images::Bones, armLeft1_i);
  Sprites::drawSelfMasked(armLeft2_x, armLeft2_y, Images::Bones, armLeft2_i);

  //arm r
  Sprites::drawSelfMasked(armRight1_x, armRight1_y, Images::Bones, armRight1_i);
  Sprites::drawSelfMasked(armRight2_x, armRight2_y, Images::Bones, armRight2_i);

  //leg l
  Sprites::drawSelfMasked(legLeft1_x, legLeft1_y, Images::Bones, legLeft1_i);
  Sprites::drawSelfMasked(legLeft2_x, legLeft2_y, Images::Bones, legLeft2_i);

  //leg r
  Sprites::drawSelfMasked(legRight1_x, legRight1_y, Images::Bones, legRight1_i);
  Sprites::drawSelfMasked(legRight2_x, legRight2_y, Images::Bones, legRight2_i);

  if (arduboy.justPressed(A_BUTTON)) idx = idx + 1;
  if (arduboy.justPressed(B_BUTTON)) idx = idx - 1;

  if (arduboy.everyXFrames(4)) {
    idx = idx + 1;
    if (idx>80) idx = 0;

  }

  arduboy.display(true);

}
