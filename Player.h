#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <vector>

class Player
{
private:
	std::string name;
	int level;
	int maxHP;
	int currentHP;
	int attack;
	int defense;
	int totalEXP;
	int expToNextLevel;

public:
	Player(std::string newName);
	std::string getName();
	int getLevel();
	void addLevel();
	void SetStats(std::map<int, int> vals);
	void ShowStats();
	void earnEXP(int exp);
	void levelUpStats();
	std::vector<int> battleStats();
	void setHP(std::string command, int amount);
};

#endif