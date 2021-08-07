#pragma once

class PauseMenu : public Menu
{
public:
  PauseMenu() : Menu(2){};

  void refresh()
  {
    option = 0;
  }

  uint8_t action(Utils *utils)
  {
    upDownMovement();

    if (okMovement())
    {
      if (option == 2)
      {
        utils->okBeep();
        return 2;
      }
      else if (option == 1)
      {
        utils->changeSound();
      }
      else if (option == 0)
      {
        return 1;
      }
    }

    if (koMovement())
    {
      return 1;
    }

    return 0;
  }

  void eventDisplay(Stats *stats, Numbers *numbers, bool sound)
  {
    Arduboy2Base::drawBitmap(18, 8, Lines::options, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(24, 20, Lines::back, 34, 4, WHITE);
    if (sound)
    {
      Arduboy2Base::drawBitmap(24, 28, Lines::sOn, 34, 4, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(24, 28, Lines::sOff, 34, 4, WHITE);
    }
    Arduboy2Base::drawBitmap(24, 36, Lines::mMenu, 34, 4, WHITE);

    displayMenuCursor(18, 20);

    numbers->print(45, 50, stats->score);
    Arduboy2Base::drawBitmap(99, 50, Lines::hubScore, 24, 5, WHITE);

    Arduboy2Base::drawBitmap(90, 0, Title::title_border, 38, 38, WHITE);
  }
};
