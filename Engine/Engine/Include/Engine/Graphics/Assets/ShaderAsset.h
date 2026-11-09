// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/Asset.h"

#include <OstTypes.h>

#include <Container/List.h>
#include <GraphicsEngine/GraphicsTypes.h>

// ------------------------------------------------------------

namespace ost
{
    class ShaderAsset : public Asset
    {
    public:
        ShaderAsset() = default;
        ShaderAsset(EPipelineStage pipelineStage, const List<Uint8> bytecode)
            : _bytecode{bytecode}
            , _bindStage{pipelineStage}
        {
        }
        ShaderAsset(const ShaderAsset&) = delete;
        ShaderAsset(ShaderAsset&&) noexcept = default;

        ShaderAsset& operator=(const ShaderAsset&) = delete;
        ShaderAsset& operator=(ShaderAsset&&) noexcept = default;

        const void* BytecodePtr() const
        {
            return _bytecode.GetData();
        }
        SizeType BytecodeSize() const
        {
            return _bytecode.GetSize();
        }
        const List<Uint8>& Bytecode() const
        {
            return _bytecode;
        }

        EPipelineStage BindStage() const
        {
            return _bindStage;
        }

        // BEGIN Asset
        TypeID AssetTypeID() const override
        {
            return TypeID::Get<Shader>();
        }
        // END Asset

    private:
        List<Uint8> _bytecode;
        EPipelineStage _bindStage;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------