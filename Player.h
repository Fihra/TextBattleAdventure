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

public:
	Player(std::string newName);
	std::string getName();
	int getLevel();
	void addLevel();
	void SetStats(std::map<int, int> vals);
	void ShowStats();
	std::vector<int> battleStats();
	void setHP(std::string command, int amount);
};

#endif