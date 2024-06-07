// TestCPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <Windows.h>
#include <windows.h>
#include <Mmsystem.h>
#include  <mciapi.h>
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"

#pragma comment(lib, "winmm.lib")

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
    std::cout << "What is your name?\n";
    std::string name;
    std::cin >> name;

    //sndPlaySound("BattleThemeTest.wav", SND_FILENAME | SND_ASYNC);
    //mciSendString("play wav", NULL, 0, NULL);
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
    srand(time(0));

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
    PlaySound(TEXT("Travel_Theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    std::cout << "Ready for Adventure!" << "\n";

    player1->ShowStats();

    std::cout << "You are traveling across the main road towards the Evil Castle. \n";
    std::cout << "Every step you take...\n";

    int step = 1000;

    do
    {
        system("pause");
        step = RandomEncounter(step);
        std::cout << "Stepping: " << step << "\n";

    } while (step > 25);
    
    std::cout << "BATTLE TIME" << "\n";
    step = 1000;
    Battle battle;

    //int& playerHealth = player1->battleStats()[1];
    PlaySound(TEXT("BattleTheme_Test.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    do
    {
        //mciSendString("play BattleTheme_Test.wav", NULL, 0, NULL);
        
        
        if (goblin->battleStats()[1] <= 0)
        {
            break;
        }

        battle.Attacking(player1, goblin);
        battle.Defending(goblin, player1);


    } while (player1->battleStats()[1] > 0);

    //PlaySound(0, 0, 0);
    PlaySound(TEXT("Travel_Theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    system("pause");
    std::cout << "done";
}
