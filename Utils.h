#pragma once

#include "src/utils/Arduboy2Ext.h"

/* ----------------------------------------------------------------------------
 *  A better absolute!
 */
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}

/* ----------------------------------------------------------------------------
 *  Return the upper 4 bits of a byte.
 */
uint8_t leftValue(uint8_t val) {

  return val >> 4; 
      
}


/* ----------------------------------------------------------------------------
 *  Return the lower 4 bits of a byte.
 */
uint8_t rightValue(uint8_t val) {

  return val & 0x0F; 
      
}


/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 */
void drawHorizontalDottedLine(Arduboy2Ext *arduboy, uint8_t x1, uint8_t x2, uint8_t y) {

  for (uint8_t x3 = x1; x3 <= x2; x3+=2) {
    arduboy->drawPixel(x3, y, WHITE);
  }
  
}

