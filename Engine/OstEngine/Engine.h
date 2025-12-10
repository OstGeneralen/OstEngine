#pragma once

namespace ost
{
    class CEngine
    {
        friend struct EngineLifetimeHandler;

    public:
        static CEngine* Instance();

    private:
        CEngine() = default;
        static CEngine* _instancePtr;
    };
    
    struct EngineLifetimeHandler
    {
        static void CreateEngine() 
        { 
            if (CEngine::_instancePtr == nullptr)
            {
                CEngine::_instancePtr = new CEngine(); 
            }
        }
        static void ReleaseEngine()
        {
            delete CEngine::_instancePtr;
            CEngine::_instancePtr = nullptr;
        }
    };
} // namespace ost