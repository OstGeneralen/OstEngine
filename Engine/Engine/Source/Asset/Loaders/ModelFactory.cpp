// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ModelFactory.h"

#include <GraphicsEngine/Rendering/Vertex.h>
#include <GraphicsEngine/Resources/Descriptors/BufferDesc.h>
#include <GraphicsEngine/Resources/IGraphicsResourceManager.h>
#include <Memory/Memory.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace ost;

// ------------------------------------------------------------

ost::ModelFactory::ModelFactory(IGraphicsResourceManager& gfxResourceManager)
    : _gfxResourceManager{gfxResourceManager}
{
}

// ------------------------------------------------------------

TypeID ost::ModelFactory::AssetTypeID() const
{
    return TypeID::Get<ModelAsset>();
}

// ------------------------------------------------------------

Asset* ost::ModelFactory::ConstructDefault() const
{
    return new ModelAsset();
}

// ------------------------------------------------------------

void ost::ModelFactory::Load(const std::filesystem::path& path, Asset* pInto) const
{
    Assimp::Importer importer;
    const aiScene* importScene =
        importer.ReadFile(path.string(), aiProcess_CalcTangentSpace | aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_GenNormals);

    List<Uint32> indices;

    // TODO: Add other potential vertex layouts to here!
    List<StaticVertex> staticVertices;
    List<Submesh> submeshes;

    for (SizeType meshIndex = 0; meshIndex < importScene->mNumMeshes; ++meshIndex)
    {
        const aiMesh* importMesh = importScene->mMeshes[meshIndex];

        Submesh buildMesh;
        buildMesh.indexCount = importMesh->mNumFaces * 3;
        buildMesh.vertexCount = importMesh->mNumVertices;
        buildMesh.materialIndex = importMesh->mMaterialIndex;
        buildMesh.vertexOffset = staticVertices.GetSize();
        buildMesh.indexOffset = indices.GetSize();
        submeshes.Add(buildMesh);

        for (SizeType vertIndex = 0; vertIndex < importMesh->mNumVertices; ++vertIndex)
        {
            const aiVector3f& importVert = importMesh->mVertices[vertIndex];
            const aiVector3f& importNormal = importMesh->mNormals[vertIndex];
            const aiVector3f& importTangent = importMesh->mTangents[vertIndex];

            StaticVertex vertex;
            vertex.position = {importVert.x, importVert.y, importVert.z, 1};
            vertex.normal = {importNormal.x, importNormal.y, importNormal.z};
            vertex.tangent = {importTangent.x, importTangent.y, importTangent.z};
            vertex.color = Colors::White;

            if (importMesh->HasTextureCoords(0))
            {
                const aiVector3f& importUV = importMesh->mTextureCoords[0][vertIndex];
                vertex.uv = {importUV.x, importUV.y};
            }
            if (importMesh->HasVertexColors(0))
            {
                const aiColor4D& importCol = importMesh->mColors[0][vertIndex];
                vertex.color = Color{importCol.r, importCol.g, importCol.b, 1};
            }

            staticVertices.Add(vertex);
        }

        for (SizeType faceIndex = 0; faceIndex < importMesh->mNumFaces; ++faceIndex)
        {
            const aiFace& importFace = importMesh->mFaces[faceIndex];

            indices.Add(importFace.mIndices[0]); // + buildMesh.vertices.offset);
            indices.Add(importFace.mIndices[1]); // + buildMesh.vertices.offset);
            indices.Add(importFace.mIndices[2]); // + buildMesh.vertices.offset);
        }
    }

    HVertexBuffer vertexBufferHandle;
    HIndexBuffer indexBufferHandle;

    { // Create Vertex Buffer
        VertexBufferDesc vertexBufferDesc = {};
        vertexBufferDesc.vertexType = EVertexType::Static;
        vertexBufferDesc.numVertices = staticVertices.GetSize();
        vertexBufferDesc.pVertexData = staticVertices.GetData();
        vertexBufferHandle = _gfxResourceManager.CreateVertexBuffer(vertexBufferDesc);
    }

    { // Create Index Buffer
        IndexBufferDesc indexBufferDesc = {};
        indexBufferDesc.numIndices = indices.GetSize();
        indexBufferDesc.pIndexData = indices.GetData();
        indexBufferHandle = _gfxResourceManager.CreateIndexBuffer(indexBufferDesc);
    }

    static_cast<ModelAsset&>(*pInto) = std::move(ModelAsset(vertexBufferHandle, indexBufferHandle, std::move(submeshes)));
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------