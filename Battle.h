#pragma once
#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h";
#include "Enemy.h";
#include <memory>

class Battle
{
public:
	void Attacking(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy);
	void Defending(std::unique_ptr<Enemy>& enemy, std::unique_ptr<Player>& player);
};

#endif
