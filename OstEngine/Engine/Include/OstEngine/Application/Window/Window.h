// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <string>


// ------------------------------------------------------------

namespace ost
{
	struct SWindowSettings
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		void* InstanceInfo;
		int InstanceFlags;
	};

	class CWindow
	{
	public:
		void Create(const SWindowSettings& settings);
		void ProcessEvents();

		void Close();
		bool IsOpen() const;

	private:
		void RecalcDPIAwareSize();

		void* _winHandle;
		int _w, _h;
		bool _open;

	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------