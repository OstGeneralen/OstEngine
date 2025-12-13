#pragma once
#include <string>
#include <d3d11.h>


namespace ost
{
    struct SDXRenderStateDescriptor;

    enum class EDxShaderType
    {
        Invalid,
        Vertex,
        Pixel,
    };

	class CDXShaderCompiler
	{
    public:
        CDXShaderCompiler( const std::string& aShaderFilePath);
        ~CDXShaderCompiler();

        void CompileShader( const std::string& aEntry, EDxShaderType aType, ID3D11Device* aDevice );

        bool HasErrors() const;
        const std::string& GetErrorString() const;

        ID3DBlob* GetBlob();

        ID3D11VertexShader* GetVertexShader(bool aConsume = true);
        ID3D11PixelShader* GetPixelShader(bool aConsume = true);
	private:
        std::wstring _shaderFilePath;
        std::string _errorMessage;
        ID3D11VertexShader* _vertexShader;
        ID3D11PixelShader* _pixelShader;
        EDxShaderType _compiledType;
        ID3DBlob* _shaderBlob;

        bool _hasErrors;
	};
}