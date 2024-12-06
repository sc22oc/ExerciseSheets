#ifndef SIMPLE_MESH_HPP_C6B749D6_C83B_434C_9E58_F05FC27FEFC9
#define SIMPLE_MESH_HPP_C6B749D6_C83B_434C_9E58_F05FC27FEFC9

#include <glad/glad.h>

#include <vector>

#include "../vmlib/vec2.hpp"
#include "../vmlib/vec3.hpp"

struct SimpleMeshData
{
	std::vector<Vec3f> positions;
	std::vector<Vec2f> texcoords;
};

GLuint create_vao( SimpleMeshData const& );

#endif // SIMPLE_MESH_HPP_C6B749D6_C83B_434C_9E58_F05FC27FEFC9
