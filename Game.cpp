// Game.cpp
#include "utilities.h"
#include "Game.h"
#include "Temple.h"
#include <iostream>
#include "utilities.h"
#include "Player.h"
#include "Monsters.h"
using namespace std;

class Temple;

// You may add data members and other member functions to this class.

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
    //Creates a new temple and adds necessary actors and objects into temple depending on level. Makes sure that all objects are added onto a space.
    m_temple = new Temple(0);
    m_temple->setGoblinSmellDistance(goblinSmellDistance);
    
    int rPlayer = randInt(2, 17);
    int cPlayer = randInt(2, 69);
    while (m_temple->charAt(rPlayer, cPlayer) != ' '){
        rPlayer = randInt(2, 17);
        cPlayer = randInt(2, 69);
    }
    m_temple->addPlayer(rPlayer, cPlayer); // Randomize Later
    
    int rStairway = randInt(2, 17);
    int cStairway = randInt(2, 69);
    while (m_temple->charAt(rStairway, cStairway) != ' '){
        rStairway = randInt(2, 17);
        cStairway = randInt(2, 69);
    }
    m_temple->addStairway(rStairway, cStairway);
    
    int M = randInt(2, 5*(m_temple->level()+1)+1);
    int rMonster = randInt(2, 17);
    int cMonster = randInt(2, 69);
    for (int i = 0; i < M; i++){ // Change to M later
        while (m_temple->charAt(rMonster, cMonster) != ' '){
            rMonster = randInt(2, 17);
            cMonster = randInt(2, 69);
        }
        m_temple->addMonster(rMonster, cMonster); // Randomize Later
    }
    int rObject = randInt(2, 17);
    int cObject = randInt(2, 69);

    for (int i = 0; i < randInt(2, 3); i++) {
        while (m_temple->charAt(rObject, cObject) != ' ') {
            rObject = randInt(2, 17);
            cObject = randInt(2, 69);
        }
        m_temple->addObjects(rObject, cObject);
    }
    
}

Game::~Game()
{
    delete m_temple;
}

void Game::play()
{
    m_temple->display();
    Player* p = m_temple->player();
    if (p == nullptr)
        return;

    while (!p->isDead() && !foundGI)
    {
        //Potenitally heals player each round
        p->heal();
        
        
        for (auto monster : m_temple->MonsterVector()) {
            if (monster->name() == "Dragon") {
                // Potenitally heals monster each round
                monster->heal();
            }
        }
        
        char ch = getCharacter();
        
        //Move player as long as player isn't asleep else decrease its sleep
        
        if(p->sleep() == 0){
            p->move(ch);
        } else {
            p->decreaseSleep();
        }
        
        m_temple->moveMonsters();

        if (ch == 'q'){
            //quits game
            m_temple->setQuitRequestTrue();
            break;
        }
        if (ch == '>' && m_temple->isStairwayAt(m_temple->player()->row(), m_temple->player()->col()))
            //Stairway
        {
            resetTemple();
            m_temple->display();
            m_temple->displayAttacks();
        }
    
        
        if (ch == 'g') {
            //Pick up object
            m_temple->display();
            cout << endl;
            for (auto it = m_temple->GameObjectVector().begin(); it != m_temple->GameObjectVector().end();) {
                Objects* object = *it;
                
                //Can't add stairway to inventory
                if (object->name() != "stairway" &&
                    object->row() == m_temple->player()->row() &&
                    object->col() == m_temple->player()->col()) {
                    m_temple->player()->InventoryP()->Add(object);
                
                    //Checks if golden idol is found
                    if (object->name() == "golden idol"){
                        foundGI = true;
                    }
                    
                    //Checks to see if it is a scroll or a weapon
                    Scrolls* sp = dynamic_cast<Scrolls*>(object);
                    
                    if (sp != nullptr) {
                        cout << "You pick up a scroll called " << object->name() << endl;
                        
                    } else if (sp == nullptr) {
                        cout << "You pick up " << object->name() << endl;
                    }

                    // Erase the object from the vector and get a new iterator
                    it = m_temple->GameObjectVector().erase(it);
                } else {
                    // Move to the next element
                    ++it;
                }
            }
            m_temple->displayAttacks();
        }
        
        if (ch == 'i')
        {
            clearScreen();
            m_temple->player()->InventoryP()->Display();
            char ch;
            cin.get(ch);
        }
        
        if (ch == 'w') {
            //Wield Weapon
            clearScreen();
            m_temple->player()->InventoryP()->Display();
            char ch;
            cin.get(ch);
            if(m_temple->player()->InventoryP()->ObjectSelect(ch)){
            Objects* obj = m_temple->player()->InventoryP()->ObjectVector()[ch - 'a'];
            Weapons* wp = dynamic_cast<Weapons*>(obj);
                
                if (wp != nullptr) {
                    m_temple->player()->setWeapon(wp);
                }

                m_temple->display();
                cout << endl;
                m_temple->displayWeaponSelection(ch);
                m_temple->displayAttacks();
                
            } else {
                m_temple->display();
                cout << endl;
                m_temple->displayAttacks();
            }
        }
        
        if (ch == 'r') {
            //Read Scrolls
            clearScreen();
            m_temple->player()->InventoryP()->Display();
            char ch;
            cin.get(ch);
            bool scroll = false;
            if(m_temple->player()->InventoryP()->ObjectSelect(ch)){
                //Read the scroll depenging on the type
                if(m_temple->player()->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of teleportation"){
                    m_temple->player()->readTeleport();
                    scroll = true;
                }
                if(m_temple->player()->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of armor"){
                    m_temple->player()->readArmor();
                    scroll = true;
                }
                if(m_temple->player()->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of strength"){
                    m_temple->player()->readStrength();
                    scroll = true;
                }
                if(m_temple->player()->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of enhance health"){
                    m_temple->player()->readHealth();
                    scroll = true;
                }
                if(m_temple->player()->InventoryP()->ObjectVector()[ch - 'a']->name() == "scroll of enhance dexterity"){
                    m_temple->player()->readDexterity();
                    scroll = true;
                }
                m_temple->display();
                cout << endl;
                m_temple->displayScrollSelection(ch);
                m_temple->displayAttacks();
                if (scroll){
                    //Delete the scroll after it has been read
                    delete m_temple->player()->InventoryP()->ObjectVector()[ch - 'a'];
                    //Erase the pointer from the vector
                    m_temple->player()->InventoryP()->Remove(ch);
                }
            }else {
                m_temple->display();
                cout << endl;
                m_temple->displayAttacks();
            }
        }
        
        if (ch == 'c') {
            //Cheat
            m_temple->player()->setMaxHitPoints(50);
            m_temple->player()->setHitPoints(50);
        }
        
        if (ch != 'g' && ch != 'w' && ch != 'r') {
            m_temple->display();
            cout << endl;
            //clearScreen();
            m_temple->displayAttacks();
        }
    
    }

    if (p->isDead())
        cout << "Press q to exit game." << endl;
    
    if (foundGI)
        cout << "You picked up the golden idol" << endl << "Congratuations you won!" << endl;
}
    

void Game::resetTemple()
{
    // Save the player pointer
    Player* player = m_temple->player();
    
    int temp = m_temple->goblinSmellDistance();
    int level = m_temple->level();

    // Delete the old Temple
    m_temple->clearMonsters();
    m_temple->clearObjects();
    
    delete m_temple;
    
    // Reallocate the Temple object
    
    m_temple = new Temple(level);
    
    m_temple->setPlayer(player);
    
    player->setTemple(m_temple);
    
    m_temple->setGoblinSmellDistance(temp);
    
    m_temple->increaseLevel();
    
    int rGoldenIdol = randInt(2, 17);
    int cGoldenIdol = randInt(2, 69);
    while (m_temple->charAt(rGoldenIdol, cGoldenIdol) != ' '){
        rGoldenIdol = randInt(2, 17);
        cGoldenIdol = randInt(2, 69);
    }
    
    if(m_temple->level() < 4){
    int rStairway = randInt(2, 17);
    int cStairway = randInt(2, 69);
    while (m_temple->charAt(rStairway, cStairway) != ' '){
        rStairway = randInt(2, 17);
        cStairway = randInt(2, 69);
    }
    m_temple->addStairway(rStairway, cStairway);
    }
    
    if(m_temple->level() == 4){
        m_temple->addGoldenIdol(rGoldenIdol, cGoldenIdol);
    }
    
    // Randomize Player's Row And Column until it isn't a space similar to Game Contructor Above and do the Same for Monsters.
    int rPlayer = randInt(2, 17);
    int cPlayer = randInt(2, 69);
    while (m_temple->charAt(rPlayer, cPlayer) != ' '){
        rPlayer = randInt(2, 17);
        cPlayer = randInt(2, 69);
    }
    
    
    m_temple->player()->setRow(rPlayer);
    m_temple->player()->setCol(cPlayer);
    
    m_temple->setCharP(m_temple->player()->row() - 1, m_temple->player()->col() - 1);
    
    int M = randInt(2, 5*(m_temple->level()+1)+1);
    int rMonster = randInt(2, 17);
    int cMonster = randInt(2, 69);
    for (int i = 0; i < M; i++){
        while (m_temple->charAt(rMonster, cMonster) != ' ' || m_temple->isMonsterAt(rMonster, cPlayer)){
            rMonster = randInt(2, 17);
            cMonster = randInt(2, 69);
        }
        m_temple->addMonster(rMonster, cMonster);
    }
    
    for (int i = 0; i < m_temple->MonsterVector().size(); i++){
        m_temple->MonsterVector()[i]->setTemple(m_temple);
    }
    
    int rObject = randInt(2, 17);
    int cObject = randInt(2, 69);

    for (int i = 0; i < randInt(2, 3); i++) {
        while (m_temple->charAt(rObject, cObject) != ' ') {
            rObject = randInt(2, 17);
            cObject = randInt(2, 69);
        }
        m_temple->addObjects(rObject, cObject);
    }
}


// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons,
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.
