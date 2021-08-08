#pragma once

namespace Lines
{
  // 26 7
  const uint8_t PROGMEM hubScoreBack[] = {
    0x24, 0x5a, 0x55, 0x55, 0x2d, 0x1e, 0x22, 0x5d, 0x55, 0x52, 0x3c, 0x22, 0x5d, 0x5d, 0x22, 0x3c, 0x42, 0x2d, 0x55, 0x2a, 0x3c, 0x42, 0x55, 0x55, 0x5d, 0x22, 
  };

  // 24 5
  const uint8_t PROGMEM hubScore[] = {
    0x12, 0x15, 0x15, 0x09, 0x00, 0x0e, 0x11, 0x11, 0x10, 0x00, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x1e, 0x09, 0x15, 0x02, 0x00, 0x1e, 0x15, 0x15, 0x11, 
  };

  // 24 5
  const uint8_t PROGMEM hubLevel[] = {
    0x1e, 0x11, 0x10, 0x10, 0x00, 0x1e, 0x15, 0x15, 0x11, 0x00, 0x07, 0x08, 0x10, 0x0e, 0x00, 0x1e, 0x15, 0x15, 0x11, 0x00, 0x1e, 0x11, 0x10, 0x10, 
  };

  // 78 8
  const uint8_t PROGMEM gameover[] = {
    0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xf3, 0xf3, 0x00, 0x00, 0xff, 0xff, 0x33, 0x33, 0x33, 0x33, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x03, 0x03, 0x0f, 0x0f, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xcf, 0xcf, 0xcf, 0xcf, 0xc3, 0xc3, 0x00, 0x00, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0x00, 0x00, 0x3f, 0x3f, 0xc0, 0xc0, 0xc0, 0xc0, 0x3f, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xcf, 0xcf, 0xcf, 0xcf, 0xc3, 0xc3, 0x00, 0x00, 0xff, 0xff, 0x33, 0x33, 0xf3, 0xf3, 0x3f, 0x3f, 
  };

  // 39 5
  const uint8_t PROGMEM continueText[] = {
      0x1e, 0x11, 0x11, 0x11, 0x00, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x1f, 0x04, 0x08, 0x1e, 0x00, 0x01, 0x1f, 0x01, 0x01, 0x00, 0x11, 0x1f, 0x11, 0x00, 0x00, 0x1f, 0x04, 0x08, 0x1e, 0x00, 0x0e, 0x10, 0x10, 0x0f, 0x00, 0x1e, 0x15, 0x15, 0x11, 
  };

  // 34 5
  const uint8_t PROGMEM advanceText[] = {
      0x1e, 0x09, 0x09, 0x1e, 0x00, 0x1f, 0x11, 0x11, 0x0e, 0x00, 0x0e, 0x10, 0x10, 0x0f, 0x00, 0x1e, 0x09, 0x09, 0x1e, 0x00, 0x1e, 0x04, 0x08, 0x1f, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x00, 0x1e, 0x15, 0x15, 0x11, 
  };
  const uint8_t PROGMEM challengeText[] = {
      0x0e, 0x11, 0x11, 0x11, 0x00, 0x1f, 0x10, 0x10, 0x10, 0x00, 0x1e, 0x09, 0x09, 0x1e, 0x00, 0x12, 0x15, 0x15, 0x09, 0x00, 0x12, 0x15, 0x15, 0x09, 0x00, 0x11, 0x1f, 0x11, 0x10, 0x00, 0x0e, 0x11, 0x11, 0x11, 
  };
  const uint8_t PROGMEM endlessText[] = {
      0x1e, 0x15, 0x15, 0x11, 0x00, 0x1e, 0x04, 0x08, 0x1f, 0x00, 0x1e, 0x11, 0x11, 0x0e, 0x00, 0x1f, 0x10, 0x10, 0x10, 0x00, 0x1e, 0x15, 0x15, 0x11, 0x00, 0x12, 0x15, 0x15, 0x09, 0x00, 0x12, 0x15, 0x15, 0x09, 
  };

  // 77 5
  const uint8_t PROGMEM backToMainMenu[] = {
      0x1e, 0x11, 0x15, 0x0a, 0x00, 0x1e, 0x09, 0x09, 0x1e, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x00, 0x1f, 0x04, 0x0a, 0x11, 0x00, 0x00, 0x00, 0x01, 0x1d, 0x03, 0x01, 0x00, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x1f, 0x02, 0x04, 0x02, 0x1e, 0x00, 0x1e, 0x09, 0x09, 0x1e, 0x00, 0x11, 0x1f, 0x11, 0x10, 0x00, 0x1f, 0x04, 0x08, 0x1e, 0x00, 0x00, 0x00, 0x1f, 0x02, 0x04, 0x02, 0x1e, 0x00, 0x1e, 0x09, 0x09, 0x1e, 0x00, 0x1f, 0x04, 0x08, 0x1e, 0x00, 0x0e, 0x10, 0x10, 0x0f, 
  };

  // 24 5
  const uint8_t PROGMEM start[] = {
      0x12, 0x15, 0x15, 0x09, 0x00, 0x01, 0x1f, 0x01, 0x01, 0x00, 0x1e, 0x09, 0x09, 0x1e, 0x00, 0x1e, 0x09, 0x15, 0x02, 0x00, 0x01, 0x1f, 0x01, 0x01, 
  };
  const uint8_t PROGMEM soundText[] = {
      0x12, 0x15, 0x15, 0x09, 0x00, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x0e, 0x10, 0x10, 0x0f, 0x00, 0x1f, 0x04, 0x08, 0x1e, 0x00, 0x1e, 0x11, 0x11, 0x0e, 
  };

  // 14 5
  const uint8_t PROGMEM on[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x1e, 0x04, 0x08, 0x1f, 
  };
  const uint8_t PROGMEM off[] = {
      0x0e, 0x11, 0x11, 0x0e, 0x00, 0x1e, 0x05, 0x05, 0x01, 0x00, 0x1e, 0x05, 0x05, 0x01, 
  };

  // 4 4
  const uint8_t PROGMEM x[] = {
      0x06, 0x0d, 0x0f, 0x06, 
  };

  // 16 5
  const uint8_t PROGMEM version[] = {
      0x0e, 0x10, 0x10, 0x0f, 0x00, 0x00, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x10, 0x00, 0x12, 0x1f, 0x10, 
  };
}