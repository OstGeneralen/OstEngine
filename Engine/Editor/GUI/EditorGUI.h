// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"
#include "GUI/GUIWindow.h"

#include <concepts>
#include <type_traits>

#include <Container/List.h>
#include <Container/Stack.h>
#include <Math/Vector2.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    concept GUIWindowType = std::is_base_of_v<GUIWindow, T>;

    class EditorGUI
    {
        friend class EditorApplication;

    public:
        static EditorGUI& Get();

        template <GUIWindowType T>
        void Open(EGUIWindowOpenPos openPosition = EGUIWindowOpenPos::Center)
        {
            auto window = Ptr::NewUnique<T>();
            if (window->GetWindowType() == EGUIWindowType::Modal)
            {
                _modalStack.Push(std::move(window));
            }
        }

        void Display(const Vector2f& displayArea);

    private:
        EditorGUI();
        ~EditorGUI();

        static EditorGUI* _pInstance;

        Stack<UniquePtr<GUIWindow>> _modalStack;
        List<GUIControl*> _rootControls;

        List<UniquePtr<GUIControl>> _openControls;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------