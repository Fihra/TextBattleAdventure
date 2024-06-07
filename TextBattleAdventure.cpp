// TestCPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"

void IncrementLevel(std::unique_ptr<Player> &player)
{
    std::cout << "Show Current Level: " << player->getLevel() << "\n";
    std::cout << "Incrementing Level\n";
    player->addLevel();
    std::cout << "New Level: " << player->getLevel() << "\n";
}

int GenerateStats()
{
    int randomNum = rand() % 10 + 1;
    return randomNum;
}

std::map<int, int> GenerateValuesMap()
{
    std::map<int, int> statsValues;

    statsValues[0] = GenerateStats();
    statsValues[1] = GenerateStats();
    statsValues[2] = GenerateStats();

    return statsValues;

}

int RandomEncounter(int num)
{
    return rand() % num + 1;
}

int main()
{
    std::cout << "Text Adventure!\n";

    std::string name;

    std::cout << "What is your name?\n";

    std::cin >> name;


    std::unique_ptr<Enemy> goblin(new Enemy("Goblin", 5, 2, 1));
    //Player player1 = Player(name);
    std::unique_ptr<Player> player1(new Player(name));

    std::cout << "Welcome " << player1->getName() << "\n";

   /* int randomNum = 5;
    int *ptr = &randomNum;
    std::cout << *ptr;*/

    //Player* playerPtr = &player1;
    //std::unique_ptr<Player> playerPtr (player1);

    //IncrementLevel(player1);
    //IncrementLevel(player1);
    IncrementLevel(player1);

    std::cout << "Lets roll for stats" << "\n";
    system("pause");

    //std::map<int, int> statsValues;

    //statsValues[0] = GenerateStats();
    //statsValues[1] = GenerateStats();

    player1->SetStats(GenerateValuesMap());

    //player1->SetStats(statsValues);
    /*for (auto val : statsValues)
    {
        std::cout << val.first << ": " << val.second << "\n";
       
    }*/
    player1->ShowStats();

    char choice;

    do
    {
        std::cout << "Reroll stats? y/n" << "\n";
        std::cin >> choice;
        if (choice == 'y')
        {
            player1->SetStats(GenerateValuesMap());
            player1->ShowStats();
        }
    } while (choice != 'n');

    std::cout << "Ready for Adventure!" << "\n";

    player1->ShowStats();

    int step = 100;

    do
    {
        system("pause");
        step = RandomEncounter(step);
        std::cout << "Stepping: " << step << "\n";

    } while (step > 25);

    std::cout << "BATTLE TIME" << "\n";

    //goblin->ShowStats();
    Battle battle;

    //int& playerHealth = player1->battleStats()[1];

    do
    {
        if (goblin->battleStats()[1] <= 0)
        {
            break;
        }

        battle.Attacking(player1, goblin);
        battle.Defending(goblin, player1);


    } while (player1->battleStats()[1] > 0);

    
   
    std::cout << "done";
}
