//
//  Objects.hpp
//  Project 3
//
//  Created by Daniel Luan on 5/17/24.
//

#ifndef Objects_hpp
#define Objects_hpp

#include <stdio.h>
#include <iostream>
#include "Temple.h"

class Objects {
public:
    Objects(Temple* tp, std::string name, int r, int c);
    std::string name(){return m_name;}
    virtual ~Objects() {}
    void setRow(int r){m_row = r;}
    void setCol(int c){m_col = c;}
    int row(){return m_row;}
    int col(){return m_col;}
private:
    std::string m_name;
    int m_row;
    int m_col;
};

class Scrolls : public Objects{
public:
    Scrolls(Temple* tp, std::string name, int r, int c) : Objects(tp, name, r, c) {}
    virtual ~Scrolls() {}
};

class TeleportScroll : public Scrolls{
public:
    TeleportScroll(Temple* tp, int r, int c): Scrolls(tp, "scroll of teleportation", r, c){}
    ~TeleportScroll() {}
};

class ArmorScroll : public Scrolls{
public:
    ArmorScroll(Temple* tp, int r, int c): Scrolls(tp, "scroll of armor", r, c){}
    ~ArmorScroll() {}
};

class StrengthScroll : public Scrolls{
public:
    StrengthScroll(Temple* tp, int r, int c): Scrolls(tp, "scroll of strength", r, c){}
    ~StrengthScroll() {}
};

class HealthScroll : public Scrolls{
public:
    HealthScroll(Temple* tp, int r, int c): Scrolls(tp, "scroll of enhance health", r, c){}
    ~HealthScroll() {}
};

class DexterityScroll : public Scrolls{
public:
    DexterityScroll(Temple* tp, int r, int c): Scrolls(tp, "scroll of enhance dexterity", r, c){}
    ~DexterityScroll() {}
};


class GoldenIdol : public Objects{
public:
    GoldenIdol(Temple* tp, int r, int c) : Objects(tp, "golden idol", r, c) {}
    ~GoldenIdol() {}
};

class Stairway : public Objects{
public:
    Stairway(Temple* tp, int r, int c) : Objects(tp, "stairway", r, c) {}
    ~Stairway() {}
};

class Weapons : public Objects{
public:
    Weapons(Temple* tp, std::string name, int r, int c, int damage, int dexterity);
    int Damage(){return m_damage;}
    int Dexterity(){return m_dexterity;}
    virtual ~Weapons() {}
private:
    int m_damage;
    int m_dexterity;
};

class Maces : public Weapons{
public:
    Maces(Temple* tp, int r, int c) : Weapons(tp, "mace", r, c, 2, 0) {}
    ~Maces() {}
};

class Shortswords : public Weapons{
public:
    Shortswords(Temple* tp, int r, int c) : Weapons(tp, "short sword", r, c, 2, 0) {}
    ~Shortswords() {}
};

class Longswords : public Weapons{
public:
    Longswords(Temple* tp, int r, int c) : Weapons(tp, "long sword", r, c, 4, 2) {}
    ~Longswords() {}
};

class MagicAxes : public Weapons{
public:
    MagicAxes(Temple* tp, int r, int c) : Weapons(tp, "magic axe", r, c, 5, 5) {}
    ~MagicAxes() {}
};

class MagicFangs : public Weapons{
public:
    MagicFangs(Temple* tp, int r, int c) : Weapons(tp, "magic fangs", r, c, 2, 3) {}
    ~MagicFangs() {}
};

#endif /* Objects_hpp */


