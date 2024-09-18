//
//  Inventory.hpp
//  Project 3
//
//  Created by macbook on 5/25/24.
//

#ifndef Inventory_hpp
#define Inventory_hpp

#include <stdio.h>
#include <vector>
#include "Objects.h"

class Inventory{
public:
    Inventory(){}
    ~Inventory();
    std::vector<Objects*> ObjectVector() {return objectVector;}
    void Add(Objects* obj) { objectVector.push_back(obj); }
    void Remove(char ch){objectVector.erase(objectVector.begin() + ch - 'a');}
    void Display();
    bool ObjectSelect(char& ch);
private:
    std::vector<Objects*> objectVector;
};

#endif /* Inventory_hpp */
