#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Cube : public GameObject
{
public:
	Cube(std::vector<ShaderProgram*> shaderPrograms, GLfloat* vertices, glm::vec3* position);
	~Cube();

	void setup();
	void update();
	void clean();

private:
	std::vector<ShaderProgram*> m_shaderPrograms;
	GLfloat* m_vertices;
	glm::vec3* m_position;
	GLuint m_texture1;
	GLuint m_texture2;
	GLuint m_VBO, m_VAO;
};

