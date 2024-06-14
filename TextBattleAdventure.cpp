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

sf::SoundBuffer buffer;
sf::Sound sound;

std::map<std::string, std::string> sfxMap = {
        {"damagedSFX", "sfx/damagedSFX.wav"},
        {"deathSFX", "sfx/deathSFX.wav"},
        {"levelUpSFX", "sfx/levelUpSFX.wav"},
        {"enemyAttack1SFX", "sfx/enemyAttack1SFX.wav"},
        {"enemyAttack2SFX", "sfx/enemyAttack2SFX.wav"},
        {"enemyAttack3SFX", "sfx/enemyAttack3SFX.wav"},
        {"playerAttack1SFX", "sfx/playerAttack1SFX.wav"},
        {"playerAttack2SFX", "sfx/playerAttack2SFX.wav"},
        {"playerAttack3SFX", "sfx/playerAttack3SFX.wav"},
};

void PlaySFX(sf::SoundBuffer& buffer, sf::Sound& sound, std::string& fileURL)
{
    buffer.loadFromFile(fileURL);
    sound.setBuffer(buffer);
    sound.play();
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

void FadeOutMusic(sf::Music& musicTrack)
{
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    float volume = 100.f;
    clock.restart();

    while (true)
    {
        if (clock.getElapsedTime().asSeconds() > 0.20f)
        {
            if (volume <= 0)
            {
                break;
            }
            else
            {
                musicTrack.setVolume(volume -= 12.5f);
            }
            clock.restart();
        }
    }
    musicTrack.pause();
}

void FadeInMusic(sf::Music& musicTrack)
{
    musicTrack.setVolume(0);
    musicTrack.play();
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    clock.restart();

    float volume = 0.f;

    while (true)
    {
        if (clock.getElapsedTime().asSeconds() > 0.20f)
        {
            if (volume >= 100)
            {
                break;
            }
            else
            {
                musicTrack.setVolume(volume += 12.5f);
            }
            clock.restart();
        }
    }
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

    bool isAlive = true;

    //int& playerHealth = player1->battleStats()[1];
    //PlaySound(TEXT("BattleTheme_Test.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    do
    {
        battle.Attacking(player, enemy);
        PlaySFX(buffer, sound, sfxMap["playerAttack1SFX"]);

        if (enemy->battleStats()[1] <= 0)
        {
            PlaySFX(buffer, sound, sfxMap["deathSFX"]);
            break;
        }
        battle.Defending(enemy, player);
        PlaySFX(buffer, sound, sfxMap["enemyAttack1SFX"]);

        if (player->battleStats()[1] <= 0)
        {
            isAlive = false;
            break;
        }

    } while (player->battleStats()[1] > 0);


    if (isAlive)
    {
        std::cout << "===============================\n";
        std::cout << "Hooray!! You won the battle!\n";
        std::cout << enemy->getName() << " dropped " << enemy->getEXP() << " EXP.\n";
        int oldLevel = player->getLevel();
        player->earnEXP(enemy->getEXP());
        if (player->getLevel() > oldLevel)
        {
            PlaySFX(buffer, sound, sfxMap["levelUpSFX"]);
        }
        std::cout << "===============================\n";
    }
    else
    {
        std::cout << "===============================\n";
        std::cout << "Ooooof!! REMATCH!!!\n";
        player->setLifeStatus(true);
        player->setHP("heal", 100);
        enemy->setHP("heal", 100);
        std::cout << "Quick level grind!\n";
        player->levelUpStats();
        PlaySFX(buffer, sound, sfxMap["levelUpSFX"]);
        std::cout << "===============================\n";
        system("pause");
        battleMusic.stop();
        battleSequence(player, enemy);
       
    }

    FadeOutMusic(battleMusic);
    //battleMusic.stop();
}

void bossSequence(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy, bool isFinalBoss = false)
{
    std::cout << "====================\n";
    std::cout << "Boss TIME" << "\n";
    std::cout << "====================\n";
    sf::Music bossMusic;

    if (isFinalBoss)
    {
        if (!bossMusic.openFromFile("music/Wizard_Showdown-Battle_Text_Adventure.wav"))
        {
            std::cout << "ERror loadin music\n";
        }
        bossMusic.setLoop(true);
        bossMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(64)));
        bossMusic.play();
    }
    else
    {
        if (!bossMusic.openFromFile("music/Beat_the_Boss-Battle_Text_Adventure.wav"))
        {
            std::cout << "ERror loadin music\n";
        }
        bossMusic.setLoop(true);
        bossMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(31.999)));
        bossMusic.play();
    }

    Battle battle;
    bool isAlive = true;

    //int& playerHealth = player1->battleStats()[1];
    //PlaySound(TEXT("BattleTheme_Test.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    do
    {
        battle.Attacking(player, enemy);
        PlaySFX(buffer, sound, sfxMap["playerAttack1SFX"]);

        if (enemy->battleStats()[1] <= 0)
        {
            PlaySFX(buffer, sound, sfxMap["deathSFX"]);
            break;
        }
        battle.Defending(enemy, player);
        PlaySFX(buffer, sound, sfxMap["damagedSFX"]);

        if (player->battleStats()[1] <= 0)
        {
            player->setLifeStatus(false);
            break;
        }

    } while (player->battleStats()[1] > 0);


    if (player->lifeStatus())
    {
        std::cout << "===============================\n";
        std::cout << "Hooray!! You won the battle!\n";
        //player->ShowStats();
        int oldLevel = player->getLevel();
        player->earnEXP(enemy->getEXP());
        if (player->getLevel() > oldLevel)
        {
            PlaySFX(buffer, sound, sfxMap["levelUpSFX"]);
        }
        std::cout << enemy->getName() << " dropped " << enemy->getEXP() << " EXP.\n";

        //player->DisplayEXP();
        std::cout << "===============================\n";
    }
    else
    {
        std::cout << "===============================\n";
        std::cout << "Ooooof!! REMATCH!!!\n";
        player->setLifeStatus(true);
        player->setHP("heal", 100);
        enemy->setHP("heal", 100);
        std::cout << "Quick level grind!\n";
        player->levelUpStats();
        PlaySFX(buffer, sound, sfxMap["levelUpSFX"]);
        std::cout << "===============================\n";
        system("pause");
        bossMusic.stop();
        bossSequence(player, enemy, isFinalBoss);
    }

    FadeOutMusic(bossMusic);
    //bossMusic.stop();
}

void finalBossSequence(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
    std::cout << "====================\n";
    std::cout << "Boss TIME" << "\n";
    std::cout << "====================\n";

    Battle battle;
    bool isAlive = true;

    //int& playerHealth = player1->battleStats()[1];
    //PlaySound(TEXT("BattleTheme_Test.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    do
    {
        battle.Attacking(player, enemy);
        PlaySFX(buffer, sound, sfxMap["playerAttack1SFX"]);

        if (enemy->battleStats()[1] <= 0)
        {
            PlaySFX(buffer, sound, sfxMap["deathSFX"]);
            break;
        }
        battle.Defending(enemy, player);
        PlaySFX(buffer, sound, sfxMap["enemyAttack1SFX"]);

        if (player->battleStats()[1] <= 0)
        {
            player->setLifeStatus(false);
            break;
        }

    } while (player->battleStats()[1] > 0);


    if (player->lifeStatus())
    {
        std::cout << "===============================\n";
        std::cout << "Hooray!! You won the battle!\n";
        //player->ShowStats();
        int oldLevel = player->getLevel();
        player->earnEXP(enemy->getEXP());
        if (player->getLevel() > oldLevel)
        {
            PlaySFX(buffer, sound, sfxMap["levelUpSFX"]);
        }
        std::cout << enemy->getName() << " dropped " << enemy->getEXP() << " EXP.\n";

        //player->DisplayEXP();
        std::cout << "===============================\n";
    }
    else
    {
        std::cout << "===============================\n";
        std::cout << "Ooooof!! REMATCH!!!\n";
        player->setLifeStatus(true);
        player->setHP("heal", 100);
        enemy->setHP("heal", 100);
        std::cout << "Quick level grind!\n";
        player->levelUpStats();
        PlaySFX(buffer, sound, sfxMap["levelUpSFX"]);
        std::cout << "===============================\n";
        system("pause");
        finalBossSequence(player, enemy);
    }
    //bossMusic.stop();
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

    std::cout << "____________________________\n";
    std::cout << "|Auto Battle Text Adventure|\n";
    std::cout << "____________________________\n";
    std::cout << "                            ^    *      ^   ^    " << std::endl;
    std::cout << "                          ^ |   / \\     |   |    " << std::endl;
    std::cout << "                       ^  |    |   |     ^      " << std::endl;
    std::cout << "      __               |       |   |     |  ^   " << std::endl;
    std::cout << "     /  \\           ^         ^|___| ^      |   " << std::endl;
    std::cout << "     \\  /           |   ^ ^ ^| ^     |^        " << std::endl;
    std::cout << "      ||                | |^|  |    ^ |  ^      " << std::endl;
    std::cout << "____/|__|\\____       ^     | ^  ^   |  ^ |      " << std::endl;
    std::cout << "   / |__| \\    \\     |       |  |      |       " << std::endl;
    std::cout << "    /_/\\_\\      \\                               " << std::endl;
    std::cout << "_________________\\                              " << std::endl;

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

    FadeOutMusic(startMusic);
    startMusic.stop();

    sf::Music travelMusic;
    //PlaySound(TEXT("Travel_Theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
   
    if (!travelMusic.openFromFile("music/Open_Travel-Battle_Text_Adventure.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
   
    std::cout << "Ready for Adventure!" << "\n";

    travelMusic.setLoop(true);
    travelMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(28.800)));
    FadeInMusic(travelMusic);
    //travelMusic.play();

    player1->ShowStats();

    std::cout << "You are traveling across the main road towards the Evil Castle. \n";
    std::cout << "Every step you take...\n";

    worldTravel();
    travelMusic.pause();
    battleSequence(player1, goblin);

    FadeInMusic(travelMusic);
    //travelMusic.play();
    std::cout << "Back on the road!\n";

    std::unique_ptr<Enemy> goblin2(new Enemy("Goblin2", 7, 4, 3, 10));

    worldTravel();

    travelMusic.pause();

    battleSequence(player1, goblin2);
    FadeInMusic(travelMusic);
    //travelMusic.play();
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
    FadeOutMusic(travelMusic);
    //travelMusic.stop();
    if (currentArea == "meadow")
    {
        sf::Music meadowMusic;

        if (!meadowMusic.openFromFile("music/Meadows-Battle_Text_Adventure.wav"))
        {
            std::cout << "ERror loadin music\n";
        }
        meadowMusic.setLoop(true);
        meadowMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(32)));
        FadeInMusic(meadowMusic);
        //meadowMusic.play();

        mainArea->MeadowMap();
        worldTravel();
        std::unique_ptr<Enemy> mushdoom(new Enemy("Mushdoom", 10, 5, 5, 20));
        meadowMusic.pause();
        battleSequence(player1, mushdoom);
        FadeInMusic(meadowMusic);
        //meadowMusic.play();
        worldTravel();
        std::unique_ptr<Enemy> boisonFlora(new Enemy("BoisonFlora", 25, 4, 9, 50));
        meadowMusic.pause();
        bossSequence(player1, boisonFlora);
        FadeInMusic(meadowMusic);
        //meadowMusic.play();
        FadeOutMusic(meadowMusic);
        //meadowMusic.stop();

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
        FadeInMusic(forestMusic);
        //forestMusic.play();

        mainArea->ForestMap();
        worldTravel();
        mainArea->RestMap();
        worldTravel();
        std::unique_ptr<Enemy> squirrelSoldier(new Enemy("Squirrel Soldier", 15, 7, 4, 20));
        forestMusic.pause();
        battleSequence(player1, squirrelSoldier);
        FadeInMusic(forestMusic);
        //forestMusic.play();
        worldTravel();
        std::unique_ptr<Enemy> dearDeer(new Enemy("Dear Deer", 20, 8, 5, 50));
        forestMusic.pause();
        bossSequence(player1, dearDeer);
        FadeInMusic(forestMusic);
        //forestMusic.play();
        FadeOutMusic(forestMusic);
    }

    FadeInMusic(travelMusic);
    //travelMusic.play();
    sf::Music mountainMusic;

    mainArea->RestMap();
    FadeOutMusic(travelMusic);
    //travelMusic.stop();
    
    if (!mountainMusic.openFromFile("music/Mountain_Climb-Battle_Text_Adventure.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    mountainMusic.setLoop(true);
    mountainMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(28.800)));
    //mountainMusic.play();
    FadeInMusic(mountainMusic);

    mainArea->MountainMap();

    worldTravel();
    //Add Mountain Music
    mountainMusic.pause();
    std::unique_ptr<Enemy> mountainGiant(new Enemy("Mountain Giant", 25, 8, 6, 75));
    battleSequence(player1, mountainGiant);
    FadeInMusic(mountainMusic);
    //mountainMusic.play();

    worldTravel();
    std::unique_ptr<Enemy> flareFowl(new Enemy("Flare Fowl", 30, 10, 4, 100));
    mountainMusic.pause();
    battleSequence(player1, flareFowl);
    FadeInMusic(mountainMusic);
    //mountainMusic.play();

    mainArea->CastleMap();
    FadeOutMusic(mountainMusic);
    //mountainMusic.stop();

    sf::Music castleMusic;

    if (!castleMusic.openFromFile("music/Castle_Wandering-Battle_Text_Adventure.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    castleMusic.setLoop(true);
    castleMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(41.142)));
    FadeInMusic(castleMusic);
    //castleMusic.play();

    mainArea->CastleRooms();

    std::cout << "Walking through the corridors and hallways in this spoopy scary castle.\n";

    int roomChoice;
    do 
    {
        std::cin >> roomChoice;

        switch ((int)roomChoice)
        {
        case 1:
            std::cout << "You entered room 1\n";
            break;
        case 2:
            std::cout << "You entered room 2\n";
            break;
        case 3:
            std::cout << "You entered room 3\n";
            break;
        }
    } while ((int)roomChoice < 0 && (int)roomChoice > 3);

    bool enterRoom = mainArea->RandomRoom();

    if (!enterRoom)
    {
        std::cout << "TRAP TIME!!\n";
        int trapDamage = rand() % 5 + 1;
        player1->setHP("attack", trapDamage);
        PlaySFX(buffer, sound, sfxMap["damagedSFX"]);
        player1->ShowStats();
    }
    else
    {
        std::cout << "Onwards!\n";
    }

    worldTravel();
    mainArea->RestMap();
    
    std::cout << "You enter the throne room of the castle. \n";
    std::cout << "There is a wizard sitting at the throne. \n";
    system("pause");
    std::cout << "Wizard: WHO YOU?!!? Why has you come to \n";
    std::cout << "my castle?? You dare challenge meh?!!!! \n";
    std::cout << "-----------------------------------------\n";
    system("pause");
    std::cout << player1->getName() << ": I am here to stop\n";
    std::cout << "with you evil ways of destruction!!\n";
    std::cout << "-----------------------------------------\n";
    system("pause");
    std::cout << "Wizard: MWAHAHAHAHA! DO YOUR WORSE!!!!\n";
    std::cout << "-----------------------------------------\n";
    system("pause");
    castleMusic.stop();

    std::unique_ptr<Enemy> chaoticWizard(new Enemy("Chaotic Wizard", 100, 5, 3, 100));

    sf::Music bossMusic;

    if (!bossMusic.openFromFile("music/Wizard_Showdown-Battle_Text_Adventure.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    bossMusic.setLoop(true);
    bossMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(64)));
    bossMusic.play();

    finalBossSequence(player1, chaoticWizard);
    FadeOutMusic(bossMusic);

    sf::Music endingMusic;

    if (!endingMusic.openFromFile("music/The_End-Battle_Text_Adventure.wav"))
    {
        std::cout << "ERror loadin music\n";
    }
    endingMusic.setLoop(true);
    endingMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0), sf::seconds(21.333)));
    endingMusic.play();

    std::cout << "You Did it!! You defeated the Chaotic wizard terrorizing the world!\n";
    std::cout << "Congrats " << player1->getName() << "!!!!\n";

    std::cout << "=============================================\n";
    std::cout << "=TTTTT   H   H  EEE    EEE  N     N   DDD   =\n";
    std::cout << "=  T     H   H  E      E    N N   N   D  D  =\n";
    std::cout << "=  T     HHHHH  EEE    EEE  N  N  N   D   D =\n";
    std::cout << "=  T     H   H  E      E    N   N N   D  D  =\n";
    std::cout << "=  T     H   H  EEE    EEE  N     N   DDD   =\n";
    std::cout << "=============================================\n";


    system("pause");
    std::cout << "done";
}
