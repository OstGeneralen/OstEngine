#include "GameInstance.h"
#include <OstLog/OstLogger.h>

#include <iostream>

OSTLOG_LOG_INSTANCE(GameLog);

class CTestComponent
{

};

std::string game::CGameInstance::GameTitle() const
{
	return "My Ost Engine Game";
}

void game::CGameInstance::RegisterGameComponents(ost::CComponentTypeRegistry& registry)
{
}
#include <OstEngine/Game/Core/TransformComponent.h>

void game::CGameInstance::OnLoad()
{
	auto scene = pEngine->NewScene(true);
	auto obj = scene->CreateObject("Test object");
	auto obj2 = scene->CreateObject("Wooo");
	obj->GetComponent<ost::CTransformComponent>();
}

void game::CGameInstance::OnTick()
{
}

void game::CGameInstance::OnUnload()
{
}