// Kasper "OstGeneralen" Esbjornsson - 2026
#include "TextureFactory.h"

#include "Engine/Asset/Texture.h"

#include <DirectXTex.h>

#include <GraphicsEngine/Resources/Descriptors/TextureDesc.h>
#include <GraphicsEngine/Resources/IGraphicsResourceManager.h>
#include <Utility/File.h>

using namespace ost;

// ------------------------------------------------------------

TextureFactory::TextureFactory(IGraphicsResourceManager& gfxResourceManager)
    : _gfxResourceManager{gfxResourceManager}
{
}

// ------------------------------------------------------------

TypeID ost::TextureFactory::AssetTypeID() const
{
    return TypeID::Get<Texture>();
}

// ------------------------------------------------------------

Asset* ConstructDefault()
{
    return new Texture();
}

void ost::TextureFactory::Load(const std::filesystem::path& path, Asset* pInto) const
{
    DirectX::TexMetadata metadata;
    DirectX::ScratchImage scratchImg;

    TextureDesc desc;

    { // Load the file content into blob and then read dds from it
        List<Uint8> ddsFileData = FileUtility::ReadFileToByteList(path.string());
        DirectX::LoadFromDDSMemory(ddsFileData.GetData(), ddsFileData.GetSize(), DirectX::DDS_FLAGS_NONE, &metadata, scratchImg);
    }

    switch (metadata.dimension)
    {
    case DirectX::TEX_DIMENSION_TEXTURE1D:
        desc.dimensionCount = 1;
        desc.dimensions = Vector3u(metadata.width, 0, 0);
        break;
    case DirectX::TEX_DIMENSION_TEXTURE2D:
        desc.dimensionCount = 2;
        desc.dimensions = Vector3u(metadata.width, metadata.height, 0);
        break;
    case DirectX::TEX_DIMENSION_TEXTURE3D:
        desc.dimensionCount = 3;
        desc.dimensions = Vector3u(metadata.width, metadata.height, metadata.depth);
        break;
    }

    // Translate and ensure supported format
    if (metadata.format == DXGI_FORMAT_BC7_TYPELESS)
    {
        metadata.format = DXGI_FORMAT_BC7_UNORM;
    }

    switch (metadata.format)
    {
    case DXGI_FORMAT_BC7_UNORM:
        desc.format = ETextureFormat::DDS_BC7;
        break;
    case DXGI_FORMAT_BC7_UNORM_SRGB:
        desc.format = ETextureFormat::DDS_BC7_SRGB;
        break;
    case DXGI_FORMAT_R16G16_UNORM:
        desc.format = ETextureFormat::NormalMap;
        break;
    default:
        OST_ASSERT(false, "Must be BC7 rgba or srgb");
    }

    desc.mipCount = metadata.mipLevels;
    desc.images = List<TextureImageDesc>(scratchImg.GetImageCount());

    // Now we copy across the various image pixel data into the assigned buffers
    for (SizeType imageIndex = 0; imageIndex < desc.images.GetSize(); ++imageIndex)
    {
        auto& dxImage = scratchImg.GetImages()[imageIndex];
        auto& descImage = desc.images[imageIndex];

        descImage.data = List<Uint8>(static_cast<SizeType>(dxImage.slicePitch));
        MemCopy(descImage.data.GetData(), dxImage.pixels, descImage.data.GetSize());

        descImage.rowPitch = dxImage.rowPitch;
        descImage.slicePitch = dxImage.slicePitch;
    }

    // Finally, build the actual gfx resource
    static_cast<Texture&>(*pInto) = std::move(Texture(_gfxResourceManager.CreateTexture(desc)));
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------