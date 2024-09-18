//
//  Player.hpp
//  Project 3
//
//  Created by Daniel Luan on 5/13/24.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Actor.h"
#include "Inventory.h"

const int  INITIAL_PLAYER_HEALTH = 20;

class Temple;

class Player : public Actor {
public:
    Player(Temple* tp, Weapons* wp, int r, int c);
    ~Player();
    virtual void move(int dir);
    void readTeleport();
    void readArmor(){increaseArmor(randInt(1, 3));}
    void readStrength(){increaseStrength(randInt(1, 3));}
    void readDexterity(){increaseDexterity(1);}
    void readHealth(){setMaxHitPoints(maxHitPoints() + randInt(3, 8));}
    Inventory* InventoryP() const {return m_inventory;}
    
private:
    Inventory* m_inventory;
};


#endif /* Player_hpp */

