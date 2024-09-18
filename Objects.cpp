//
//  Objects.cpp
//  Project 3
//
//  Created by Daniel Luan on 5/17/24.
//

#include "Objects.h"

// Implementation of the Objects constructor
Objects::Objects(Temple* tp, std::string name, int r, int c) : m_name(name), m_row(r), m_col(c) {}

// Implementation of the Weapons constructor
Weapons::Weapons(Temple* tp, std::string name, int r, int c, int damage, int dexterity)
    : Objects(tp, name, r, c), m_damage(damage), m_dexterity(dexterity) {}
