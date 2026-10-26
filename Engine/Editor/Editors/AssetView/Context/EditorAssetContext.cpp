// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorAssetContext.h"

#include "EditorContext.h"

using namespace ost;

// ------------------------------------------------------------

ost::EditorAssetContext::EditorAssetContext(EditorContext& parentCtx)
    : _parentContext{parentCtx}
{
    SetRootAssetsDirectory(std::filesystem::current_path());
}

void ost::EditorAssetContext::SetRootAssetsDirectory(const std::filesystem::path& path)
{
    _rootDirectoryEntry = AssetDirectoryEntry{};
    _rootDirectoryEntry.path = std::filesystem::weakly_canonical(path);
    _rootDirectoryEntry.parentPath = "";
    BuildEntriesRecursive(_rootDirectoryEntry);

    _pCurrentDirectoryEntry = &_rootDirectoryEntry;
}

AssetDirectoryEntry& ost::EditorAssetContext::GetRootAssetDirectory()
{
    return _rootDirectoryEntry;
}

// ------------------------------------------------------------

void ost::EditorAssetContext::SetCurrentAssetDirectory(AssetDirectoryEntry& entry)
{
    _pCurrentDirectoryEntry = &entry;
}

AssetDirectoryEntry& ost::EditorAssetContext::GetCurrentAssetDirectory()
{
    return *_pCurrentDirectoryEntry;
}

bool ost::EditorAssetContext::IsCurrentDirectoryEntry(const AssetDirectoryEntry& entry) const
{
    return &entry == _pCurrentDirectoryEntry;
}

// ------------------------------------------------------------

const List<AssetFileEntry>& ost::EditorAssetContext::GetCurrentDirectoryEntries() const
{
    return _pCurrentDirectoryEntry->fileEntries;
}

// ------------------------------------------------------------

void ost::EditorAssetContext::BuildEntriesRecursive(AssetDirectoryEntry& forEntry)
{
    for (auto it : std::filesystem::directory_iterator(forEntry.path))
    {
        if (it.is_directory())
        {
            AssetDirectoryEntry childEntry;
            childEntry.parentPath = forEntry.path;
            childEntry.path = std::filesystem::weakly_canonical(it.path());
            BuildEntriesRecursive(childEntry);
            forEntry.childEntries.Add(childEntry);
        }
        else if (it.is_regular_file())
        {
            EditorAssetTypeUtility typeUtility(it.path());

            AssetFileEntry fileEntry;
            fileEntry.canonicalPath = std::filesystem::weakly_canonical(it.path());
            fileEntry.assetFileType = typeUtility.GetAssetType();
            fileEntry.name = fileEntry.canonicalPath.filename().string();
            forEntry.fileEntries.Add(fileEntry);
        }
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------