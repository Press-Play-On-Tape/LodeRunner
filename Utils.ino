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
void drawHorizontalDottedLine(uint8_t x1, uint8_t x2, uint8_t y) {

  for (uint8_t x3 = x1; x3 <= x2; x3+=2) {
    arduboy.drawPixel(x3, y, WHITE);
  }
  
}



/* ----------------------------------------------------------------------------
 *  Draw a vertical dotted line. 
 */
void drawVerticalDottedLine(uint8_t x, uint8_t y1, uint8_t y2) {

  for (uint8_t y3 = y1; y3 <= y2; y3+=2) {
    arduboy.drawPixel(x, y3, WHITE);
  }
  
}


boolean isSolid(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
      return true;

    default:
      return false;

  }

}


boolean canBeStoodOn(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
    case LevelElement::Ladder:
    case LevelElement::LadderLevel:
      return true;

    default:
      return false;

  }

}


boolean canBeFallenOn(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Brick:
    case LevelElement::Solid:
    case LevelElement::Rail:
    case LevelElement::Ladder:
    case LevelElement::LadderLevel:
      return true;

    default:
      return false;

  }

}

boolean canBeOccupied(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Blank:
    case LevelElement::Ladder:
    case LevelElement::Rail:
    case LevelElement::LadderLevel:
      return true;

    default:
      return false;

  }

}


boolean canBeFallenInto(LevelElement levelElement) {

  switch (levelElement) {

    case LevelElement::Blank:
    case LevelElement::Brick_4:
    case LevelElement::Brick_Transition:
    case LevelElement::Brick_Close_1:
      return true;

    default:
      return false;

  }

}
// boolean inCellXY(int16_t x, int16_t y) {

//   return (x % gridSize == 0) && (y % gridSize == 0);

// }


// boolean inCell(int16_t z) {

//   return (z % gridSize == 0);

// }


boolean inCellX() {

  return ((player.x - level.xOffset) % gridSize == 0);

}

boolean inCellX(uint8_t margin) {

  uint8_t rem = (player.x - level.xOffset) % gridSize;
  return (rem > (gridSize / 2) ? gridSize - rem : rem) <= margin;

}

boolean inCellY() {

  return ((player.y - level.yOffset) % gridSize == 0);

}

boolean inCellY(uint8_t margin) {

  uint8_t rem = (player.y - level.yOffset) % gridSize;

  return (rem > (gridSize / 2) ? gridSize - rem : rem) <= margin;

}
