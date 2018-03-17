#include "Arduboy2Ext.h"

Arduboy2Ext::Arduboy2Ext() : Arduboy2Base() { }

void Arduboy2Ext::clearButtonState() {

  currentButtonState = previousButtonState = 0;

}

struct BitStreamReader {

  const uint8_t *source;
  uint16_t sourceIndex;
  uint8_t bitBuffer;
  uint8_t byteBuffer;


  BitStreamReader(const uint8_t *source) : source(source), sourceIndex(), bitBuffer(), byteBuffer() { }
  
  uint16_t readBits(uint16_t bitCount)
  {
    uint16_t result = 0;
    for (uint16_t i = 0; i < bitCount; i++)
    {
      if (this->bitBuffer == 0)
      {
        this->bitBuffer = 0x1;
        this->byteBuffer = pgm_read_byte(&this->source[this->sourceIndex]);
        ++this->sourceIndex;
      }
      
      if ((this->byteBuffer & this->bitBuffer) != 0)
        result |= (1 << i); // result |= bitshift_left[i];
        
      this->bitBuffer <<= 1;
    }
    return result;
  }
  
};


void Arduboy2Ext::drawCompressedMirror(int16_t sx, int16_t sy, const uint8_t *bitmap, uint8_t color, bool mirror) {

  // set up decompress state

  BitStreamReader cs = BitStreamReader(bitmap);

  // read header

  int width = (int)cs.readBits(8) + 1;
  int height = (int)cs.readBits(8) + 1;
  uint8_t spanColour = static_cast<uint8_t>(cs.readBits(1)); // starting colour

  // no need to draw at all if we're offscreen
  if ((sx + width < 0) || (sx > WIDTH - 1) || (sy + height < 0) || (sy > HEIGHT - 1))
    return;

  // sy = sy - (frame * height);

  int yOffset = abs(sy) % 8;
  int startRow = sy / 8;
  if (sy < 0) {
    startRow--;
    yOffset = 8 - yOffset;
  }
  int rows = height / 8;
  if ((height % 8) != 0)
    ++rows;

  int rowOffset = 0; // +(frame*rows);
  int columnOffset = 0;
  
  if (mirror) {
    columnOffset = width - 1;
  }
  else {
    columnOffset = 0;
  }

  uint8_t byte = 0x00;
  uint8_t bit = 0x01;
  while (rowOffset < rows) {// + (frame*rows))
  
    uint16_t bitLength = 1;
    while (cs.readBits(1) == 0)
      bitLength += 2;

    uint16_t len = cs.readBits(bitLength) + 1; // span length

    // draw the span
    for (uint16_t i = 0; i < len; ++i) {

      if (spanColour != 0)
        byte |= bit;
      bit <<= 1;

      if (bit == 0) // reached end of byte
      {
        // draw
        int bRow = startRow + rowOffset;

        //if (byte) // possible optimisation
        if ((bRow <= (HEIGHT / 8) - 1) && (bRow > -2) && (columnOffset + sx <= (WIDTH - 1)) && (columnOffset + sx >= 0)) {

          int16_t offset = (bRow * WIDTH) + sx + columnOffset;
          
          if (bRow >= 0) {
            int16_t index = offset;
            uint8_t value = byte << yOffset;
            
            if (color != 0)
              sBuffer[index] |= value;
            else
              sBuffer[index] &= ~value;
          }

          if ((yOffset != 0) && (bRow < (HEIGHT / 8) - 1)) {

            int16_t index = offset + WIDTH;
            uint8_t value = byte >> (8 - yOffset);
            
            if (color != 0)
              sBuffer[index] |= value;
            else
              sBuffer[index] &= ~value;
          }
          
        }


        // iterate
        if (!mirror) {
          ++columnOffset;
          if (columnOffset >= width)
          {
            columnOffset = 0;
            ++rowOffset;
          }
        }
        else {
          --columnOffset;
          if (columnOffset < 0) {
            columnOffset = width - 1;
            ++rowOffset;
          }
        }


        // reset byte
        byte = 0x00;
        bit = 0x01;
      }
    }

    spanColour ^= 0x01; // toggle colour bit (bit 0) for next span
  }
}



/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 */
void Arduboy2Ext::drawHorizontalDottedLine(uint8_t x1, uint8_t x2, uint8_t y) {

  for (uint8_t x3 = x1; x3 <= x2; x3+=2) {
    drawPixel(x3, y, WHITE);
  }
  
}


/* ----------------------------------------------------------------------------
 *  Draw a vertical dotted line. 
 */
void Arduboy2Ext::drawVerticalDottedLine(uint8_t y1, uint8_t y2, uint8_t x) {

  for (uint8_t y3 = y1; y3 <= y2; y3+=2) {
    drawPixel(x, y3, WHITE);
  }
  
}


void Arduboy2Ext::setRGBled(uint8_t red, uint8_t green, uint8_t blue)
{
#ifdef ARDUBOY_10 // RGB, all the pretty colors
  // timer 0: Fast PWM, OC0A clear on compare / set at top
  // We must stay in Fast PWM mode because timer 0 is used for system timing.
  // We can't use "inverted" mode because it won't allow full shut off.
  TCCR0A = _BV(COM0A1) | _BV(WGM01) | _BV(WGM00);
  OCR0A = 255 - green;
  // timer 1: Phase correct PWM 8 bit
  // OC1A and OC1B set on up-counting / clear on down-counting (inverted). This
  // allows the value to be directly loaded into the OCR with common anode LED.
  TCCR1A = _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM10);
  OCR1AL = blue;
  OCR1BL = red;
#elif defined(AB_DEVKIT)
  // only blue on DevKit, which is not PWM capable
  (void)red;    // parameter unused
  (void)green;  // parameter unused
  bitWrite(BLUE_LED_PORT, BLUE_LED_BIT, blue ? RGB_ON : RGB_OFF);
#endif
}

void Arduboy2Ext::setRGBled(uint8_t color, uint8_t val)
{
#ifdef ARDUBOY_10
  if (color == RED_LED)
  {
    OCR1BL = val;
  }
  else if (color == GREEN_LED)
  {
    OCR0A = 255 - val;
  }
  else if (color == BLUE_LED)
  {
    OCR1AL = val;
  }
#elif defined(AB_DEVKIT)
  // only blue on DevKit, which is not PWM capable
  if (color == BLUE_LED)
  {
    bitWrite(BLUE_LED_PORT, BLUE_LED_BIT, val ? RGB_ON : RGB_OFF);
  }
#endif
}