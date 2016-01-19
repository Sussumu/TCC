#pragma once

#include "WindowComponent.h"
#include "ShaderProgram.h"
#include "Scenario.h"
#include "Camera.h"
#include <vector>

class Simulador
{
public:

	Simulador(int option);
	~Simulador();

	bool initializeSystems(); 
	void setupScenario(int option);
	bool gameLoop(int scenario);
	
private:

	enum SimulationState
	{
		PLAY,
		EXIT
	} m_simulationState;

	// DeltaTime
	float m_actualTicks = 0, m_deltaTime = 0;
	float m_maxFps { 60.0f };

	// Input
	GLfloat m_lastMouseX = SCREEN_WIDTH/2, m_lastMouseY = SCREEN_HEIGHT/2;
	bool m_firstMouse = true;

	// Componentes
	WindowComponent* m_window { new WindowComponent() };
	ShaderProgram* m_shaderProgram{ new ShaderProgram() };
	ShaderProgram* m_lightShaderProgram{ new ShaderProgram() };

	Scenario* m_scenario;
	Camera* m_camera;
	std::vector<ShaderProgram*> m_shaderPrograms;

	void render(int scenario);
	void eventHandler();
	void keyboardHandler(SDL_Keycode key);
	void mouseHandler(double currentMouseX, double currentMouseY);
	void mouseScrollHandler(double offset);
	void endProgram();
	void initShaders();
	void updateCamera();
};

