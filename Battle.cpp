#include "Battle.h"
#include <iostream>
#include <vector>

void Battle::Attacking(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
	player->ShowStats();
	enemy->ShowStats();

	std::cout << player->getName() << " attacks!" << "\n";

	std::vector<int> playerStats = player->battleStats();
	std::vector<int> enemyStats = enemy->battleStats();

	int damageDealing = (playerStats[2] - enemyStats[3]); //player atk - enemy def 
	if (playerStats[2] < enemyStats[3])
	{
		int loweredDamage = enemyStats[3] - playerStats[2];
		if(abs(playerStats[2] - enemyStats[3]) < 5)
		{
			loweredDamage = 3;
		}
		else if (loweredDamage < 0)
		{
			loweredDamage = 1;
		} 

		damageDealing = loweredDamage;
	}

	std::cout << player->getName() << " deals " << damageDealing << " damage to " << enemy->getName() << "\n";

	enemy->setHP("attack", damageDealing);
	DisplayPlayerStats(player, playerStats);
	DisplayEnemyStats(enemy, enemyStats);

	system("pause");

}

void Battle::Defending(std::unique_ptr<Enemy>& enemy, std::unique_ptr<Player>& player)
{
	enemy->ShowStats();
	player->ShowStats();

	std::vector<int> enemyStats = enemy->battleStats();
	std::vector<int> playerStats = player->battleStats();

	int damageDealing = (enemyStats[2] - playerStats[3]); //enemy atk - player def 
	if (playerStats[3] > enemyStats[2])
	{
		int loweredDamage = playerStats[3] - enemyStats[2];
		if(abs(playerStats[3] - enemyStats[2]) < 5)
		{
			loweredDamage = 3;
		}
		else if (loweredDamage < 0)
		{
			loweredDamage = 1;
		} 

		damageDealing = loweredDamage;
	}
	//if (damageDealing < 0) {
	//	damageDealing = 1;
	//}

	std::cout << enemy->getName() << " attacks & deals " << damageDealing << " damage to " << player->getName() << "\n";

	player->setHP("attack", damageDealing);
	DisplayPlayerStats(player, playerStats);
	DisplayEnemyStats(enemy, enemyStats);

	system("pause");
}

void Battle::DisplayPlayerStats(std::unique_ptr<Player>& player, std::vector<int> stats)
{
	int maxHP = stats[0];
	int currentHP = stats[1];
	int atk = stats[2];
	int def = stats[3];

	std::cout << "Name: " << player->getName() << "\n";
	std::cout << "HP: " << currentHP << "/" << maxHP << "\n";
}

void Battle::DisplayEnemyStats(std::unique_ptr<Enemy>& enemy, std::vector<int> stats)
{
	int maxHP = stats[0];
	int currentHP = stats[1];
	int atk = stats[2];
	int def = stats[3];

	std::cout << "Name: " << enemy->getName() << "\n";
	std::cout << "HP: " << currentHP << "/" << maxHP << "\n";
}