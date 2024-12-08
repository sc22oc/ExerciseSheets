#include "simple_mesh.hpp"

SimpleMeshData concatenate( SimpleMeshData aM, SimpleMeshData const& aN )
{
	aM.positions.insert( aM.positions.end(), aN.positions.begin(), aN.positions.end() );
	aM.colors.insert( aM.colors.end(), aN.colors.begin(), aN.colors.end() );
	aM.normals.insert( aM.normals.end(), aN.normals.begin(), aN.normals.end() );
	return aM;
}

GLuint create_vao( SimpleMeshData const& aMeshData )
{
	//TODO: implement 
	GLuint posVBO = 0;
	GLuint colVBO = 0;
	GLuint normVBO = 0;
	glGenBuffers(1, &posVBO);
	glGenBuffers(1, &colVBO);
	glGenBuffers(1, &normVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER,
				 aMeshData.positions.size() * sizeof(Vec3f),
				 aMeshData.positions.data(),
				 GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colVBO);
	glBufferData(GL_ARRAY_BUFFER,
				 aMeshData.colors.size() * sizeof(Vec3f),
				 aMeshData.colors.data(),
				 GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normVBO);
	glBufferData(GL_ARRAY_BUFFER,
				 aMeshData.normals.size() * sizeof(Vec3f),
				 aMeshData.normals.data(),
				 GL_STATIC_DRAW);

	// VAO
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glVertexAttribPointer(
		0,
		3, GL_FLOAT, GL_FALSE,
		0,
		0
	);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, colVBO);
	glVertexAttribPointer(
		1,
		3, GL_FLOAT, GL_FALSE,
		0,
		0
	);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, normVBO);
	glVertexAttribPointer(
		2,
		3, GL_FLOAT, GL_FALSE,
		0,
		0
	);
	glEnableVertexAttribArray(2);

	return vao;

}
