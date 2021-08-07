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

    if (leftRightMovement())
    {
      if (option == 1)
      {
        utils->changeSound();
      }
    }

    if (okMovement())
    {
      if (option == 2)
      {
        utils->okBeep();
        return 2;
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

  void eventDisplay(bool sound)
  {
    Arduboy2Base::drawBitmap(24, 15, Lines::continueText, 39, 5, WHITE);
    if (sound)
    {
      Arduboy2Base::drawBitmap(24, 23, Lines::soundText, 24, 5, WHITE);
      Arduboy2Base::drawBitmap(46, 23, Lines::on, 14, 5, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(24, 23, Lines::soundText, 24, 5, WHITE);
      Arduboy2Base::drawBitmap(51, 23, Lines::off, 14, 5, WHITE);
    }
    Arduboy2Base::drawBitmap(24, 31, Lines::backToMainMenu, 77, 5, WHITE);

    displayMenuCursor(18, 15);

    Arduboy2Base::drawBitmap(90, 0, Title::title_border, 38, 38, WHITE);
  }
};
