#include "GameInstance.h"

#include <iostream>

std::string game::CGameInstance::GameTitle() const
{
	return "My Ost Engine Game";
}

void game::CGameInstance::Run()
{
	std::cout << "This is printed from the game instance yo" << std::endl;
}