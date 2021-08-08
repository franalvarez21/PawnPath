#pragma once

static uint8_t (*digitList[10])[sizeof(Digits::zero)] = {
    &Digits::zero,
    &Digits::one,
    &Digits::two,
    &Digits::three,
    &Digits::four,
    &Digits::five,
    &Digits::six,
    &Digits::seven,
    &Digits::eight,
    &Digits::nine};

class Numbers
{
public:
  static void print(uint8_t x, uint8_t y, int16_t number)
  {
    number = abs(number);
    uint16_t multiplier = 10;
    for (uint8_t i = 0; i < 4; i++)
    {
      size_t pos = (number % multiplier) == 0 ? 0 : (number % multiplier) / (multiplier / 10);
      Arduboy2Base::drawBitmap(x + (40 - 10 * i) - 1, y - 1, Digits::back, 10, 10, BLACK);
      Arduboy2Base::drawBitmap(x + (40 - 10 * i), y, *digitList[pos], 8, 8, WHITE);
      multiplier *= 10;
    }
  }
};
