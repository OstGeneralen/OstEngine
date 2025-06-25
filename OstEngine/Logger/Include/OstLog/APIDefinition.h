// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/APIDefinition.h"

// ------------------------------------------------------------

#if LOGGER_DLL_BUILD
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------