// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <filesystem>

// ------------------------------------------------------------

namespace ost
{
    enum class EAssetType
    {
        Unknown,
        Texture,
        Shader,
        Audio,
        Material,
        Actor,
        Model,
        Config,
    };

    class EditorAssetTypeUtility
    {
    public:
        EditorAssetTypeUtility(EAssetType assetType);
        EditorAssetTypeUtility(const std::filesystem::path& path);

        EAssetType GetAssetType() const;
        const char* GetDragDropTypeID() const;
        bool CanDragDrop() const;
        const char* GetAssetIconFontID() const;

        void DrawDragDropSource(const char* name, SizeType payload) const;
        void* DrawDragDropTarget() const;

    private:
        EAssetType _assetType;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------