//
//  Actors.hpp
//  Project 3
//
//  Created by Daniel Luan on 5/13/24.
//

#ifndef Actors_hpp
#define Actors_hpp

#include <stdio.h>
#include "utilities.h"
#include "Game.h"
#include "Objects.h"
#include "iostream"

class Temple;

class Monster;

class Actor {
public:
    Actor(Temple* tp, Weapons* wp, std::string name, int r, int c, int hitPoints, int armor, int strength, int dexterity);
    virtual ~Actor() {}
    std::string name() {return m_name;}
    Temple* templeP() const {return m_temple;}
    Weapons* weaponP() const {return m_weapon;}
    void DeleteWeapon() {delete m_weapon;}
    void setWeapon(Weapons* wp) {m_weapon = wp;}
    int row() const { return m_row; }
    int col() const { return m_col; }
    void setRow(int r) { m_row = r;}
    void setCol(int c) { m_col = c;}
    virtual void move(int r, int c);
    void  getAttacked(int damage){m_hitPoints -= damage;}
    bool isDead() {return m_hitPoints <= 0;}
    void AttackedBy(Actor* ap);
    void setAttackedBy() {m_gotAttackedBy = "Nothing";}
    std::string gotAttackedBy() const {return m_gotAttackedBy;}
    void setAttackTrue() {m_didAttack = true;}
    void setAttackFalse() {m_didAttack = false;}
    bool didAttack() const {return m_didAttack;}
    void setInitiateSleepTrue() {m_initiateSleep = true;}
    void setInitiateSleepFalse() {m_initiateSleep = false;}
    bool initiateSleep() const {return m_initiateSleep;}
    void setFinalBlow() {m_finalBlow = true;}
    bool finalBlow() const {return m_finalBlow;}
    void setHit() {m_hit = !m_hit;}
    bool didHit() const {return m_hit;}
    void setHitPoints(int health) {m_hitPoints = health;}
    virtual int hitPoints() const { return m_hitPoints; }
    void setMaxHitPoints(int health) {m_maxHitPoints = health;}
    virtual int maxHitPoints() const {return m_maxHitPoints;}
    void heal();
    void increaseArmor(int i) {m_armor += i;}
    virtual int armor() const { return m_armor; }
    virtual int strength() const { return m_strength; }
    void increaseStrength(int i) {m_strength += i;}
    virtual int dexterity() const { return m_dexterity; }
    void increaseDexterity(int i) {m_dexterity += i;}
    void decreaseSleep() {m_sleep--;}
    void setSleep(int sleep) {m_sleep = std::max(m_sleep, sleep);}
    int sleep() const { return m_sleep; }
    void setTemple(Temple* temple) {m_temple = temple;}


private:
    
    Temple* m_temple;
    Weapons* m_weapon;
    std::string m_name;
    int m_row;
    int m_col;
    std::string m_gotAttackedBy = "Nothing";
    bool m_didAttack = false;;
    bool m_initiateSleep = false;
    bool m_finalBlow = false;
    bool m_hit = false;
    int m_hitPoints;
    int m_maxHitPoints;
    int m_armor;
    int m_strength;
    int m_dexterity;
    int m_sleep;
    
};


#endif /* Actors_hpp */
