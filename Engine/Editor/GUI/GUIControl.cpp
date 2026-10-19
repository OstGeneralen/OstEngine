// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIControl.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

void GUIControl::SetParent(GUIControl* pParent)
{
    if (_pParent)
    {
        constexpr static SizeType NPOS = static_cast<SizeType>(-1);
        SizeType indexOfThis = NPOS;
        for (SizeType i = 0; i < _pParent->_children.GetSize(); ++i)
        {
            if (_pParent->_children[i] == this)
            {
                indexOfThis = i;
                break;
            }
        }

        if (indexOfThis != NPOS)
        {
            _pParent->_children.Remove(indexOfThis);
        }
    }

    _pParent = pParent;

    if (_pParent)
    {
        _pParent->_children.Add(this);
    }
}

void ost::GUIControl::AddChild(GUIControl* pChild)
{
    if (pChild)
    {
        pChild->SetParent(this);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------