#pragma once

namespace ost
{
    class CEngine
    {
        friend class COstEngineApp;

    public:
        static CEngine* Instance();

    private:
        CEngine() = default;
        static CEngine* _instancePtr;
    };
} // namespace ost