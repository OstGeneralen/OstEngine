#pragma once
#include <OstEngine/Debug/Logging/Logger.h>

#include <cstdlib>
#include <format>
#include <iostream>
#include <string_view>

#define OST_ASSERT_ALWAYS( condition, message, ... ) ost::OstEngineAssert( condition, message, __VA_ARGS__)

#if _DEBUG
#define OST_ASSERT( condition, message, ... ) ost::OstEngineAssert(condition, message, __VA_ARGS__)
#else
#define OST_ASSERT( condition, message, ... ) 
#endif


namespace ost
{
    template <typename... TFmt>
    void OstEngineAssert( bool aCmd, std::string_view aMsg, TFmt&&... aFmt )
    {
        if ( !aCmd )
        {
            Logging::Error( aMsg, aFmt... );
            std::cerr << std::vformat( aMsg, std::make_format_args( aFmt... ) ) << std::endl;
            std::abort();
        }
    }
} // namespace ost