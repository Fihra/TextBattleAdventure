#pragma once
#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h";
#include "Enemy.h";
#include <memory>
#include <vector>

class Battle
{
public:
	void Attacking(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy);
	void Defending(std::unique_ptr<Enemy>& enemy, std::unique_ptr<Player>& player);
	void DisplayPlayerStats(std::unique_ptr<Player>& player, std::vector<int> stats);
	void DisplayEnemyStats(std::unique_ptr<Enemy>& enemy, std::vector<int> stats);
};

#endif
