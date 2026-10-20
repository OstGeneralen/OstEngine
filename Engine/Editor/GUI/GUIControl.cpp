// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIControl.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

ost::GUIControl::GUIControl(const std::string& uniqueID)
    : _uidString{uniqueID}
    , _pChildren{}
    , _pParent{nullptr}
{
}

GUIControl::~GUIControl()
{
    for (auto pChild : _pChildren)
    {
        delete pChild;
    }
    _pChildren.Clear();
}

// ------------------------------------------------------------

bool ost::GUIControl::IsRoot() const
{
    return _pParent == nullptr;
}

// ------------------------------------------------------------

void ost::GUIControl::MoveToRoot()
{
    if (_pParent != nullptr)
    {
        ost::GUIControl* pRoot = _pParent;
        while (pRoot->_pParent != nullptr)
        {
            pRoot = pRoot->_pParent;
        }

        SetParent(*pRoot);
    }
}

void ost::GUIControl::SetParent(GUIControl& parent)
{
    if (_pParent == &parent)
    {
        // Nothing to do :)
        return;
    }

    if (_pParent != nullptr)
    {
        for (SizeType i = 0; i < _pParent->_pChildren.GetSize(); ++i)
        {
            if (this == _pParent->_pChildren[i])
            {
                _pParent->_pChildren.Remove(i);
                break;
            }
        }
    }

    _pParent = &parent;
    parent._pChildren.Add(this);
}

void ost::GUIControl::AddChild(GUIControl& child)
{
    child.SetParent(*this);
}

// ------------------------------------------------------------

GUIControl* ost::GUIControl::GetParent()
{
    return _pParent;
}

const GUIControl* ost::GUIControl::GetParent() const
{
    return _pParent;
}

List<GUIControl*>& ost::GUIControl::GetChildren()
{
    return _pChildren;
}

const List<GUIControl*>& ost::GUIControl::GetChildren() const
{
    return _pChildren;
}

// ------------------------------------------------------------

const std::string& ost::GUIControl::GetUIDString() const
{
    return _uidString;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------