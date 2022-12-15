#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Ship.h"
#include "HalfPlane.h"
#include "Button.h"
#include "Label.h"
#include "PhysicsEngine.h"

const float PHYSICS_TIMESTEP = 0.016f;

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	// Scene LifeCycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	//glm::vec2 m_mousePosition;

	Plane* m_pPlaneSprite{};
	Player* m_pPlayer{};
	Ship* m_pShip{};
	Ship* m_pShip1{};
	HalfPlane* m_pHalfPlane;
	//Ship* m_pBox{};
	//bool m_playerFacingRight{};

	/*
		X1, Y1 = position of parametric simulation object
		X2, Y2 = position of iterative simulation object
		t = game time, in seconds (time since play scene began)
		dt = delta time, in seconds (time since last frame)
		a = variable.
		b = variable.
		c = variable.
		d = variable.
	*/
	float t = 0.0f;
	float a = 1.0f;
	float b = 100.0f;
	float c = 100.0f;
	float d = 100.0f;

	// UI Items
	//Button* m_pBackButton{};
	//Button* m_pNextButton{};
	//Label* m_pInstructionsLabel{};

	float m_angleDegrees = 0;
	float m_speed = 500; // p/s
	glm::vec2 m_startPosition = glm::vec2(0, 500);

	float m_angleHalfPlane = 0.0f;
	
	float m_deltaTime = 0.0f;
	float m_LaunchAngle = 90.0f;
	float m_LaunchSpeed = 50;
	float m_startingY = 200.f;
	float m_AccelerationGravity = 9.80f;

	// Input Control
	//int m_pCurrentInputType{};
	void GetKeyboardInput();
	PhysicsEngine Physics;
};

#endif /* defined (__PLAY_SCENE__) */