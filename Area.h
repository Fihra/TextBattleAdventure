#pragma once


#ifndef AREA_H
#define AREA_H
#include <string>
#include <vector>
#include <iostream>

class Area
{
public:
	void MeadowMap();
	void ForestMap();
	void MountainMap();
	void CastleMap();
	void CastleRooms();
	void TrapRoomDisplay();
	void SafeRoomDisplay();
	bool RandomRoom();
	void RestMap();
};

#endif

