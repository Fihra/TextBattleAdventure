#pragma once

#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <vector>

class Enemy
{
private:
	std::string name;
	int maxHP;
	int currentHP;
	int attack;
	int defense;
public:
	Enemy(std::string newName, int newHP, int newAttack, int defense);
	std::string getName();
	void ShowStats();
	std::vector<int> battleStats();
	void setHP(std::string command, int amount);
};

#endif