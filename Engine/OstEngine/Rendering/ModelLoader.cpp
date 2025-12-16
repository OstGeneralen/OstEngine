#include "ModelLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h> 

void ost::ModelLoading::Load( const std::string& aPath, CDXModel& aInto )
{
    aInto;
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile( aPath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices );
    scene;
}