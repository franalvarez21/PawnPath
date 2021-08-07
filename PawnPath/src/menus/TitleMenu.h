#pragma once

class TitleMenu : public Menu
{
public:
  TitleMenu() : Menu(1){};

  bool action(Utils *utils)
  {
    upDownMovement();

    if (leftRightMovement())
    {
      if (option == 1)
      {
        utils->changeSound();
      }
      else if (option == 0)
      {
        utils->changeMode();
      }
    }

    if (okMovement())
    {
      if (option == 0)
      {
        return false;
      }
    }

    return true;
  }

  void eventDisplay(uint8_t cycle, bool sound, bool mode)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::title, 128, 64, WHITE);

    Arduboy2Base::drawBitmap(104, 51, Lines::start, 24, 5, WHITE);

    if (mode)
    {
      Arduboy2Base::drawBitmap(62, 51, Lines::endlessText, 34, 5, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(62, 51, Lines::challengeText, 34, 5, WHITE);
    }

    Arduboy2Base::drawBitmap(104, 59, Lines::soundText, 24, 5, WHITE);

    if (sound)
    {
      Arduboy2Base::drawBitmap(82, 59, Lines::on, 14, 5, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(82, 59, Lines::off, 14, 5, WHITE);
    }

    displayMenuCursor(98, 51);

    Arduboy2Base::drawBitmap(37, 51, Lines::version, 16, 5, WHITE);
  }
};
