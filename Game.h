#ifndef GAME_H
#define GAME_H

#include "Temple.h"
//#include "Objects.h"
#include <vector>

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
    ~Game();
    void resetTemple();

private:
    Temple* m_temple;
    bool foundGI = false;
};

#endif // GAME_H
