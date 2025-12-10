#pragma once

namespace ost
{
    class IGame
    {
    public:
        virtual void Load() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
    };

} // namespace ost