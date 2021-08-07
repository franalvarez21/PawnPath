
class Cutscene
{
protected:
  uint8_t timer;
  bool gameOver;

public:
  void start(const bool gameOver)
  {
    timer = CUTSCENE_TIMER;
    this->gameOver = gameOver;
  }

  bool enabled()
  {
    return (timer == 0);
  }

  void eventDisplay()
  {
    //TODO: Print event picture
    if (timer > 0)
    {
      timer--;
    }
  }
};
