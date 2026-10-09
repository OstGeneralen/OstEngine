// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace ost;

// ------------------------------------------------------------

void ModelLoader::Load(const std::string& path, ModelCPUData& into)
{
    // Load the data
    {
        Assimp::Importer importer;
        const aiScene* importScene = importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_GenNormals);

        auto& indices = into.indexList;
        auto& vertices = into.vertexList;
        auto& submeshes = into.submeshes;

        into.numMaterials = importScene->mNumMaterials;

        for (SizeType meshIndex = 0; meshIndex < importScene->mNumMeshes; ++meshIndex)
        {
            const aiMesh* importMesh = importScene->mMeshes[meshIndex];

            Uint32 vertexLayoutMaskValue = 0;
            vertexLayoutMaskValue |= importMesh->HasNormals() ? EModelVertexData_Normal : 0;
            vertexLayoutMaskValue |= importMesh->HasTangentsAndBitangents() ? EModelVertexData_Tangent : 0;
            vertexLayoutMaskValue |= importMesh->HasTextureCoords(0) ? EModelVertexData_UV : 0;
            vertexLayoutMaskValue |= importMesh->HasVertexColors(0) ? EModelVertexData_Color : 0;

            ModelCPUData::Mesh buildMesh;
            buildMesh.indices.count = importMesh->mNumFaces * 3;
            buildMesh.vertices.count = importMesh->mNumVertices;
            buildMesh.materialIndex = importMesh->mMaterialIndex;
            buildMesh.vertices.offset = vertices.GetSize();
            buildMesh.indices.offset = indices.GetSize();
            submeshes.Add(buildMesh);

            for (SizeType vertIndex = 0; vertIndex < importMesh->mNumVertices; ++vertIndex)
            {
                const aiVector3f& importVert = importMesh->mVertices[vertIndex];
                const aiVector3f& importNormal = importMesh->mNormals[vertIndex];
                const aiVector3f& importTangent = importMesh->mTangents[vertIndex];

                ModelVertex vertex;
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
                
                indices.Add(importFace.mIndices[0]);// + buildMesh.vertices.offset);
                indices.Add(importFace.mIndices[1]);// + buildMesh.vertices.offset);
                indices.Add(importFace.mIndices[2]);// + buildMesh.vertices.offset);
            }
        }
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------