#pragma once

struct Effects
{
  void displayErrorLine()
  {
    if (rand() % 10 == 0)
    {
      Arduboy2Base::drawFastHLine(0, rand() % 60, 88, BLACK);
    }
  }
};
