// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Objects/PipelineStateObject.h"
#include "GraphicsEngine/Objects/Buffer.h"
#include "GraphicsEngine/Objects/Texture.h"

#include <string>

#include <Container/Map.h>
#include <Math/Color.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EMaterialDomain
    {
        None,
        Surface,
    };

    enum class EMaterialShadingModel
    {
        None,
        Lit,
        Unlit,
    };

    struct MaterialDesc
    {
        EMaterialDomain domain;
        EMaterialShadingModel shadingModel;
        std::string materialShaderFilePath;
    };

    class Material
    {
        struct Property;

        friend class MaterialFactory;

    public:
        Material();
        Material(const Material&);
        Material(Material&&) noexcept;
        ~Material();

        Material& operator=(const Material&);
        Material& operator=(Material&&) noexcept;

        void SetProperty(const std::string& propertyName, const Texture& texture);
        void SetProperty(const std::string& propertyName, const Color& c);
        void SetProperty(const std::string& propertyName, const Vector4f& v);
        void SetProperty(const std::string& propertyName, const Vector3f& v);
        void SetProperty(const std::string& propertyName, const Vector2f& v);
        void SetProperty(const std::string& propertyName, Float32 v);

        SizeType GetVariablesByteCount() const;
        const void* GetVariablesData() const;
        const Buffer& GetVariablesBuffer() const;

        SizeType GetTextureCount() const;
        const Texture* GetTextures() const;

        const PipelineStateObject& GetPSO() const;

    private:
        void SetVariableProperty(const std::string& propertyName, const void* pData, SizeType dataSize);

        PipelineStateObject _pso;
        Map<std::string, Property> _propertyMap;

        Buffer _variablesBuffer;

        SizeType _variablesByteCount = 0;
        Uint8 _variablePropertyData[512] = {0};

        SizeType _numTextures = 0;
        const Texture* _pTextureProperties[8] = {nullptr};

    private:
        struct Property
        {
            enum class EType
            {
                Unknown,
                Texture,
                Variable,
            };

            EType type;
            SizeType offset; // If type is a texture, this is the bind slot. If variable, this is offset into the byte array.
            SizeType size;   // Unused for textures, tells byte size of variables.
        };
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------