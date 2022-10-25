#include "Rendering/Public/TestService.h"
#include <Common/Public/Debugging/Logging/Logging.h>

DEFINE_LOG(TestServiceLog);

void ost::CTestRenderingService::CallMe()
{
	LOG_VERBOSE(TestServiceLog, "Yoinkers badoinkers");
}