// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIControl.h"

#include <imgui.h>

#include <Math/Math.h>

using namespace ost;

// ------------------------------------------------------------

ost::GUIControl::GUIControl(const std::string& uniqueID)
    : _uidString{uniqueID}
    , _pChildren{}
    , _pParent{nullptr}
    , _guiFlags{0}
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

GUIControl& ost::GUIControl::SetResizeFlag(EGUIResize resizeFlag)
{
    if (resizeFlag & EGUIResize_X)
    {
        _guiFlags |= ImGuiChildFlags_ResizeX;
    }
    if (resizeFlag & EGUIResize_Y)
    {
        _guiFlags |= ImGuiChildFlags_ResizeY;
    }
    return *this;
}

GUIControl& ost::GUIControl::SetBordered(bool bordered)
{
    if (bordered)
    {
        _guiFlags |= ImGuiChildFlags_Borders;
    }
    return *this;
}

GUIControl& ost::GUIControl::SetInitialSize(const Vector2f& size)
{
    _size = size;
    return *this;
}

GUIControl& ost::GUIControl::SetPivot(const Vector2f& pivot)
{
    _pivot = pivot;
    return *this;
}

bool GUIControl::AllowResizeX() const
{
    return _guiFlags & ImGuiChildFlags_ResizeX;
}

bool GUIControl::AllowResizeY() const
{
    return _guiFlags & ImGuiChildFlags_ResizeY;
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

void ost::GUIControl::BeginGUI(Int32 windowFlags)
{
    ImGui::BeginChild(_uidString.c_str(), _size, _guiFlags, windowFlags);
}

void ost::GUIControl::EndGUI()
{
    ImGui::EndChild();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------