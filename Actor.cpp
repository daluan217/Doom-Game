//
//  Actors.cpp
//  Project 3
//
//  Created by Daniel Luan on 5/13/24.
//

#include "Actor.h"
#include "Temple.h"
#include "Monsters.h"
#include <iostream>
using namespace std;

Actor:: Actor(Temple* tp, Weapons* wp, std::string name, int r, int c, int hitPoints, int armor, int strength, int dexterity)
 : m_temple(tp), m_weapon(wp), m_name(name), m_row(r), m_col(c), m_hitPoints(hitPoints), m_armor(armor), m_strength(strength), m_dexterity(dexterity), m_sleep(0)
{
    if (tp == nullptr)
    {
        cout << "***** The actor must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > 18  ||  c < 1  ||  c > 70)
    {
        cout << "**** Actor created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
}

void Actor::move(int r, int c)
{
    m_row = r;
    m_col = c;
}

void Actor::AttackedBy(Actor* ap){
    m_gotAttackedBy = ap->name();
}

void Actor::heal(){
    int i = randInt(0, 9);
    if (i == 0 && m_hitPoints < m_maxHitPoints){
        m_hitPoints++;
    }
}
