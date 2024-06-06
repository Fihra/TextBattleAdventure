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

	int damageDealing = playerStats[2] - enemyStats[3];

	std::cout << player->getName() << " deals " << damageDealing << " damage to " << enemy->getName() << "\n";



	for (auto i : playerStats)
	{
		std::cout << i << "\n";
	}

}