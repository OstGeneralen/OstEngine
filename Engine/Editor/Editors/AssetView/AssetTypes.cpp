// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AssetTypes.h"

#include "GUI/IconsFontAwesome6.h"
#include "GUI/OstGui.h"

using namespace ost;

// ------------------------------------------------------------

ost::EditorAssetTypeUtility::EditorAssetTypeUtility(EAssetType assetType)
    : _assetType{assetType}
{
}

ost::EditorAssetTypeUtility::EditorAssetTypeUtility(const std::filesystem::path& path)
    : _assetType{EAssetType::Unknown}
{
    std::filesystem::path ext = path.extension();

    if (ext == ".dds")
    {
        _assetType = EAssetType::Texture;
    }
    else if (ext == ".fbx")
    {
        _assetType = EAssetType::Model;
    }
    else if (ext == ".hlsl" || ext == ".hlsli")
    {
        _assetType = EAssetType::Shader;
    }
    else if (ext == ".json")
    {
        _assetType = EAssetType::Config;
    }
    else if (ext == ".ostmat")
    {
        _assetType = EAssetType::Material;
    }
}

EAssetType ost::EditorAssetTypeUtility::GetAssetType() const
{
    return _assetType;
}

// ------------------------------------------------------------

const char* ost::EditorAssetTypeUtility::GetDragDropTypeID() const
{
    switch (_assetType)
    {
    case EAssetType::Model:
        return "DDID_MODEL";
    case EAssetType::Texture:
        return "DDID_TEXTURE";
    case EAssetType::Material:
        return "DDID_MATERIAL";
    }
    return "";
}

bool ost::EditorAssetTypeUtility::CanDragDrop() const
{
    switch (_assetType)
    {
    case EAssetType::Model:
    case EAssetType::Texture:
    case EAssetType::Material:
        return true;
    }
    return false;
}

// ------------------------------------------------------------

const char* ost::EditorAssetTypeUtility::GetAssetIconFontID() const
{
    switch (_assetType)
    {
    case EAssetType::Model:
        return ICON_FA_CUBE;
    case EAssetType::Texture:
        return ICON_FA_IMAGE;
    case EAssetType::Material:
        return ICON_FA_PAINTBRUSH;
    case EAssetType::Config:
        return ICON_FA_GEAR;
    case EAssetType::Shader:
        return ICON_FA_FILE_CODE;
    case EAssetType::Actor:
        return ICON_FA_PERSON;
    case EAssetType::Audio:
        return ICON_FA_FILE_AUDIO;
    }

    return ICON_FA_FILE;
}

// ------------------------------------------------------------

void ost::EditorAssetTypeUtility::DrawDragDropSource(const char* name, SizeType payload) const
{
    if (CanDragDrop() && OstGui::BeginDragDropSource(ImGuiDragDropFlags_None))
    {
        OstGui::SetDragDropPayload(GetDragDropTypeID(), &payload, sizeof(SizeType), ImGuiCond_Always);

        OstGui::EndDragDropSource();
    }
}

void* ost::EditorAssetTypeUtility::DrawDragDropTarget() const
{
    if(CanDragDrop() && OstGui::BeginDragDropTarget())

    return nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------