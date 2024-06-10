#include "Area.h"

void Area::MeadowMap()
{
	std::cout << "=======================\n";
	std::cout << "Entering the Meadows\n";
	std::cout << "=======================\n";
	system("pause");
	std::cout << "Strolling across the flat grass~\n";
}

void Area::ForestMap()
{
	std::cout << "=======================\n";
	std::cout << "Entering the Forest\n";
	std::cout << "=======================\n";
	system("pause");
	std::cout << "Treading on the path with surrounding trees.\n";
}

void Area::MountainMap()
{
	std::cout << "=======================\n";
	std::cout << "Entering the Mountain\n";
	std::cout << "=======================\n";
	system("pause");
	std::cout << "Climbing the path up the mountain.\n";
}

void Area::CastleMap()
{
	std::cout << "=======================\n";
	std::cout << "Entering the Castle\n";
	std::cout << "=======================\n";
	system("pause");
}

void Area::CastleRooms()
{
	std::cout << "You approach 3 separate rooms.\n";
	std::cout << "===========================================\n";
	std::cout << "|| Room ||      || Room ||       || Room ||\n";
	std::cout << "||   1  ||      ||   2  ||       ||   3  ||\n";
	std::cout << "||==##==||      ||==##==||       ||==##==||\n";
	std::cout << "											 \n";
	std::cout << "Enter the number of the room you wish to enter: ";
}

void Area::TrapRoomDisplay()
{
	std::cout << "You entered a trap card!\n";
	std::cout << "Spike trap attack!!!\n";
	std::cout << "Prepare to face some damage!\n";
}

void Area::SafeRoomDisplay()
{
	std::cout << "Nothing out of the ordinary in here.\n";
	std::cout << "Just an empty room.\n";
}

bool Area::RandomRoom()
{
	int randomizer = rand() % 100 + 1;

	if (randomizer > 49)
	{
		Area::SafeRoomDisplay();
		return true;
	}
	else
	{
		Area::TrapRoomDisplay();
		return false;
	}
}

void Area::RestMap()
{
	std::cout << "=======================\n";
	std::cout << "Rest stop\n";
	std::cout << "=======================\n";
	system("pause");
}