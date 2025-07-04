// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/GameObject.h>
#include <OstEngine/ObjectSystem/Scene.h>
#include <OstEngine/ObjectSystem/Registration/ComponentTypeRegistry.h>
#include <OstEngine/ObjectSystem/ManagedType/ManagedTypeContainer.h>

namespace ost
{
	class CObjectSystem
	{
	public:
		CComponentTypeRegistry& GetComponentTypeRegistry();

		void SetActiveScene(TPtr<CScene> scene);
		TPtr<CScene> CreateScene(bool makeActive);

		void TickActiveScene();

		void SweepUnreferenced();
	private:
		CComponentTypeRegistry _componentTypeRegistry;
		TManagedTypeContainer<CScene> _scenes;

		TPtr<CScene> _activeScene;
	};
}

