// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "System/EditorCommand.h"
#include "System/IEditorCommandQueue.h"

#include <string>

#include <Container/List.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

// ------------------------------------------------------------

namespace ost
{

    typedef void (*OnClickFunc)(EditorContext& context);

    enum class EMainMenuHeader
    {
        File,
        Project,
        Options,
        View,
        About,
    };

    struct GUIMainMenuItem
    {
        std::string name;
        OnClickFunc onClick;
    };

    struct GUIMainMenuCategory
    {
        EMainMenuHeader header;
        List<GUIMainMenuItem> items;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------