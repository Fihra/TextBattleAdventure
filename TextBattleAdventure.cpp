// TestCPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <Windows.h>
#include <Mmsystem.h>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"
#include "Area.h"

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

void worldTravel()
{
    int step = 1000;

    do
    {
        system("pause");
        step = RandomEncounter(step);
        std::cout << "Stepping: " << step << "\n";

    } while (step > 25);
}

void battleSequence(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
    std::cout << "====================\n";
    std::cout << "BATTLE TIME" << "\n";
    std::cout << "====================\n";
    sf::Music battleMusic;

    if (!battleMusic.openFromFile("BattleTheme_Test.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    battleMusic.setLoop(true);
    battleMusic.play();

    Battle battle;

    //int& playerHealth = player1->battleStats()[1];
    //PlaySound(TEXT("BattleTheme_Test.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    do
    {
        battle.Attacking(player, enemy);
       
        if (enemy->battleStats()[1] <= 0)
        {
            break;
        }
        battle.Defending(enemy, player);

    } while (player->battleStats()[1] > 0);

    std::cout << "===============================\n";
    std::cout << "Hooray!! You won the battle!\n";
    player->ShowStats();
    player->earnEXP(enemy->getEXP());
    std::cout << "LEVEL UP!!!!!!\n";
    player->DisplayEXP();
    std::cout << "===============================\n";

    battleMusic.stop();
}

int main()
{
    std::cout << "Auto Battle Text Adventure!\n";
    std::cout << "What is your name?\n";
    std::string name;
    std::cin >> name;

    std::unique_ptr<Enemy> goblin(new Enemy("Goblin", 5, 2, 1, 5));
    std::unique_ptr<Player> player1(new Player(name));
    std::cout << "Welcome " << player1->getName() << "\n";
    //Player player1 = Player(name);
   /* int randomNum = 5;
    int *ptr = &randomNum;
    std::cout << *ptr;*/

    //Player* playerPtr = &player1;
    //std::unique_ptr<Player> playerPtr (player1);

    //IncrementLevel(player1);

    std::cout << "Lets roll for stats" << "\n";
    system("pause");

    srand(time(0));

    player1->SetStats(GenerateValuesMap());
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

    sf::Music travelMusic;
    //PlaySound(TEXT("Travel_Theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
   
    if (!travelMusic.openFromFile("Travel_Theme.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    travelMusic.setLoop(true);
    travelMusic.play();
    std::cout << "Ready for Adventure!" << "\n";

    player1->ShowStats();

    std::cout << "You are traveling across the main road towards the Evil Castle. \n";
    std::cout << "Every step you take...\n";

    worldTravel();
    travelMusic.pause();
    battleSequence(player1, goblin);

    travelMusic.play();
    std::cout << "Back on the road!\n";

    std::unique_ptr<Enemy> goblin2(new Enemy("Goblin2", 7, 4, 3, 10));

    worldTravel();

    travelMusic.pause();

    battleSequence(player1, goblin2);
    travelMusic.play();
    //PlaySound(TEXT("Travel_Theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    worldTravel();

    std::cout << "You have reached a fork in the road.\n";
    std::cout << "The left road looks like it leads into a meadow.\n";
    std::cout << "The right road looks like a deep forest ahead.\n";

    char forkOneChoice;

    std::string areas[4] = {"meadow", "forest", "mountain", "castle"};
    std::string currentArea;
    std::unique_ptr<Area> mainArea;

    do 
    {
        std::cout << "Which way do you go? (l)eft/(r)ight" << std::endl;
        std::cin >> forkOneChoice;

        switch (forkOneChoice)
        {
        case 'l':
            currentArea = areas[0];
            //mainArea->setCurrentArea(areas[0]);

            break;
        case 'r':
            currentArea = areas[1];
            //mainArea->setCurrentArea(areas[1]);
            break;
        }
    } while (forkOneChoice != 'l' && forkOneChoice != 'r');

    std::cout << "You take the path to the " << currentArea << ".\n";
    //std::cout << "You take the path to the " << mainArea->getCurrentArea() << ".\n";

    if (currentArea == "meadow")
    {
        mainArea->MeadowMap();
        worldTravel();
        std::unique_ptr<Enemy> mushdoom(new Enemy("Mushdoom", 10, 5, 5, 20));
        travelMusic.pause();
        battleSequence(player1, mushdoom);
        travelMusic.play();
        worldTravel();
        std::unique_ptr<Enemy> boisonFlora(new Enemy("BoisonFlora", 25, 4, 9, 50));
        travelMusic.pause();
        battleSequence(player1, boisonFlora);
        travelMusic.play();

    }
    else if (currentArea == "forest")
    {
        mainArea->ForestMap();
        worldTravel();
        mainArea->RestMap();
        worldTravel();
        std::unique_ptr<Enemy> squirrelSoldier(new Enemy("Squirrel Soldier", 15, 7, 4, 20));
        travelMusic.pause();
        battleSequence(player1, squirrelSoldier);
        travelMusic.play();
        worldTravel();
        std::unique_ptr<Enemy> dearDeer(new Enemy("Dear Deer", 20, 8, 5, 50));
        travelMusic.pause();
        battleSequence(player1, dearDeer);
        travelMusic.play();
    }

    mainArea->RestMap();
    mainArea->MountainMap();
    //worldTravel();


    system("pause");
    std::cout << "done";
}
