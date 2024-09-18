//
//  Temple.hpp
//  Project 3
//
//  Created by Daniel Luan on 5/13/24.
//

#ifndef Temple_hpp
#define Temple_hpp

#include "utilities.h"
#include <stdio.h>
#include <vector>



const int MAXROWS = 18;               // max number of rows in a city
const int MAXCOLS = 70;               // max number of columns in a city

class Player;

class Monster;

class Objects;

class Temple
{
public:
    Temple(int level);

    ~Temple();
    
    void setPlayer(Player* player){m_player = player;}
    
    void display();
    
    void displayAttacks();
    
    void displayWeaponSelection(char& ch);
    
    void displayScrollSelection(char& ch);
    
    bool addPlayer(int r, int c);
    bool addMonster(int r, int c);
    bool addObjects(int r, int c);
    bool addGoldenIdol(int r, int c);
    bool addStairway(int r, int c);
    
    void moveMonsters();
    Player* player() const;
    std::vector<Monster*>& MonsterVector() {return monsterVector;}
    std::vector<Objects*>& GameObjectVector() {return gameObjectVector;}
    char charAt(int r, int c) const;
    void setCharP(int r, int c) {grid[r - 1][c- 1] = 'P';}
    void setCharM(int r, int c) {grid[r - 1][c- 1] = 'M';}
    //char grid();
    bool isInBounds(int r, int c) const;
    bool determineNewPosition(int& r, int& c, char dir, Monster* m=nullptr);
    bool isPlayerAt(int r, int c) const;
    bool isMonsterAt(int r, int c) const;
    bool isObjectAt(int r, int c) const;
    bool isStairwayAt(int r, int c) const;
    bool isWall(int r, int c) const;
    void setPrintedFinal() {m_printedFinal = !m_printedFinal;}
    bool printedFinal() const {return m_printedFinal;}
    void setGoblinSmellDistance(int GSD){m_goblinSmellDistance = GSD;}
    int goblinSmellDistance(){return m_goblinSmellDistance;}
    int level() const {return m_level;}
    void increaseLevel() {m_level++;}
    void clearMonsters();
    void clearObjects();
    void setQuitRequestTrue() {m_quitRequested = true;}
    bool quitRequested(){return m_quitRequested;}
    const char (&getGrid() const)[MAXROWS][MAXCOLS];
    

    friend class Monster;
    friend class Goblins;
    friend class Bogeymen;
    friend class Dragons;
    friend class Snakewomen;
    
private:
    Player* m_player;
    Monster* m_monster;
    Objects* m_weapon;
    Objects* m_stairway;
    std::vector<Monster*> monsterVector;
    Objects* m_objects;
    std::vector<Objects*> gameObjectVector;
    char m_charAt;
    //int m_rows;
    //int m_cols;
    bool m_printedFinal = false;
    char grid[MAXROWS][MAXCOLS];
    int m_goblinSmellDistance;
    int m_level;
    bool m_quitRequested = false;
    struct Room {
        int startRow, startCol, endRow, endCol;
    };
    Room rooms[4];
};
#endif /* Temple_hpp */
