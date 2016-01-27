#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>

class Cube : public GameObject
{
public:
	Cube(ShaderProgram* shaderProgram, GLfloat* vertices, glm::vec3 position, bool enablePhysics);
	~Cube();

	void setup();
	void updatePhysics();
	void update();
	void clean();

	btRigidBody* getRigidBody();

private:
	ShaderProgram* m_shaderProgram;
	GLfloat* m_vertices;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	//GLuint m_texture1;
	//GLuint m_texture2;
	GLuint m_VBO, m_VAO;

	btCollisionShape* shape;
	btDefaultMotionState* motionState;
	btRigidBody* rigidBody;
	btScalar yaw, pitch, roll;
};

