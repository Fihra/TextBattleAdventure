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

    if (!battleMusic.openFromFile("music/Fierce_Fight-Battle_Text_Adventure.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    battleMusic.setLoop(true);
    battleMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(22.588)));
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

void bossSequence(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
    std::cout << "====================\n";
    std::cout << "Boss TIME" << "\n";
    std::cout << "====================\n";
    sf::Music bossMusic;

    if (!bossMusic.openFromFile("music/Beat_the_Boss-Battle_Text_Adventure.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    bossMusic.setLoop(true);
    bossMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(31.999)));
    bossMusic.play();

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

    bossMusic.stop();
}

int main()
{
    sf::Music startMusic;
    if (!startMusic.openFromFile("music/Beginning-Battle_Text_Adventure.wav"))
    {
        std::cout << "Error Loading Music\n";
    }
    startMusic.setLoop(true);
    startMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0),sf::seconds(42.666)));
    startMusic.play();

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

    srand((unsigned int)time(NULL));

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

    startMusic.stop();

    sf::Music travelMusic;
    //PlaySound(TEXT("Travel_Theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
   
    if (!travelMusic.openFromFile("music/Open_Travel-Battle_Text_Adventure.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    travelMusic.setLoop(true);
    travelMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(28.800)));
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
            break;
        case 'r':
            currentArea = areas[1];
            break;
        }
    } while (forkOneChoice != 'l' && forkOneChoice != 'r');

    std::cout << "You take the path to the " << currentArea << ".\n";
    travelMusic.stop();
    if (currentArea == "meadow")
    {
        sf::Music meadowMusic;

        if (!meadowMusic.openFromFile("music/Meadows-Battle_Text_Adventure.wav"))
        {
            std::cout << "ERror loadin music\n";
        }
        meadowMusic.setLoop(true);
        meadowMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(32)));
        meadowMusic.play();

        mainArea->MeadowMap();
        worldTravel();
        std::unique_ptr<Enemy> mushdoom(new Enemy("Mushdoom", 10, 5, 5, 20));
        meadowMusic.pause();
        battleSequence(player1, mushdoom);
        meadowMusic.play();
        worldTravel();
        std::unique_ptr<Enemy> boisonFlora(new Enemy("BoisonFlora", 25, 4, 9, 50));
        meadowMusic.pause();
        bossSequence(player1, boisonFlora);
        meadowMusic.play();
        meadowMusic.stop();

    }
    else if (currentArea == "forest")
    {
        sf::Music forestMusic;

        if (!forestMusic.openFromFile("music/Forestry-Battle_Text_Adventure.wav"))
        {
            std::cout << "ERror loadin music\n";
        }
        forestMusic.setLoop(true);
        forestMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(27.692)));
        forestMusic.play();

        mainArea->ForestMap();
        worldTravel();
        mainArea->RestMap();
        worldTravel();
        std::unique_ptr<Enemy> squirrelSoldier(new Enemy("Squirrel Soldier", 15, 7, 4, 20));
        forestMusic.pause();
        battleSequence(player1, squirrelSoldier);
        forestMusic.play();
        worldTravel();
        //Add Boss Music
        std::unique_ptr<Enemy> dearDeer(new Enemy("Dear Deer", 20, 8, 5, 50));
        forestMusic.pause();
        bossSequence(player1, dearDeer);
        forestMusic.play();
        forestMusic.play();
    }

    travelMusic.play();
    sf::Music mountainMusic;

    mainArea->RestMap();
    travelMusic.stop();
    mainArea->MountainMap();

    if (!mountainMusic.openFromFile("music/Mountain_Climb-Battle_Text_Adventure.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    mountainMusic.setLoop(true);
    mountainMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(28.800)));
    mountainMusic.play();
    

    worldTravel();
    //Add Mountain Music
    mountainMusic.pause();
    std::unique_ptr<Enemy> mountainGiant(new Enemy("Mountain Giant", 25, 8, 6, 75));
    battleSequence(player1, mountainGiant);
    mountainMusic.play();

    worldTravel();
    std::unique_ptr<Enemy> flareFowl(new Enemy("Flare Fowl", 30, 10, 4, 100));
    mountainMusic.pause();
    battleSequence(player1, flareFowl);
    mountainMusic.play();

    mainArea->CastleMap();
    //Add Castle Music
    mainArea->CastleRooms();

    int roomChoice;

    do 
    {
        std::cin >> roomChoice;

        switch ((int)roomChoice)
        {
        case 1:
            std::cout << "You entered room 1";
            break;
        case 2:
            std::cout << "You entered room 2";
            break;
        case 3:
            std::cout << "You entered room 3";
            break;
        }
    } while (roomChoice < 0 && roomChoice > 3);

    bool enterRoom = mainArea->RandomRoom();

    if (!enterRoom)
    {
        int trapDamage = rand() % 5 + 1;
        player1->setHP("attack", trapDamage);
    }
    else
    {
        std::cout << "Onwards!\n";
    }

    worldTravel();
    mainArea->RestMap();

    std::unique_ptr<Enemy> chaoticWizard(new Enemy("Chaotic Wizard", 100, 5, 3, 100));
    battleSequence(player1, chaoticWizard);

    std::cout << "You Did it!! You defeated the Chaotic wizard terrorizing the world!\n";
    std::cout << "Congrats " << player1->getName() << "!!!!\n";

    std::cout << "=============================================\n";
    std::cout << "=TTTTT   H   H  EEE    EEE  N     N   DDD   =\n";
    std::cout << "=  T     H   H  E      E    N N   N   D  D  =\n";
    std::cout << "=  T     HHHHH  EEE    EEE  N  N  N   D   D =\n";
    std::cout << "=  T     H   H  E      E    N   N N   D  D  =\n";
    std::cout << "=  T     H   H  EEE    EEE  N     N   DDD   =\n";


    system("pause");
    std::cout << "done";
}
