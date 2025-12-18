#include "OstEngine/Rendering/RenderData/Texture.h"

#include "OstEngine/Debug/Logging/LogInstance.h"
#include "OstEngine/Utility/StringUtility.h"
#include "Src/Rendering/DX/DDSTextureLoader11.h"
#include "Src/Rendering/DX/DXHandling.h"

ost::log::CLogInstance TextureLoadLog{ "TextureLoad" };

// ------------------------------------------------------------

void ost::CTexture::LoadDDS( const std::string& aPath )
{
    const std::wstring wPath = stringUtils::StringToWString( aPath );

    ID3D11ShaderResourceView* resourceView;
    HRESULT result = DirectX::CreateDDSTextureFromFile( dx::Device, wPath.c_str(), nullptr, &resourceView );
    _texResView = resourceView;

    if ( result == S_OK )
    {
        TextureLoadLog.BeginConfirm( "Successfully loaded texture {}", aPath );
    }
    else
    {
        TextureLoadLog.Warning( "Failed to load texture {}", aPath );
        return;
    }

    ID3D11Resource* textureBaseResource = nullptr;
    ID3D11Texture2D* texture = nullptr;
    resourceView->GetResource( &textureBaseResource );
    textureBaseResource->QueryInterface( IID_PPV_ARGS( &texture ) );

    if ( texture != nullptr )
    {
        D3D11_TEXTURE2D_DESC textureDesc = {};
        texture->GetDesc( &textureDesc );
        _dimensions = { static_cast<Uint32>( textureDesc.Width ), static_cast<Uint32>( textureDesc.Height ) };
    }
}

// ------------------------------------------------------------

ost::SUntypedPtr ost::CTexture::GetTextureResource() const
{
    return _texResView;
}

// ------------------------------------------------------------

const ost::Vector2u& ost::CTexture::GetDimensions() const
{
    return _dimensions;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------