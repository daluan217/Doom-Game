//
//  Player.cpp
//  Project 3
//
//  Created by Daniel Luan on 5/13/24.
//

#include "Player.h"
#include <iostream>
using namespace std;
#include "Temple.h"


Player :: Player(Temple* tp, Weapons* wp, int r, int c) : Actor(tp, wp, "Player", r, c, 20, 2, 2, 2), m_inventory(new Inventory()){
    setMaxHitPoints(20);
    //cout << this->maxHitPoints();
}

Player::~Player()
{
    delete m_inventory;
}



void Player::move(int dir)
{
    int r = row();
    int c = col();
    if (templeP()->determineNewPosition(r, c, dir))
    {
         
        if (!templeP()->isWall(r, c) && !templeP()->isMonsterAt(r, c))
        {
            setRow(r);
            setCol(c);
            for (auto object : m_inventory->ObjectVector()) {
                object->setRow(r);
                object->setCol(r);
            }
        }
    }
}

void Player::readTeleport()
{
    int rPlayer = randInt(2, 17);
    int cPlayer = randInt(2, 69);
    while (templeP()->charAt(rPlayer, cPlayer) != ' '){
        rPlayer = randInt(2, 17);
        cPlayer = randInt(2, 69);
    }
    setRow(rPlayer);
    setCol(cPlayer);
}


