#pragma once

class TitleMenu : public Menu
{
public:
  TitleMenu() : Menu(1){};

  bool action(Utils *utils)
  {
    upDownMovement();

    if (okMovement())
    {
      if (option == 1)
      {
        utils->changeSound();
      }
      else if (option == 0)
      {
        utils->okBeep();
        return false;
      }
    }

    return true;
  }

  void eventDisplay(uint8_t cycle, bool sound)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::title, 128, 64, WHITE);

    Arduboy2Base::drawBitmap(104, 52, Lines::start, 24, 4, WHITE);
    Arduboy2Base::drawBitmap(104, 60, Lines::sound, 24, 4, WHITE);
    if (sound)
    {
      Arduboy2Base::drawBitmap(82, 60, Lines::on, 14, 4, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(82, 60, Lines::off, 14, 4, WHITE);
    }
    displayMenuCursor(98, 52);

    Arduboy2Base::drawBitmap(0, 60, Lines::version, 34, 4, WHITE);
  }
};
