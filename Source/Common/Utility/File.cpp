// Kasper "OstGeneralen" Esbjornsson - 2026
#include "File.h"

#include <fstream>

using namespace ost;

// ------------------------------------------------------------

Blob FileUtility::ReadFileToBlob(const std::string& path)
{
    std::fstream readStream{path, std::ios::binary | std::ios::ate};
    Blob blob{readStream.tellg()};
    readStream.seekg(0);

    readStream.read(static_cast<char*>(blob.DataWritable()), blob.Size());

    readStream.close();

    return blob;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------