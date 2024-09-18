//
//  Monsters.hpp
//  Project 3
//
//  Created by Daniel Luan on 5/13/24.
//

#ifndef Monsters_hpp
#define Monsters_hpp

#include <stdio.h>
#include "Actor.h"
#include "Player.h"
#include "Temple.h"


class Monster : public Actor {
public:
    Monster(Temple* tp, Weapons* wp, std::string name, int r, int c, int hitPoints, int armor, int strength, int dexterity) : Actor(tp, wp, name, r, c, hitPoints, armor, strength, dexterity){}
    virtual ~Monster(){}
    
    virtual void move();
    virtual void drop(Temple& temple, int r, int c){}
    void  getAttacked();
    virtual int shortestPath(Temple& temple, int sr, int sc, int er, int ec);
    void setDeathMessage(){m_deathMessage = !m_deathMessage;}
    bool deathMessage(){return m_deathMessage;}
    struct Position {
        int row, col, steps;
    };
private:
    bool m_deathMessage = false;;

};

class Bogeymen : public Monster {
public:
    Bogeymen(Temple* tp, Weapons* wp, int r, int c);
    void drop(Temple& temple, int r, int c);
    ~Bogeymen(){DeleteWeapon();}
};

class Snakewomen : public Monster {
public:
    Snakewomen(Temple* tp, Weapons* wp, int r, int c);
    void drop(Temple& temple, int r, int c);
    ~Snakewomen(){DeleteWeapon();}
};

class Dragons : public Monster {
public:
    Dragons(Temple* tp, Weapons* wp, int r, int c);
    void drop(Temple& temple, int r, int c);
    ~Dragons(){DeleteWeapon();}
};

class Goblins : public Monster {
public:
    Goblins(Temple* tp, Weapons* wp, int r, int c);
    void findShortestPath(Temple& temple, bool visited[][70], int sr, int sc, int er, int ec, int steps, int &minSteps);
    ~Goblins(){DeleteWeapon();}
    bool pathExists(Temple& temple, int nRows, int nCols, int sr, int sc, int er, int ec);
    bool isValidMove(Temple& temple, bool visited[MAXROWS][MAXCOLS], int row, int col);
    int shortestPath(Temple& temple, int sr, int sc, int er, int ec);
    int optimalMove(int i) ;
    void move();
    void drop(Temple& temple, int r, int c);

};

#endif /* Monsters_hpp */
