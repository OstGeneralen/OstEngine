#include "GameInstance.h"
#include <OstEngine/ObjectSystem/Component/Component.h>
#include <OstLog/OstLogger.h>

#include <iostream>

OSTLOG_LOG_INSTANCE(GameLog);

class MyCustomComponent : public ost::CComponent
{
};


std::string game::CGameInstance::GameTitle() const
{
	return "My Ost Engine Game";
}

void game::CGameInstance::RegisterGameComponentTypes(ost::CComponentRegistry& registry) const
{
	registry.RegisterComponentType<MyCustomComponent>();
}

void game::CGameInstance::Shutdown()
{
	GameLog.Log(OstLogLevel::Info, "Shutdown invoked on game");
}
