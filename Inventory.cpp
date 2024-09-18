//
//  Inventory.cpp
//  Project 3
//
//  Created by macbook on 5/25/24.
//

#include "Inventory.h"
#include <iostream>
using namespace std;

Inventory::~Inventory() {
    for (Objects* obj : objectVector) {
        delete obj;
        obj = nullptr;  // Set pointer to nullptr after deletion
    }
    objectVector.clear();
}

void Inventory::Display(){
    char letter = 'a';
    cout << "Inventory: " << endl;
    for (auto object : objectVector) {
        cout << letter++ << ". " << object->name() << endl;
    }
}

bool Inventory::ObjectSelect(char& ch){
    if (ch - 'a' < 0 || ch - 'a' >= objectVector.size()){
        return false;
    }

    return true;
}

