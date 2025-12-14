#include "OSRFileReader.h"

#include <exception>
#include <format>
#include <fstream>
#include <string_view>

#include <d3d11.h>
#include <dxgi.h>

#include <json.hpp>

using namespace nlohmann;

namespace osrFormat
{
    class OsrException : public std::exception
    {
    public:

        OsrException( const char* msg )
            : std::exception( msg )
        {
        }

        template <typename... TArgs>
        OsrException( const char* msg, const char* innerMsg, TArgs&&... aFmt )
            : std::exception( std::vformat( std::string_view( msg ), std::make_format_args( aFmt... ) ).c_str() )
            , InnerMessage( innerMsg )
        {
        }

        OsrException( const OsrException& ) = default;

        std::string InnerMessage;
    };

    DXGI_FORMAT ConvertFormat( const std::string& aDataTypeStr, Int32 aDataSize )
    {
        if ( aDataTypeStr == "Float32" )
        {
            switch ( aDataSize )
            {
            case 1:
                return DXGI_FORMAT_R32_FLOAT;
            case 2:
                return DXGI_FORMAT_R32G32_FLOAT;
            case 3:
                return DXGI_FORMAT_R32G32B32_FLOAT;
            case 4:
                return DXGI_FORMAT_R32G32B32A32_FLOAT;
            default:
                throw OsrException( "no available value for \"dataSize\": {} of \"dataType\": \"Float32\"", "",
                                    aDataSize );
            }
        }
        else if ( aDataTypeStr == "Uint32" )
        {
            switch ( aDataSize )
            {
            case 1:
                return DXGI_FORMAT_R32_UINT;
            case 2:
                return DXGI_FORMAT_R32G32_UINT;
            case 3:
                return DXGI_FORMAT_R32G32B32_UINT;
            case 4:
                return DXGI_FORMAT_R32G32B32A32_UINT;
            default:
                throw OsrException( "no available value for \"dataSize\": {} of \"dataType\": \"Uint32\"", "",
                                    aDataSize );
            }
        }
        else
        {
            throw OsrException( "incorrect/unsupported \"dataType\" for layout element ({})",
                                "", aDataTypeStr, aDataSize );
        }
    }

    json TryReadRoot( std::ifstream& fromStream )
    {
        try
        {
            return json::parse( fromStream );
        }
        catch ( const std::exception& e )
        {
            fromStream.close();
            throw OsrException( "failed to read root of osr file", e.what() );
        }
    }

    std::string TryReadPixelMain( json& fromRoot )
    {
        try
        {
            return fromRoot["ps"]["main"];
        }
        catch ( const std::exception& e )
        {
            throw OsrException( "unable to read \"main\" from \"ps\"", e.what() );
        }
    }

    std::string TryReadVertexMain( json& fromRoot )
    {
        try
        {
            return fromRoot["vs"]["main"];
        }
        catch ( const std::exception& e )
        {
            throw OsrException( "unable to read \"main\" from \"vs\"", e.what() );
        }
    }

    Int32 TryReadNumLayoutElements( json& fromRoot )
    {
        try
        {
            return fromRoot["layoutElements"].size();
        }
        catch ( const std::exception& e )
        {
            throw OsrException( "failed to read size from \"layoutElements\"[]", e.what() );
        }
    }

    ost::SDXInputElementDesc TryReadElementDesc( json& fromRoot, Int32 atIndex )
    {
        ost::SDXInputElementDesc desc;
        json layoutElementRoot;

        try
        {
            layoutElementRoot = fromRoot["layoutElements"][atIndex];
        }
        catch ( const std::exception& e )
        {
            throw OsrException( "failed to read root of layout element at index '{}'", e.what(), atIndex );
        }

        try
        {
            desc.SemanticName = layoutElementRoot["semanticName"];
            desc.D3DDesc.SemanticIndex = layoutElementRoot["semanticIndex"];
        }
        catch ( const std::exception& e )
        {
            throw OsrException( "failed to read semantic data of element at index '{}'", e.what(), atIndex );
        }

        std::string dataTypeName = std::string( "" );
        Int32 dataSize = -1;
        try
        {
            dataTypeName = layoutElementRoot["format"]["dataType"];
            dataSize = layoutElementRoot["format"]["dataSize"];
        }
        catch ( const std::exception& e )
        {
            if (dataTypeName.size() == 0)
            {
                throw OsrException( "failed to read \"dataType\" of \"format\" for layout element at index '{}'", e.what(), atIndex);
            }
            else if (dataSize == -1)
            {
                throw OsrException( "failed to read \"dataSize\" of \"format\" for layout element at index '{}'",
                                    e.what(), desc.SemanticName );
            }
        }

        desc.ByteSize = 4u * dataSize;
        desc.D3DDesc.Format = ConvertFormat( dataTypeName, dataSize );

        if (static_cast<Uint32>(desc.D3DDesc.Format) == 0)
        {
            throw OsrException( "failed to convert format from {}x{}", "", dataTypeName, dataSize );
        }
        return desc;
    }


} // namespace osrFormat

bool ost::COSRFileReader::TryReadFromFile( const std::string& aPath, SDXRenderStateDescriptor& outInto )
{
    // Read the json content
    try
    {
        // Open, read and parse the .osr file
        std::ifstream readStream{ aPath };
        json root = osrFormat::TryReadRoot( readStream );
        readStream.close();

        outInto.PixelMain = osrFormat::TryReadPixelMain( root );
        outInto.VertexMain = osrFormat::TryReadVertexMain( root );

        outInto.NumElements = osrFormat::TryReadNumLayoutElements( root );

        for ( Int32 i = 0; i < outInto.NumElements; ++i )
        {
            SDXInputElementDesc& target = outInto.ElementDescs[i];
            target = osrFormat::TryReadElementDesc( root, i );
        }
    }
    catch (const osrFormat::OsrException& e)
    {
        if (e.InnerMessage.length() == 0)
        {
            Logging::Error( "Osr Read Error for {}\n\t> {}", aPath, e.what());
        }
        else
        {
            Logging::Error( "Osr Read Error for {}\n\t> {}\n\t> {}", aPath, e.what(), e.InnerMessage );
        }

        return false;
    }

    Logging::Confirm( "Successfully parsed .osr file '{}'", aPath );
    return true;
}
