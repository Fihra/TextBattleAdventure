#include "Enemy.h"
#include <iostream>
#include <string>
#include <map>

Enemy::Enemy(std::string newName, int newHP, int newAttack, int newDefense, int newEXP)
{
	name = newName;
	maxHP = newHP;
	currentHP = maxHP;
	attack = newAttack;
	defense = newDefense;
	expGiven = newEXP;
}

std::string Enemy::getName()
{
	return name;
}

void Enemy::ShowStats()
{
	std::cout << "Name: " << name << "\n";
	std::cout << "HP: " << currentHP << "/" << maxHP << "\n";
	std::cout << "Atk: " << attack << "\n";
	std::cout << "Def: " << defense << "\n";
}

int Enemy::getEXP()
{
	return expGiven;
}

std::vector<int> Enemy::battleStats()
{
	std::vector<int> battleStats;

	battleStats.push_back(maxHP);
	battleStats.push_back(currentHP);
	battleStats.push_back(attack);
	battleStats.push_back(defense);

	return battleStats;
}

void Enemy::setHP(std::string command, int amount)
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