#pragma once

#include <Arduboy2.h>

class Arduboy2Ext : public Arduboy2/*Base*/ {

   public:
     Arduboy2Ext();

     void drawCompressedMirror(int16_t sx, int16_t sy, const uint8_t *bitmap, uint8_t color, bool mirror);

};
