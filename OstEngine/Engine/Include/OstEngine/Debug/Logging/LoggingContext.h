// OstEngine - Copyright(c) 2025 Kasper Esbj�rnsson (MIT License)
#pragma once

// ------------------------------------------------------------

namespace ost
{
	class CLoggingContext
	{
	public:
		static void Create();
		static void Bind(CLoggingContext* context);
		static CLoggingContext* Get();



	private:
		static CLoggingContext* s_pInstance;
		static bool s_instanceBound;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------