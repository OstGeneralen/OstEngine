// Kasper "OstGeneralen" Esbjornsson - 2026
#include "File.h"

#include <fstream>

using namespace ost;

// ------------------------------------------------------------

Blob FileUtility::ReadFileToBlob(const std::string& path)
{
    std::ifstream readStream{path, std::ios::binary | std::ios::ate};
    Blob blob{static_cast<SizeType>(readStream.tellg())};
    readStream.seekg(0);

    readStream.read(static_cast<char*>(blob.DataWritable()), blob.Size());

    readStream.close();

    return blob;
}

// ------------------------------------------------------------

char* ost::FileUtility::ReadFileToCharArray(const std::string& path, SizeType& outSize)
{
    std::ifstream readStream{path, std::ios::ate | std::ios::binary};

    if (!readStream)
    {
        outSize = 0;
        return nullptr;
    }

    outSize = readStream.tellg();
    char* buff = new char[outSize];
    readStream.seekg(0);
    readStream.read(buff, outSize);
    readStream.close();

    return buff;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------