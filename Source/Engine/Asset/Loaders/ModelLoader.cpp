// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ModelLoader.h"

#include "Engine/OstEngine.h"

#include <GraphicsEngine/GraphicsEngine.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace ost;

// ------------------------------------------------------------

void ModelLoader::LoadAsset(ModelAsset& asset)
{
    asset.state = EAssetState::Loading;

    // Load the data
    {
        Assimp::Importer importer;
        const aiScene* importScene =
            importer.ReadFile(asset.path, aiProcess_CalcTangentSpace | aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_GenNormals);

        auto& indices = asset.cpuData.indices;
        auto& vertices = asset.cpuData.vertices;
        auto& submeshes = asset.cpuData.meshes;

        for (SizeType meshIndex = 0; meshIndex < importScene->mNumMeshes; ++meshIndex)
        {
            const aiMesh* importMesh = importScene->mMeshes[meshIndex];

            StaticModelDesc::Submesh buildMesh;
            buildMesh.indexCount = importMesh->mNumFaces * 3;
            buildMesh.vertexCount = importMesh->mNumVertices;
            buildMesh.materialIndex = importMesh->mMaterialIndex;
            buildMesh.vertexOffset = vertices.GetSize();
            buildMesh.indexOffset = indices.GetSize();
            submeshes.Add(buildMesh);

            for (SizeType vertIndex = 0; vertIndex < importMesh->mNumVertices; ++vertIndex)
            {
                const aiVector3f& importVert = importMesh->mVertices[vertIndex];
                const aiVector3f& importNormal = importMesh->mNormals[vertIndex];
                const aiVector3f& importTangent = importMesh->mTangents[vertIndex];

                SurfaceVertex vertex;
                vertex.position = {importVert.x, importVert.y, importVert.z, 1};
                vertex.normal = {importNormal.x, importNormal.y, importNormal.z};
                vertex.tangent = {importTangent.x, importTangent.y, importTangent.z};

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

                vertices.Add(vertex);
            }

            for (SizeType faceIndex = 0; faceIndex < importMesh->mNumFaces; ++faceIndex)
            {
                const aiFace& importFace = importMesh->mFaces[faceIndex];

                indices.Add(importFace.mIndices[0]);
                indices.Add(importFace.mIndices[1]);
                indices.Add(importFace.mIndices[2]);
            }
        }
    }

    // Build the resource
    asset.gpuHandle = pEngine->GetGraphicsEngine().GetResourceManager().Create(asset.cpuData);
    asset.cpuData = {};

    asset.state = EAssetState::Ready;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------