#include "Player.h"
#include <iostream>
#include <string>
#include <map>

enum stats {hp , attack, defense };

Player::Player(std::string newName)
{
	name = newName;
	level = 1;
	totalEXP = 5;
	expToNextLevel = 0;
	isAlive = true;
}

std::string Player::getName()
{
	return name;
}

int Player::getLevel()
{
	return level;
}

bool Player::lifeStatus()
{
	return isAlive;
}

void Player::setLifeStatus(bool status)
{
	isAlive = status;
}

void Player::earnEXP(int exp)
{

	int remainingEXP = expToNextLevel + exp;

	if (remainingEXP >= totalEXP)
	{
		Player::levelUpStats();
		expToNextLevel = 0;
		totalEXP += totalEXP;
		remainingEXP -= totalEXP;
		Player::earnEXP(remainingEXP);
	}

}

void Player::levelUpStats()
{
	std::cout << "LEVEL UP!!!!!!\n";

	int oldHP = maxHP;
	int oldAttack = attack;
	int oldDefense = defense;
	int oldLevel = level;

	level++;
	maxHP += (rand() % 5 + 1);
	currentHP = maxHP;
	attack += (rand() % 5 + 1);
	defense += (rand() % 5 + 1);

	std::cout << "Level: " << oldLevel << " -> " << level << "\n";
	std::cout << "HP: " << oldHP << " -> " << maxHP << "\n";
	std::cout << "Attack: " << oldAttack << " -> " << attack << "\n";
	std::cout << "Defense: " << oldDefense << " -> " << defense << "\n";

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
	}
}

void Player::ShowStats()
{
	std::cout << "Name: " << name << "\n";
	std::cout << "Level: " << level << "\n";
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

void Player::DisplayEXP()
{
	std::cout << "Total EXP: " << totalEXP << "\n";
	Player::ShowStats();
}