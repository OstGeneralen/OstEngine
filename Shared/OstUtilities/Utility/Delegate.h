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

            const void* pMethodID = nullptr;

            bool operator==(const Binding& rhs) const
            {
                return pInstance == rhs.pInstance && pMethodID == rhs.pMethodID;
            }
        };

    public:
        template <typename T, void (T::*method)(TArgs&&...)>
        void Bind(void* pInstance)
        {
            Binding binding;
            binding.pInstance = pInstance;
            binding.stub = [](void* pInst, TArgs&&... args) { (static_cast<T*>(pInst)->*method)(std::forward<TArgs>(args)...); };

            binding.pMethodID = reinterpret_cast<const void*>(&method);

            _bindings.Add(binding);
        }

        template <typename T, void (T::*method)(TArgs&&...)>
        void Unbind(void* pInstance)
        {
            Binding removeBinding;
            removeBinding.pInstance = pInstance;
            removeBinding.stub = [](void* pInst, TArgs&&... args) { (static_cast<T*>(pInst)->*method)(std::forward<TArgs>(args)...); };

            removeBinding.pMethodID = reinterpret_cast<const void*>(&method);

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