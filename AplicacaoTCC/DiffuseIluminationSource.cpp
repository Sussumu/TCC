#include "DiffuseIluminationSource.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DiffuseIluminationSource::DiffuseIluminationSource(std::vector<ShaderProgram*> shaderPrograms, GLfloat* vertices, glm::vec3* position)
{
	m_shaderPrograms = shaderPrograms;
	m_vertices = (GLfloat*)malloc(sizeof vertices);
	m_position = (glm::vec3*)malloc(sizeof position);
	memcpy(m_vertices, vertices, sizeof(vertices));
	memcpy(m_position, position, sizeof(position));
}

DiffuseIluminationSource::~DiffuseIluminationSource()
{
}

void DiffuseIluminationSource::setup()
{
#pragma region Draw
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
#pragma endregion
}

void DiffuseIluminationSource::update()
{
#pragma region Lighting
	glm::vec3 lightPosition = { 1.2f, 1.0f, 2.0f };
	GLint objectColorLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "lightColor");
	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
#pragma endregion

	GLint modelLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "model");
	GLint viewLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "view");
	GLint projLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "projection");

	glm::mat4 model;
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewLoc));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projLoc));
	model = glm::mat4();
	model = glm::translate(model, lightPosition);
	model = glm::scale(model, glm::vec3(0.2f)); 
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}

void DiffuseIluminationSource::clean()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}
