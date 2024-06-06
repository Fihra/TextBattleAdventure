#include "Player.h"
#include <iostream>
#include <string>
#include <map>

enum stats {hp , attack, defense };

Player::Player(std::string newName)
{
	name = newName;
	level = 1;
}

std::string Player::getName()
{
	return name;
}

int Player::getLevel()
{
	return level;
}

void Player::addLevel()
{
	level++;
}

void Player::SetStats(std::map<int, int> vals)
{
	for (auto v : vals)
	{
		switch (v.first)
		{
			case 0:
				maxHP = v.second;
				currentHP = maxHP;
				break;
			case 1:
				attack = v.second;
				break;
			case 2:
				defense = v.second;
				break;
		}
		//std::cout << "first: " << v.first << "\n";
		//std::cout << "second: " << v.second << "\n";
	}
}

void Player::ShowStats()
{
	std::cout << "Name: " << name << "\n";
	std::cout << "HP: " << currentHP << "/" << maxHP << "\n";
	std::cout << "Attack: " << attack << "\n";
	std::cout << "Defense: " << defense << "\n";
}

std::vector<int> Player::battleStats()
{
	std::vector<int> battleStats;

	battleStats.push_back(maxHP);
	battleStats.push_back(currentHP);
	battleStats.push_back(attack);
	battleStats.push_back(defense);

	return battleStats;
}

void Player::setHP(std::string command, int amount)
{
	if (command == "attack")
	{
		currentHP -= amount;
	}
	else if (command == "heal")
	{
		currentHP += amount;
		if (currentHP > maxHP)
		{
			currentHP = maxHP;
		}
	}
}