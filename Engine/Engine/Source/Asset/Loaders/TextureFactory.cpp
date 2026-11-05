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
        break;
    case DirectX::TEX_DIMENSION_TEXTURE2D:
        desc.dimensionCount = 2;
        break;
    case DirectX::TEX_DIMENSION_TEXTURE3D:
        desc.dimensionCount = 3;
        break;
    }

    // Translate and ensure supported format
    if (metadata.format == DXGI_FORMAT_BC7_TYPELESS)
    {
        metadata.format = DXGI_FORMAT_BC7_UNORM;
    }

    // TODO: Carry on from here!!!
    switch (metadata.format)
    {
    case DXGI_FORMAT_BC7_UNORM:
        into.format = ETextureFormat::DDS_BC7;
        break;
    case DXGI_FORMAT_BC7_UNORM_SRGB:
        into.format = ETextureFormat::DDS_BC7_SRGB;
        break;
    case DXGI_FORMAT_R16G16_UNORM:
        into.format = ETextureFormat::NormalMap;
        break;
    default:
        OST_ASSERT(false, "Must be BC7 rgba or srgb");
    }

    into.mipCount = metadata.mipLevels;
    into.dimensions = Vector2u{static_cast<Uint32>(metadata.width), static_cast<Uint32>(metadata.height)};

    // Now we copy across the various image pixel data into the assigned buffers
    into.images = List<TextureCPUData::ImageData>{scratchImg.GetImageCount()};

    for (SizeType imageIndex = 0; imageIndex < into.images.GetSize(); ++imageIndex)
    {
        auto& dxImage = scratchImg.GetImages()[imageIndex];
        auto& cpuDataImage = into.images[imageIndex];

        cpuDataImage.data = List<Uint8>(static_cast<SizeType>(dxImage.slicePitch));
        MemCopy(cpuDataImage.data.GetData(), dxImage.pixels, cpuDataImage.data.GetSize());

        cpuDataImage.rowPitch = dxImage.rowPitch;
        cpuDataImage.slicePitch = dxImage.slicePitch;
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------