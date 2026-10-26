// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Editors/AssetView/AssetTypes.h"

#include <OstTypes.h>
#include <filesystem>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;

    // Represents a file within the hierarchy
    struct AssetFileEntry
    {
        EAssetType assetFileType;
        std::filesystem::path canonicalPath;
        std::string name;
    };

    // Represents a directory in the hierarchy from the root of the selected asset path
    struct AssetDirectoryEntry
    {
        std::filesystem::path path;
        std::filesystem::path parentPath;
        List<AssetDirectoryEntry> childEntries;
        List<AssetFileEntry> fileEntries;
    };

    class EditorAssetContext
    {
    public:
        EditorAssetContext(EditorContext& parentCtx);

        void SetRootAssetsDirectory(const std::filesystem::path& path);
        AssetDirectoryEntry& GetRootAssetDirectory();

        void SetCurrentAssetDirectory(AssetDirectoryEntry& entry);
        AssetDirectoryEntry& GetCurrentAssetDirectory();

        bool IsCurrentDirectoryEntry( const AssetDirectoryEntry& entry ) const;

        const List<AssetFileEntry>& GetCurrentDirectoryEntries() const;

    private:
        void BuildEntriesRecursive(AssetDirectoryEntry& forEntry);

        EditorContext& _parentContext;

        AssetDirectoryEntry _rootDirectoryEntry;
        AssetDirectoryEntry* _pCurrentDirectoryEntry;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------