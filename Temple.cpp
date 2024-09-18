//
//  Temple.cpp
//  Project 3
//
//  Created by Daniel Luan on 5/13/24.
//

#include "Temple.h"
#include "Player.h"
#include "utilities.h"
#include "Objects.h"
#include "Monsters.h"

#include <iostream>
#include <cstdlib>

using namespace std;



Temple::Temple(int level) : m_player(nullptr), m_level(level)
{
    int r, c;
    for (r = 0; r < MAXROWS; r++)
        for (c = 0; c < MAXCOLS; c++)
            grid[r][c] = '#';
    
    
    // Define rooms (startRow, startCol, endRow, endCol)
    struct Room {
     int startRow, startCol, endRow, endCol;
     };
    
    // Example room definitions (you can adjust these as needed)
    //rooms[6];
    rooms[0].startRow = randInt(2,4); rooms[0].startCol = randInt(2,17); rooms[0].endRow = randInt(6,8); rooms[0].endCol = randInt(19,34);
    rooms[1].startRow = randInt(2,4); rooms[1].startCol = randInt(36,51); rooms[1].endRow = randInt(6,8); rooms[1].endCol = randInt(53,69);
    rooms[2].startRow = randInt(11,13); rooms[2].startCol = randInt(2,17); rooms[2].endRow = randInt(15,17); rooms[2].endCol = randInt(19,34);
    rooms[3].startRow = randInt(11,13); rooms[3].startCol = randInt(36,51); rooms[3].endRow = randInt(15,17); rooms[3].endCol = randInt(53,69);
    
    
    // Create rooms by filling specified areas with spaces
    for (int i = 0; i < 4; i++) {
        //Room room = rooms[i];
        for (r = rooms[i].startRow; r <= rooms[i].endRow; r++) {
            for (c = rooms[i].startCol; c <= rooms[i].endCol; c++) {
                grid[r][c] = ' ';
            }
        }
    }
    for (int i = 17; i < 51; i++){
        grid[4][i] = ' ';
        grid[13][i] = ' ';
    }
    for (int i = 4; i < 13; i++){
        grid[i][17] = ' ';
        grid[i][51] = ' ';
    }

    
    for (r = 0; r < MAXROWS; r++)
        for (c = 0; c < MAXCOLS; c++)
            if (r < 1 || c < 1  || r + 1 == MAXROWS || c + 1 == MAXCOLS)
                grid[r][c] = '#';
}

Temple::~Temple()
{
    for (Monster* monster : monsterVector)
    {
        delete monster;
    }
    monsterVector.clear();
    
    for (Objects* obj : gameObjectVector) {
        delete obj;
    }
    gameObjectVector.clear();
    
    if (quitRequested() || (level() == 4 && m_player) || m_player->isDead()){
        delete m_player;
        m_player = nullptr;
    }
}

void Temple::display()
{
    clearScreen();

    int r, c;
    for (r = 0; r < MAXROWS; r++)
        for (c = 0; c < MAXCOLS; c++)
            grid[r][c] = '#';
    //Delete Later

    struct Room {
        int startRow, startCol, endRow, endCol;
    };

    for (int i = 0; i < 4; i++) {
        for (r = rooms[i].startRow; r <= rooms[i].endRow; r++) {
            for (c = rooms[i].startCol; c <= rooms[i].endCol; c++) {
                grid[r][c] = ' ';
            }
        }
    }

    for (int i = 17; i < 51; i++) {
        grid[4][i] = ' ';
        grid[13][i] = ' ';
    }
    for (int i = 4; i < 13; i++) {
        grid[i][17] = ' ';
        grid[i][51] = ' ';
    }
    

    for (r = 0; r < MAXROWS; r++)
        for (c = 0; c < MAXCOLS; c++)
            if (r < 1 || c < 1 || r + 1 == MAXROWS || c + 1 == MAXCOLS)
                grid[r][c] = '#';
    
    for (int i = 0; i < gameObjectVector.size(); i++) {
        Objects* obj = gameObjectVector[i];
        Scrolls* sp = dynamic_cast<Scrolls*>(obj);
        if (sp!= nullptr)
            grid[gameObjectVector[i]->row() - 1][gameObjectVector[i]->col() - 1] = '?';
        
        Objects* obj2 = gameObjectVector[i];
        Weapons* wp = dynamic_cast<Weapons*>(obj2);
        if (wp != nullptr)
            grid[gameObjectVector[i]->row() - 1][gameObjectVector[i]->col() - 1] = ')';
        
        if (gameObjectVector[i]->name() == "stairway")
            grid[gameObjectVector[i]->row() - 1][gameObjectVector[i]->col() - 1] = '>';
        
        if (gameObjectVector[i]->name() == "golden idol")
            grid[gameObjectVector[i]->row() - 1][gameObjectVector[i]->col() - 1] = '&';
    }
    
    for (int i = 0; i < monsterVector.size(); i++) {
        if (monsterVector[i]->name() == "Bogeyman" && !monsterVector[i]->isDead())
            grid[monsterVector[i]->row() - 1][monsterVector[i]->col() - 1] = 'B';
        if (monsterVector[i]->name() == "Snakewoman" && !monsterVector[i]->isDead())
            grid[monsterVector[i]->row() - 1][monsterVector[i]->col() - 1] = 'S';
        if (monsterVector[i]->name() == "Goblin" && !monsterVector[i]->isDead())
            grid[monsterVector[i]->row() - 1][monsterVector[i]->col() - 1] = 'G';
        if (monsterVector[i]->name() == "Dragon" && !monsterVector[i]->isDead())
            grid[monsterVector[i]->row() - 1][monsterVector[i]->col() - 1] = 'D';
    }
    
    if (m_player != nullptr) {
        grid[m_player->row() - 1][m_player->col() - 1] = '@';
    }

    for (r = 0; r < MAXROWS; r++) {
        for (c = 0; c < MAXCOLS; c++)
            cout << grid[r][c];
        cout << endl;
    }

    cout << "Level: " << level() << ", Hit Points: " << m_player->hitPoints() << ", Armor: " << m_player->armor() << ", Strength: " << m_player->strength() << ", Dexterity: " << m_player->dexterity() << endl;
}

void Temple::displayAttacks(){
    
    for (auto it = monsterVector.begin(); it != monsterVector.end(); ) {
        if ((*it)->gotAttackedBy() != "Nothing") {
            string action = "swings";
            if (m_player->weaponP()->name() == "short sword") {
                action = "slashes";
            }
            if (m_player->weaponP()->name() == "magic fangs") {
                action = "strikes";
            }
            if (m_player->weaponP()->name() == "magic axe") {
                action = "chops";
            }

            if ((*it)->isDead() && !(*it)->deathMessage()) {
                (*it)->setDeathMessage();
                (*it)->drop(*this, (*it)->row(), (*it)->col());
                display();
                cout << "Player " << action << " " << m_player->weaponP()->name() << " at the " << (*it)->name() << " dealing a final blow" << endl;
                delete *it;
                it = monsterVector.erase(it);  // Remove from vector and get new iterator
            } else if (!m_player->didHit()) {
                cout << "Player " << action <<  " " << m_player->weaponP()->name() << " at the " << (*it)->name() << " and misses" << endl;
                (*it)->setAttackedBy();
                ++it;  // Move to the next element
            } else if (m_player->didHit() && !m_player->initiateSleep() && !(*it)->isDead()) {
                cout << "Player " << action << " " << m_player->weaponP()->name() << " at the " << (*it)->name() << " and hits" << endl;
                m_player->setHit();
                (*it)->setAttackedBy();
                ++it;  // Move to the next element
            } else if (m_player->didHit() && m_player->initiateSleep() && !(*it)->isDead()) {
                cout << "Player " << action << " " << m_player->weaponP()->name() << " at the " << (*it)->name() << " and hits putting " << (*it)->name() << " to sleep" << endl;
                m_player->setHit();
                m_player->setInitiateSleepFalse();
                (*it)->setAttackedBy();
                ++it;  // Move to the next element
            }

        } else {
            ++it;  // Move to the next element
        }
    }
    
    if (m_player->gotAttackedBy() != "Nothing") {

        for (auto& monster : monsterVector) {
            if (monster->didAttack()) {
                string action = "swings";
                if (monster->weaponP()->name() == "short sword") {
                    action = "slahes";
                }
                if (monster->weaponP()->name() == "magic fangs") {
                    action = "strikes";
                }
                if (monster->weaponP()->name() == "magic axe") {
                    action = "chops";
                }
                if (m_player->isDead() /*&& !printedFinal()*/) {
                    if (monster->finalBlow()) {
                        cout << "The " << monster->name() << " " << action << " " << monster->weaponP()->name() << " at player dealing a final blow " << endl;
                        //setPrintedFinal();
                    }
                } else if (!monster->didHit()) {
                    cout << "The " << monster->name() << " " << action << " " << monster->weaponP()->name() << " at Player and misses" << endl;
                    monster->setAttackFalse();
                } else if (monster->didHit() && !monster->initiateSleep() && !m_player->isDead()) {
                    cout << "The " << monster->name() << " " << action << " " << monster->weaponP()->name() << " at Player and hits" << endl;
                    monster->setHit();
                    monster->setAttackFalse();
                } else if (monster->didHit() && monster->initiateSleep() && !m_player->isDead()) {
                    cout << "The Snakewoman strikes magic fangs at Player and hits, putting Player to sleep" << endl;
                    monster->setHit();
                    monster->setAttackFalse();
                    monster->setInitiateSleepFalse();
                }
            }
        }
    }
    
    m_player->setAttackedBy();
}

void Temple::displayWeaponSelection(char& ch){

    Objects* obj = player()->InventoryP()->ObjectVector()[ch - 'a'];
    Weapons* wp = dynamic_cast<Weapons*>(obj);
    if(wp != nullptr){
        cout << "You are wielding " << m_player->InventoryP()->ObjectVector()[ch - 'a']->name() << endl;
    } else{
        cout << "You can't wield " << m_player->InventoryP()->ObjectVector()[ch - 'a']->name() << endl;
    }
}

void Temple::displayScrollSelection(char& ch){

    Objects* obj = player()->InventoryP()->ObjectVector()[ch - 'a'];
    Weapons* wp = dynamic_cast<Weapons*>(obj);
    if(wp != nullptr){
        cout << "You can't read a " << m_player->InventoryP()->ObjectVector()[ch - 'a']->name() << endl;
    }
    if(m_player->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of teleportation"){
        cout << "You read the scroll called " << m_player->InventoryP()->ObjectVector()[ch - 'a']->name() << endl;
        cout << "You feel your body wrenched in space and time" << endl;}
    if(m_player->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of armor"){
        cout << "You read the scroll called " << m_player->InventoryP()->ObjectVector()[ch - 'a']->name() << endl;
        cout << "Your armor glows blue" << endl;}
    if(m_player->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of strength"){
        cout << "You read the scroll called " << m_player->InventoryP()->ObjectVector()[ch - 'a']->name() << endl;
        cout << "You feel your muscles bulge" << endl;}
    if(m_player->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of enhance health"){
        cout << "You read the scroll called " << m_player->InventoryP()->ObjectVector()[ch - 'a']->name() << endl;
        cout << "You feel your heart beating stronger" << endl;}
    if(m_player->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of enhance dexterity"){
        cout << "You read the scroll called " << m_player->InventoryP()->ObjectVector()[ch - 'a']->name() << endl;
        cout << "You feel like less of a klutz" << endl;}
}

bool Temple::addPlayer(int r, int c)
{
    if ( !isInBounds(r, c))
        return false;
    
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Dynamically allocate new Player and add it to the city
    Weapons* wp = new Shortswords(this, r, c);
    m_player = new Player(this, wp, r, c);
    m_player->InventoryP()->Add(wp);
    
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a Monster there
        // Indicate player's position
        grid[m_player->row() - 1][m_player->col() - 1] = '@';
    }
    return true;
}

bool Temple::addMonster(int r, int c)
{
    
    if ( !isInBounds(r, c))
        return false;
    
    // Don't add a player on a spot with a Tooter
    /*if (nTootersAt(r, c) > 0)
     return false;*/
    if (m_level < 2){
        int x = randInt(0, 1);
        if (x == 0){
            Weapons* wp = new MagicFangs(this, r, c);
            m_monster = new Snakewomen(this, wp, r, c);
            monsterVector.push_back(m_monster);
        }
        if (x == 1){
            Weapons* wp = new Shortswords(this, r, c);
            m_monster = new Goblins(this, wp, r, c);
            monsterVector.push_back(m_monster);
        }
    }
    if (m_level == 2){
        int x = randInt(0, 2);
        if (x == 0){
            Weapons* wp = new MagicFangs(this, r, c);
            m_monster = new Snakewomen(this, wp, r, c);
            monsterVector.push_back(m_monster);
        }
        if (x == 1){
            Weapons* wp = new Shortswords(this, r, c);
            m_monster = new Goblins(this, wp, r, c);
            monsterVector.push_back(m_monster);
        }
        if (x == 2){
            Weapons* wp = new Shortswords(this, r, c);
            m_monster = new Bogeymen(this, wp, r, c);
            monsterVector.push_back(m_monster);
        }
    }
    if (m_level > 2) {
        int x = randInt(0, 3);
        if (x == 0){
            Weapons* wp = new MagicFangs(this, r, c);
            m_monster = new Snakewomen(this, wp, r, c);
            monsterVector.push_back(m_monster);
        }
        if (x == 1){
            Weapons* wp = new Shortswords(this, r, c);
            m_monster = new Goblins(this, wp, r, c);
            monsterVector.push_back(m_monster);
        }
        if (x == 2) {
            Weapons* wp = new Shortswords(this, r, c);
            m_monster = new Bogeymen(this, wp, r, c);
            monsterVector.push_back(m_monster);
        }
        if (x == 3){
            Weapons* wp = new Longswords(this, r, c);
            m_monster = new Dragons(this, wp, r, c);
            monsterVector.push_back(m_monster);
        }
    }
    
    string type = m_monster->name();
    if (type == "Snakewoman") {
        grid[r - 1][c - 1] = 'S';
    }
    if (type == "Goblin") {
        grid[r - 1][c - 1] = 'G';
    }
    
    if (type == "Bogeyman") {
        grid[r - 1][c - 1] = 'B';
    }
    
    if (type == "Dragon") {
        grid[r - 1][c - 1] = 'D';
    }
    
    return true;
}

bool Temple::addObjects(int r, int c)
{
    if (!isInBounds(r, c))
        return false;

    int x = randInt(0, 6);
    Objects* newObject = nullptr;

    switch (x) {
    case 0:
        newObject = new Maces(this, r, c);
        grid[r - 1][c - 1] = ')';
        break;
    case 1:
        newObject = new Shortswords(this, r, c);
        grid[r - 1][c - 1] = ')';
        break;
    case 2:
        newObject = new Longswords(this, r, c);
        grid[r - 1][c - 1] = ')';
        break;
    case 3:
        newObject = new ArmorScroll(this, r, c);
        grid[r - 1][c - 1] = '?';
        break;
    case 4:
        newObject = new StrengthScroll(this, r, c);
        grid[r - 1][c - 1] = '?';
        break;
    case 5:
        newObject = new HealthScroll(this, r, c);
        grid[r - 1][c - 1] = '?';
        break;
    case 6:
        newObject = new DexterityScroll(this, r, c);
        grid[r - 1][c - 1] = '?';
        break;
    }

    if (newObject) {
        gameObjectVector.push_back(newObject);
    }

    return true;
}

bool Temple::addGoldenIdol(int r, int c)
{
    if (!isInBounds(r, c))
        return false;
    
    Objects* newObject = new GoldenIdol(this, r, c);
    grid[r - 1][c - 1] = '&';
    gameObjectVector.push_back(newObject);
    
    return true;
}

bool Temple::addStairway(int r, int c)
{
    if (!isInBounds(r, c))
        return false;
    
    m_stairway = new Stairway(this, r, c);
    grid[r - 1][c - 1] = '>';
    gameObjectVector.push_back(m_stairway);
    
    return true;
}

Player* Temple::player() const
{
    return m_player;
}

void Temple::moveMonsters()
{
    for (int k = 0; k < monsterVector.size(); k++)
    {
        Monster* mp = monsterVector[k];
        if (m_player == nullptr)
            continue;
        int rowdiff = mp->row() - m_player->row();
        int coldiff = mp->col() - m_player->col();
        
        
        int distance = mp->shortestPath(*this, mp->row(), mp->col(), m_player->row(), m_player->col());
        
        if ((mp->name() == "Goblin" && mp->sleep() == 0 && distance <= goblinSmellDistance()))
            //cout << distance << endl;
            mp->move();
        
        if ((mp->name() == "Bogeyman" && mp->sleep() == 0 && abs(rowdiff) + abs(coldiff) <= 5))
            mp->move();
        
        if ((mp->name() == "Snakewoman" && mp->sleep() == 0 && abs(rowdiff) + abs(coldiff) <= 3))
            mp->move();
        
        if ((mp->name() == "Dragon" && mp->sleep() == 0 && abs(rowdiff) + abs(coldiff) <= 1))
            mp->move();
        
        if (mp->sleep() > 0){
            mp->decreaseSleep();
        }
    }
}


char Temple::charAt(int r, int c) const
{
    return grid[r - 1][c- 1];
}

bool Temple::isInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= MAXROWS  &&  c >= 1  &&  c <= MAXCOLS);
}

bool Temple::isPlayerAt(int r, int c) const
{
    return m_player != nullptr  &&
    m_player->row() == r  &&  m_player->col() == c;
}

bool Temple::isMonsterAt(int r, int c) const
{
    for (auto monster : monsterVector) {
        if (monster->row() == r && monster->col() == c) {
            return true;
        }
    }
    return false;
}

bool Temple::isObjectAt(int r, int c) const
{
    for (auto object : gameObjectVector) {
        if (object->row() == r && object->col() == c) {
            return true;
        }
    }
    return false;
}

bool Temple::isStairwayAt(int r, int c) const
{
    if (m_stairway->row() == r && m_stairway->col() == c) {
        return true;
    }
    return false;
}

bool Temple::isWall(int r, int c) const
{
    return grid[r - 1][c - 1] == '#';
}

bool Temple::determineNewPosition(int& r, int& c, char dir, Monster* mp)
{
    // Determine the new position based on the direction
    switch(dir)
    {
        case 'k': r--; break; // Move up
        case 'j': r++; break; // Move down
        case 'h': c--; break; // Move left
        case 'l': c++; break; // Move right
        default: return false;
    }
    
    // Check if the new position is a wall
    if (isWall(r, c))
        return false;
    
    // Check if the new position is the player's position
    if (isPlayerAt(r, c))
    {
        mp->setAttackTrue();
        int attackerPoints = mp->dexterity() + mp->weaponP()->Dexterity();
        int defenderPoints = m_player->dexterity() + m_player->armor();
        int damagePoints = randInt(0, mp->strength() + mp->weaponP()->Damage() - 1);
        // Monster attacks the player

        if (!mp->isDead() && randInt(1, attackerPoints) >= randInt(1, defenderPoints))
        {
            grid[mp->row() - 1][mp->col() - 1] = ' ';
            m_player->getAttacked(damagePoints);
            if(mp->weaponP()->name() == "magic fangs" && randInt(0, 4) == 0){
                m_player->setSleep(randInt(2, 6));
                mp->setInitiateSleepTrue();
            }
            mp->setAttackTrue();
            mp->setHit();
            if (m_player->isDead())
            {
                mp->setFinalBlow();
            }
            m_player->AttackedBy(mp);
        }
        if (!mp->isDead() && randInt(1, attackerPoints) < randInt(1, defenderPoints)){
            mp->setAttackTrue();
            m_player->AttackedBy(mp);
        }
        m_player->AttackedBy(mp);
        
        return false;
    }
    
    // Check if the new position is occupied by another monster
    if (isMonsterAt(r, c))
    {
        Monster* mp = nullptr;
        for (int i = 0; i < monsterVector.size(); i++)
        {
            if (monsterVector[i]->row() == r && monsterVector[i]->col() == c)
            {
                mp = monsterVector[i];
            }
        }
        // Player attacks the monster occupying the new position
        int attackerPoints = m_player->dexterity() + m_player->weaponP()->Dexterity();
        int defenderPoints = mp->dexterity() + mp->armor();
        int damagePoints = randInt(0, m_player->strength() + m_player->weaponP()->Damage() - 1);
        
        
        if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)){
            mp->Actor::getAttacked(damagePoints);
            if(m_player->weaponP()->name() == "magic fangs" && randInt(0, 4) == 0){
                mp->setSleep(randInt(2, 6));
                m_player->setInitiateSleepTrue();
            }

            m_player->setHit();
        }
        m_player->AttackedBy(mp);
        mp->AttackedBy(m_player);
        return false;
    }
    
    return true;
}

void Temple::clearMonsters() {
    for (auto monster : monsterVector) {
        delete monster;
    }
    monsterVector.clear();
}

void Temple::clearObjects() {
    for (auto object : gameObjectVector) {
        delete object;
    }
    gameObjectVector.clear();
}

const char (&Temple::getGrid() const)[MAXROWS][MAXCOLS] {return grid;}
