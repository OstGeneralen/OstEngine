// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Configuration/CmdArg.h>

//			Handle Var Name			Long form command			Cmd Shorthand	Command Description
CMD_ARG_S(	CMD_VAR(ArgWinWidth),	CMD_FULL(windowWidth),		CMD_SHORT(w),	CMD_DESC("Width of the app window"))
CMD_ARG_S(	CMD_VAR(ArgWinHeight),	CMD_FULL(windowHeight),		CMD_SHORT(h),	CMD_DESC("Height of the app window"))
CMD_ARG_S(	CMD_VAR(ArgAssetsPath),	CMD_FULL(assetsPath),		CMD_SHORT(a),	CMD_DESC("Root directory path for assets"))
CMD_ARG_S(	CMD_VAR(ArgGameModule),	CMD_FULL(gameModule),		CMD_SHORT(g),	CMD_DESC("Name of the game module dll"))