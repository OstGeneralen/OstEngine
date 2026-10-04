// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <iostream>
#include <string_view>

// ------------------------------------------------------------

#define OST_ASSERT_ALWAYS(condition, message) ost::internal::utility::AssertionHandler(condition, #condition, message)

#if _DEBUG
#define OST_ASSERT(condition, message) ost::internal::utility::AssertionHandler(condition, #condition, message)
#else
#define OST_ASSERT(condition, message)
#endif

// ------------------------------------------------------------

namespace ost::internal::utility
{
    inline void AssertionHandler(bool cnd, std::string_view cndMsg, std::string_view msg)
    {
        // If the condition is passed, we don't actually debugbreak right
        if (cnd)
            return;

#if defined(_MSC_VER)
        std::cerr << "ASSERTION FAILED " << cndMsg << " " << msg << std::endl;
        __debugbreak();
#else
// Todo: Implement other compilers here should we want to a target them
#endif
    }
} // namespace ost::internal::utility

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------