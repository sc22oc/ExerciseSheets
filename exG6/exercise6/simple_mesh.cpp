#include "simple_mesh.hpp"
#include <iostream>

GLuint create_vao( SimpleMeshData const& aMeshData )
{

	GLuint posVBO = 0;
	GLuint texVBO = 0;
	glGenBuffers(1, &posVBO);
	glGenBuffers(1, &texVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER,
				 aMeshData.positions.size() * sizeof(Vec3f),
				 aMeshData.positions.data(),
				 GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER,
				 aMeshData.texcoords.size() * sizeof(Vec2f),
				 aMeshData.texcoords.data(),
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

	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glVertexAttribPointer(
		1,
		2, GL_FLOAT, GL_FALSE,
		0,
		nullptr
	);
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);	
	return vao;
}

