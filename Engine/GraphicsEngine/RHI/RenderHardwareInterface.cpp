// Kasper "OstGeneralen" Esbjornsson - 2026
#include "RenderHardwareInterface.h"

#include "RHI/RHIInternal.h"

#include <Memory/Memory.h>

using namespace ost;

// ------------------------------------------------------------

RenderHardwareInterface::RenderHardwareInterface() = default;
RenderHardwareInterface::~RenderHardwareInterface()
{
    _swapChain.Reset();
    _immediateContext.Reset();
    _device.Reset();
}

// ------------------------------------------------------------

bool RenderHardwareInterface::Initialize(const Vector2u& renderSize, void* winHnd, Texture& outBackbuffer)
{
    HWND hwnd = static_cast<HWND>(winHnd);

    // 1. Create the factory and find the most appropriate device (based on VRAM)
    ComPtr<IDXGIFactory> factory;
    CreateDXGIFactory(IID_PPV_ARGS(&factory));

    ComPtr<IDXGIAdapter> selectedAdapter;
    {
        SizeType bestVram = 0;
        ComPtr<IDXGIAdapter> currentEvalAdapter;
        SizeType currentAdapterIndex = 0;

        while (factory->EnumAdapters(currentAdapterIndex, &currentEvalAdapter) != DXGI_ERROR_NOT_FOUND)
        {
            DXGI_ADAPTER_DESC adapterDesc = {};
            currentEvalAdapter->GetDesc(&adapterDesc);

            if (adapterDesc.DedicatedVideoMemory > bestVram)
            {
                bestVram = adapterDesc.DedicatedVideoMemory;
                selectedAdapter = currentEvalAdapter;
            }
            currentAdapterIndex++;
        }
    }

    // 2. Create the device + immediate context
    if (FAILED(D3D11CreateDevice(selectedAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, 0, D3D11_SDK_VERSION, &_device, NULL,
                                 &_immediateContext)))
    {
        return false;
    }

    // 3. Create the swapchain
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.Windowed = true;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.Height = renderSize.Y;
    swapChainDesc.BufferDesc.Width = renderSize.X;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT;

    if (FAILED(factory->CreateSwapChain(_device.Get(), &swapChainDesc, &_swapChain)))
    {
        return false;
    }

    // 4. Construct the render target output of the backbuffer
    ComPtr<RHITexture2D> backbufferTexture;
    _swapChain->GetBuffer(0, IID_PPV_ARGS(&backbufferTexture));

    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    if (FAILED(_device->CreateRenderTargetView(backbufferTexture.Get(), &rtvDesc, &outBackbuffer._rtv)))
    {
        return false;
    }

    D3D11_VIEWPORT viewport = {};
    viewport.MaxDepth = 1.0f;
    viewport.MinDepth = 0.0f;
    viewport.Width = renderSize.X;
    viewport.Height = renderSize.Y;
    _immediateContext->RSSetViewports(1, &viewport);

    return true;
}

void RenderHardwareInterface::ResizeBackbuffer(const Vector2u& newSize, Texture& inOutBackbuffer)
{
    inOutBackbuffer._rtv.Reset();

    _swapChain->ResizeBuffers(2, newSize.X, newSize.Y, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING);

    ComPtr<RHITexture2D> backbufferTexture;
    _swapChain->GetBuffer(0, IID_PPV_ARGS(&backbufferTexture));

    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    _device->CreateRenderTargetView(backbufferTexture.Get(), &rtvDesc, &inOutBackbuffer._rtv);

    D3D11_VIEWPORT viewport = {};
    viewport.MaxDepth = 1.0f;
    viewport.MinDepth = 0.0f;
    viewport.Width = newSize.X;
    viewport.Height = newSize.Y;
    _immediateContext->RSSetViewports(1, &viewport);
}

// ------------------------------------------------------------

bool RenderHardwareInterface::CreateTexture(const TextureCPUData& desc, Texture& outTexture) const
{
    D3D11_TEXTURE2D_DESC textureDesc = {};
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    textureDesc.Format = translate::TextureFormat(desc.format);
    textureDesc.Height = desc.dimensions.Y;
    textureDesc.Width = desc.dimensions.X;
    textureDesc.MipLevels = desc.mipCount;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Count = 0;
    textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
    textureDesc.ArraySize = 1;

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Texture2D.MipLevels = desc.mipCount;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

    List<D3D11_SUBRESOURCE_DATA> imgData{desc.images.GetSize()};
    for (SizeType i = 0; i < imgData.GetSize(); ++i)
    {
        imgData[i].pSysMem = desc.images[i].data.GetData();
        imgData[i].SysMemPitch = desc.images[i].rowPitch;
        imgData[i].SysMemSlicePitch = desc.images[i].slicePitch;
    }

    ComPtr<RHITexture2D> textureResource;
    if (FAILED(_device->CreateTexture2D(&textureDesc, imgData.GetData(), &textureResource)))
    {
        return false;
    }

    if (FAILED(_device->CreateShaderResourceView(textureResource.Get(), &srvDesc, &outTexture._srv)))
    {
        return false;
    }

    return true;
}

bool RenderHardwareInterface::CreateRenderTargetTexture(const Vector2u& dimensions, EDataFormat format, bool allowAsResource, Texture& outTexture) const
{
    // 1. Fill out descriptions
    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.ArraySize = 1;
    texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | (allowAsResource ? D3D11_BIND_SHADER_RESOURCE : 0);
    texDesc.Format = translate::DataFormat(format);
    texDesc.Width = dimensions.X;
    texDesc.Height = dimensions.Y;
    texDesc.MipLevels = 1;
    texDesc.SampleDesc.Count = 1;
    texDesc.Usage = D3D11_USAGE_DEFAULT;

    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = translate::DataFormat(format);
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = translate::DataFormat(format);
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    // 2. Create the resources
    ComPtr<RHITexture2D> textureResource;
    if (FAILED(_device->CreateTexture2D(&texDesc, NULL, &textureResource)))
    {
        return false;
    }

    if (FAILED(_device->CreateRenderTargetView(textureResource.Get(), &rtvDesc, &outTexture._rtv)))
    {
        return false;
    }

    if (allowAsResource && FAILED(_device->CreateShaderResourceView(textureResource.Get(), &srvDesc, &outTexture._srv)))
    {
        return false;
    }

    return true;
}

bool RenderHardwareInterface::CreateDepthStencilTexture(const Vector2u& dimensions, bool allowAsResource, Texture& outTexture) const
{
    // 1. Fill out descriptions
    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.ArraySize = 1;
    texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | (allowAsResource ? D3D11_BIND_SHADER_RESOURCE : 0);
    texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    texDesc.Width = dimensions.X;
    texDesc.Height = dimensions.Y;
    texDesc.MipLevels = 1;
    texDesc.SampleDesc.Count = 1;
    texDesc.Usage = D3D11_USAGE_DEFAULT;

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    // 2. Create the resources
    ComPtr<RHITexture2D> textureResource;
    if (FAILED(_device->CreateTexture2D(&texDesc, NULL, &textureResource)))
    {
        return false;
    }

    if (FAILED(_device->CreateDepthStencilView(textureResource.Get(), &dsvDesc, &outTexture._dsv)))
    {
        return false;
    }

    if (allowAsResource && FAILED(_device->CreateShaderResourceView(textureResource.Get(), &srvDesc, &outTexture._srv)))
    {
        return false;
    }

    return true;
}

void RenderHardwareInterface::ClearRenderTarget(const Texture& renderTarget, const Color& clearColor) const
{
    _immediateContext->ClearRenderTargetView(renderTarget._rtv.Get(), clearColor.FltArray);
}

void RenderHardwareInterface::ClearDepthStencil(const Texture& depthStencil, Float32 depth, Uint8 stencil) const
{
    _immediateContext->ClearDepthStencilView(depthStencil._dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
}

bool RenderHardwareInterface::CreateVertexBuffer(SizeType vertexSize, SizeType numVerts, const void* pData, Buffer& outBuffer) const
{
    D3D11_BUFFER_DESC desc = {};
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.ByteWidth = vertexSize * numVerts;
    desc.CPUAccessFlags = 0;
    desc.StructureByteStride = vertexSize;
    desc.Usage = D3D11_USAGE_IMMUTABLE;

    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem = pData;

    if (FAILED(_device->CreateBuffer(&desc, &initialData, &outBuffer._buffer)))
    {
        return false;
    }

    outBuffer._allocSize = vertexSize * numVerts;

    return true;
}

bool RenderHardwareInterface::CreateIndexBuffer(SizeType numIndices, const Uint32* pData, Buffer& outBuffer) const
{
    D3D11_BUFFER_DESC desc = {};
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.ByteWidth = sizeof(Uint32) * numIndices;
    desc.CPUAccessFlags = 0;
    desc.StructureByteStride = sizeof(Uint32);
    desc.Usage = D3D11_USAGE_IMMUTABLE;

    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem = pData;

    if (FAILED(_device->CreateBuffer(&desc, &initialData, &outBuffer._buffer)))
    {
        return false;
    }
    outBuffer._allocSize = sizeof(Uint32) * numIndices;

    return true;
}

bool RenderHardwareInterface::CreateBuffer(SizeType numBytes, Buffer& outBuffer, const void* pInitialData) const
{
    D3D11_BUFFER_DESC desc = {};
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.ByteWidth = numBytes;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.StructureByteStride = numBytes;
    desc.Usage = D3D11_USAGE_DYNAMIC;

    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem = pInitialData;

    D3D11_SUBRESOURCE_DATA* pAssignedInitData = (pInitialData ? &initialData : nullptr);

    outBuffer._allocSize = numBytes;

    if (FAILED(_device->CreateBuffer(&desc, pAssignedInitData, &outBuffer._buffer)))
    {
        return false;
    }
    return true;
}

bool RenderHardwareInterface::UpdateBuffer(const Buffer& targetBuffer, const void* pData, SizeType dataSize) const
{
    D3D11_MAPPED_SUBRESOURCE mapped = {};

    _immediateContext->Map(targetBuffer._buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
    MemCopy(mapped.pData, pData, dataSize);
    _immediateContext->Unmap(targetBuffer._buffer.Get(), 0);

    return true;
}

bool RenderHardwareInterface::CreatePSO(const PipelineStateObjectDesc& desc, PipelineStateObject& outPSO) const
{
    outPSO._primitiveTopology = desc.primitiveTopology;

    if (FAILED(_device->CreateVertexShader(desc.vertexShader.pBytecode, desc.vertexShader.bytecodeSize, NULL, &outPSO._vertexShader)))
    {
        return false;
    }
    if (FAILED(_device->CreatePixelShader(desc.pixelShader.pBytecode, desc.pixelShader.bytecodeSize, NULL, &outPSO._pixelShader)))
    {
        return false;
    }

    List<D3D11_INPUT_ELEMENT_DESC> inputElements{desc.vertexLayout.GetSize()};
    for (SizeType i = 0; i < inputElements.GetSize(); ++i)
    {
        D3D11_INPUT_ELEMENT_DESC& inputElem = inputElements[i];

        inputElem.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        inputElem.Format = translate::DataSize(desc.vertexLayout[i].dataSize);
        inputElem.InputSlot = 0;
        inputElem.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        inputElem.InstanceDataStepRate = 0;
        inputElem.SemanticIndex = 0;
        inputElem.SemanticName = desc.vertexLayout[i].semanticName.c_str();
    }

    if (FAILED(_device->CreateInputLayout(inputElements.GetData(), inputElements.GetSize(), desc.vertexShader.pBytecode, desc.vertexShader.bytecodeSize,
                                          &outPSO._vertexLayout)))
    {
        return false;
    }

    return true;
}

// ------------------------------------------------------------

void RenderHardwareInterface::SetTexture(const Texture& texture, Uint32 slot, EPipelineStage_ stageFlag) const
{
    if (stageFlag & EPipelineStage_VS)
    {
        _immediateContext->VSSetShaderResources(slot, 1, texture._srv.GetAddressOf());
    }
    if (stageFlag & EPipelineStage_PS)
    {
        _immediateContext->PSSetShaderResources(slot, 1, texture._srv.GetAddressOf());
    }
}

void RenderHardwareInterface::SetBuffer(const Buffer& buffer, Uint32 slot, EPipelineStage_ stageFlag) const
{
    if (stageFlag & EPipelineStage_VS)
    {
        _immediateContext->VSSetConstantBuffers(slot, 1, buffer._buffer.GetAddressOf());
    }
    if (stageFlag & EPipelineStage_PS)
    {
        _immediateContext->PSSetConstantBuffers(slot, 1, buffer._buffer.GetAddressOf());
    }
}

void RenderHardwareInterface::SetPSO(const PipelineStateObject& pso) const
{
    _immediateContext->VSSetShader(pso._vertexShader.Get(), NULL, 0);
    _immediateContext->PSSetShader(pso._pixelShader.Get(), NULL, 0);
    _immediateContext->IASetInputLayout(pso._vertexLayout.Get());
    _immediateContext->IASetPrimitiveTopology(translate::PrimitiveTopology(pso._primitiveTopology));
}

void RenderHardwareInterface::SetRenderTarget(const Texture& renderTarget, const Texture* pDepthTarget) const
{
    _immediateContext->OMSetRenderTargets(1, renderTarget._rtv.GetAddressOf(), (pDepthTarget ? pDepthTarget->_dsv.Get() : nullptr));
}

void RenderHardwareInterface::SetRenderTargets(const Texture* pRenderTargets, SizeType numTargets, const Texture* pDepthTarget) const
{
    ID3D11RenderTargetView* rtvs[8]{nullptr};

    for (SizeType i = 0; i < numTargets; ++i)
    {
        rtvs[i] = pRenderTargets[i]._rtv.Get();
    }

    _immediateContext->OMSetRenderTargets(numTargets, rtvs, (pDepthTarget ? pDepthTarget->_dsv.Get() : nullptr));
}

void RenderHardwareInterface::Draw(const Mesh& mesh, bool setBuffers) const
{
    if (setBuffers)
    {
        UINT strides[] = {sizeof(SurfaceVertex)};
        UINT offsets[] = {mesh.vertexOffset};

        _immediateContext->IASetVertexBuffers(0, 1, mesh.vertexBuffer._buffer.GetAddressOf(), strides, offsets);
        _immediateContext->IASetIndexBuffer(mesh.indexBuffer._buffer.Get(), DXGI_FORMAT_R32_UINT, mesh.indexOffset);
    }

    _immediateContext->DrawIndexed(mesh.indexCount, mesh.indexOffset, mesh.vertexOffset);
}

void RenderHardwareInterface::Present() const
{
    _swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------