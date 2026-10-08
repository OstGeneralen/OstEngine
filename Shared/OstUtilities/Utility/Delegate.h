// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Container/List.h"

// ------------------------------------------------------------

namespace ost
{
    template <typename... TArgs>
    class Delegate
    {
    private:
        struct Binding
        {
            void* pInstance = nullptr;
            void (*stub)(void*, TArgs&&...) = nullptr;

            bool operator==(const Binding& rhs) const
            {
                return pInstance == rhs.pInstance && stub == rhs.stub;
            }
        };

    public:
        template <typename T, void (T::*method)(TArgs&&...)>
        void Bind(void* pInstance)
        {
            Binding binding;
            binding.pInstance = pInstance;
            binding.stub = [](void* pInst, TArgs&&... args) { (static_cast<T*>(pInst)->*method)(std::forward<TArgs>(args)...); };
            _bindings.Add(binding);
        }

        template <typename T, void (T::*method)(TArgs&&...)>
        void Unbind(void* pInstance)
        {
            Binding removeBinding;
            removeBinding.pInstance = pInstance;
            removeBinding.stub = [](void* pInst, TArgs&&... args) { (static_cast<T*>(pInst)->*method)(std::forward<TArgs>(args)...); };

            for (SizeType i = 0; i < _bindings.GetSize(); i++)
            {
                if (_bindings[i] == removeBinding)
                {
                    _bindings.Remove(i);
                    break;
                }
            }
        }

        void Broadcast(TArgs&&... args)
        {
            for (Binding& b : _bindings)
            {
                b.stub(b.pInstance, std::forward<TArgs>(args)...);
            }
        }

    private:
        List<Binding> _bindings;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------