//
//  Monsters.hpp
//  Project 3
//
//  Created by Daniel Luan on 5/13/24.
//

//#ifndef Monsters_hpp
//#define Monsters_hpp

#include <stdio.h>
#include "Actor.h"
#include "Player.h"
#include "Temple.h"
#include "Monsters.h"
#include <iostream>
#include <climits>
#include <queue>
using namespace std;


//#endif /* Monsters_hpp */
//
//  Monsters.cpp
//  Project 3
//
//  Created by Daniel Luan on 5/13/24.
//


void Monster::move(){

    char dir = 'y';
    
    if (templeP()->player()->row() > row() && templeP()->player()->col() > col()){
        int y = randInt(0, 1);
        if (y == 0)
            dir = 'l';
        else
            dir = 'j';
    }
    
    if (templeP()->player()->row() > row() && templeP()->player()->col() < col()){
        int y = randInt(0, 1);
        if (y == 0)
            dir = 'h';
        else
            dir = 'j';
    }
    
    if (templeP()->player()->row() < row() && templeP()->player()->col() > col()){
        int y = randInt(0, 1);
        if (y == 0)
            dir = 'l';
        else
            dir = 'k';
    }
    
    if (templeP()->player()->row() < row() && templeP()->player()->col() < col()){
        int y = randInt(0, 1);
        if (y == 0)
            dir = 'h';
        else
            dir = 'k';
    }
    
    if (templeP()->player()->row() > row() && templeP()->player()->col() == col()){
            dir = 'j';
    }
    
    if (templeP()->player()->row() < row() && templeP()->player()->col() == col()){
            dir = 'k';
    }
    
    if (templeP()->player()->row() == row() && templeP()->player()->col() > col()){
            dir = 'l';
    }
    
    if (templeP()->player()->row() == row() && templeP()->player()->col() < col()){
            dir = 'h';
    }
    
    if (templeP()->player()->row() == row() && templeP()->player()->col() == col()){
        return;
    }
    
    
    int r = row();
    int c = col();
    
    if (!templeP()->determineNewPosition(r, c, dir, this))
        return;
    
    
    if (!templeP()->isWall(r, c) && !templeP()->isMonsterAt(r, c) && !templeP()->isPlayerAt(r, c)){
        setRow(r);
        setCol(c);
        this->weaponP()->setRow(r);
        this->weaponP()->setCol(c);
    }
}
void  Monster::getAttacked(){
    
}

int Monster::shortestPath(Temple& temple, int sr, int sc, int er, int ec) {
    // Provides a default behavior, for example, return a large value or -1
    return -1;
}

Bogeymen::Bogeymen(Temple* tp, Weapons* wp, int r, int c) : Monster(tp, wp, "Bogeyman", r, c, randInt(5, 10), randInt(2, 3), randInt(2, 3), 2){
    
}

Snakewomen::Snakewomen(Temple* tp, Weapons* wp, int r, int c) : Monster(tp, wp, "Snakewoman", r, c, randInt(3, 6), 2, 3, 3){
    
}

Dragons::Dragons(Temple* tp, Weapons* wp, int r, int c) : Monster(tp, wp, "Dragon", r, c, randInt(20, 25), 4, 4, 4){
    setMaxHitPoints(hitPoints());
}

Goblins::Goblins(Temple* tp, Weapons* wp, int r, int c) : Monster(tp, wp, "Goblin", r, c, randInt(15, 20), 3, 1, 1){
    
}

bool Goblins::isValidMove(Temple& temple, bool visited[MAXROWS][MAXCOLS], int row, int col) {
    return row >= 1 && row <= MAXROWS && col >= 1 && col <= MAXCOLS &&
    !temple.isWall(row, col) &&
    !visited[row - 1][col - 1] &&
    !temple.isMonsterAt(row, col);
    
}

int Goblins::shortestPath(Temple& temple, int sr, int sc, int er, int ec) {

    
    if (sr == er && sc == ec) return 0;
    //cout << er << ", " << ec << endl;
    bool visited[MAXROWS][MAXCOLS] = {false};
    std::queue<Position> q;

    q.push({sr, sc, 0});
    visited[sr - 1][sc - 1] = true;

    int dr[4] = {0, 1, 0, -1};
    int dc[4] = {1, 0, -1, 0};

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];

            if (newRow == er && newCol == ec) {
                return current.steps + 1;
            }

            if (isValidMove(temple, visited, newRow, newCol)) {
                visited[newRow - 1][newCol - 1] = true;
                q.push({newRow, newCol, current.steps + 1});
            }
        }
    }

    return 999;
}
int Goblins::optimalMove(int i) {
    
    bool visited[MAXROWS][MAXCOLS] = {false};
    
    if (i > 3) {
        return -1;  // All directions have been checked
    }

    int dr[4] = {-1, 1, 0, 0}; // delta row for up, down, left, right
    int dc[4] = {0, 0, -1, 1}; // delta col for up, down, left, right

    int newRow = row() + dr[i];
    int newCol = col() + dc[i];
    int startPosDist = shortestPath(*templeP(), row(), col(), templeP()->player()->row(), templeP()->player()->col());
    int endPosDist = 999;

    if (isValidMove(*templeP(), visited, newRow, newCol)) {
        endPosDist = shortestPath(*templeP(), newRow, newCol, templeP()->player()->row(), templeP()->player()->col());
    }

    if (endPosDist < startPosDist && templeP()->grid[newRow - 1][newCol - 1] != '#') {
        return i;  // Found a valid move
    } else {
        return optimalMove(i + 1);  // Check the next direction
    }
}
void Goblins::move() {
    bool visited[MAXROWS][MAXCOLS] = {false};
    visited[row()][col()] = true;  // Ensure to mark the current position as visited

    int i = optimalMove(0);  // Get the optimal move direction
    char dir = 'k';
    // Map the index to the corresponding direction
    if (i == 0) dir = 'k'; // Move up
    if (i == 1) dir = 'j'; // Move down
    if (i == 2) dir = 'h'; // Move left
    if (i == 3) dir = 'l'; // Move right

    int r = row();
    int c = col();
    
    if (!templeP()->determineNewPosition(r, c, dir, this)) {
        // If the new position is the player's position, the attack logic inside determineNewPosition will handle it.
        return;
    }
    
    if (!templeP()->isWall(r, c) && !templeP()->isMonsterAt(r, c) && !templeP()->isPlayerAt(r, c)) {
        setRow(r);
        setCol(c);
        this->weaponP()->setRow(r);
        this->weaponP()->setCol(c);
    }
}

void Bogeymen::drop(Temple& temple, int r, int c){
    if(randInt(0, 9) == 0){
        Temple* tp = &temple;
        Objects* newObject = new MagicAxes(tp, r, c);
        temple.gameObjectVector.push_back(newObject);
        temple.grid[r - 1][c - 1] = ')';
    }
}

void Snakewomen::drop(Temple& temple, int r, int c){
    if(randInt(0, 2) == 0 && !temple.isObjectAt(r, c)){
        Temple* tp = &temple;
        Objects* newObject = new MagicFangs(tp, r, c);
        temple.gameObjectVector.push_back(newObject);
        temple.grid[r - 1][c - 1] = ')';
    }
}

void Dragons::drop(Temple& temple, int r, int c){
    if(!temple.isObjectAt(r, c)){
        Temple* tp = &temple;
        Objects* newObject = nullptr;
        int i = randInt(0, 4);
        if (i == 0){
            newObject = new TeleportScroll(tp, r, c);
        }
        if (i == 1){
            newObject = new ArmorScroll(tp, r, c);
        }
        if (i == 2){
            newObject = new StrengthScroll(tp, r, c);
        }
        if (i == 3){
            newObject = new HealthScroll(tp, r, c);
        }
        if (i == 4){
            newObject = new DexterityScroll(tp, r, c);
        }
        temple.gameObjectVector.push_back(newObject);
        temple.grid[r - 1][c - 1] = '?';
    }
}

void Goblins::drop(Temple& temple, int r, int c){
    int i = randInt(0, 6);
    if(i < 2 && !temple.isObjectAt(r, c)){
        Temple* tp = &temple;
        Objects* newObject = nullptr;
        if(i == 0){
            newObject = new MagicFangs(tp, r, c);
        }
        if(i == 1){
            newObject = new MagicAxes(tp, r, c);
        }
        temple.gameObjectVector.push_back(newObject);
        temple.grid[r - 1][c - 1] = ')';
    }
}
