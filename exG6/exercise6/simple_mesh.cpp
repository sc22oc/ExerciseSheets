#include "simple_mesh.hpp"

SimpleMeshData concatenate( SimpleMeshData aM, SimpleMeshData const& aN )
{
	aM.positions.insert( aM.positions.end(), aN.positions.begin(), aN.positions.end() );
	aM.normals.insert( aM.normals.end(), aN.normals.begin(), aN.normals.end() );
	aM.texcoords.insert( aM.texcoords.end(), aN.texcoords.begin(), aN.texcoords.end() );
	return aM;
}


GLuint create_vao( SimpleMeshData const& aMeshData )
{
	//TODO: implement me
	return 0;
}

