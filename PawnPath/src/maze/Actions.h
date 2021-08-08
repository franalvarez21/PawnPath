
class Actions
{
public:
  bool evaluateAction(Utils *utils, Stats *stats, Dungeon *dungeon, uint8_t action)
  {
    if (dungeon->canContinue())
    {
      if (dungeon->hasMoved())
      {
        stats->incScore(5);
        dungeon->increaseLevel();
        utils->levelUpBeep();
      }
      dungeon->reset(stats, utils->mode);
      return true;
    }

    switch (action)
    {
    case 1:
      // Fall of map
      dungeon->reset(stats, utils->mode);
      utils->koBeep();
      stats->decHP(1);
      break;
    case 2:
      // Restore HP
      stats->incHP(1);
      utils->okBeep();
      stats->incScore(1);
      break;
    case 3:
      // Restore map
      utils->okBeep();
      break;
    case 4:
      // Decrease HP
      stats->decHP(1);
      utils->koBeep();
      break;
    case 5:
      // Activate goal
      utils->fastBeep();
      stats->incScore(5);
      break;
    case 6:
      // Deactivate goal
      utils->boundBeep();
      stats->decScore(5);
      break;
    }

    return false;
  }
};
