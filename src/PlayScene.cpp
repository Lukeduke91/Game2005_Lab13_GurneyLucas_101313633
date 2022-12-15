#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "InputType.h"
#include "Box.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::Start();
}

PlayScene::~PlayScene()
= default;



void PlayScene::Draw()
{
	DrawDisplayList();

	glm::vec2 velocity = Util::AngleMagnitudeToVec2(m_angleDegrees, m_speed);
	glm::vec2 endposition = m_startPosition + velocity;
	Util::DrawLine(m_startPosition, endposition, glm::vec4(1.0f, 0.3f, 0.3f, 1.0f));

	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void PlayScene::Update()
{

	//t += PHYSICS_TIMESTEP;
	//m_deltaTime += PHYSICS_TIMESTEP;
	//// Makes PlaneSprite spin
	//m_pPlaneSprite->GetTransform()->position = 
	//	glm::vec2(d + cos(t * a) * b, c + sin(t * a) * b);
	//// Makes Player spin
	//m_pPlayer->GetTransform()->position = glm::vec2(m_pPlayer->GetTransform()->position.x + (-sin(t *a)) * a * b * PHYSICS_TIMESTEP, 
	//	m_pPlayer->GetTransform()->position.y + (cos(t * a)) * a * b * PHYSICS_TIMESTEP);

	//float Velocity = m_LaunchSpeed * m_deltaTime;
	//glm::vec2 Angle = AngleMagnitudeToVec2(m_LaunchAngle, m_LaunchSpeed);
	//float frame = (Angle.y + m_AccelerationGravity++) * m_deltaTime;
	////Yeets the box
	//m_pShip->GetTransform()->position = glm::vec2(100 + Velocity, m_startingY + frame);

	//if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
	//{
	//	m_deltaTime = 0.0f;

	//	m_AccelerationGravity = 9.80f;
	//}


	UpdateDisplayList();
	Physics.Update();
}

void PlayScene::Clean()
{
	RemoveAllChildren();
}


void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();

	GetKeyboardInput();
}

void PlayScene::GetKeyboardInput()
{
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
	{
		Box* box = new Box();
		AddChild(box);
		Physics.AddObject(box->GetRigidBody());
		box->GetRigidBody()->velocity = Util::AngleMagnitudeToVec2(m_angleDegrees, m_speed);
		box->GetTransform()->position = m_startPosition;
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::START);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance().ChangeSceneState(SceneState::END);
	}
}

void PlayScene::Start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Set Input Type
	//m_pCurrentInputType = static_cast<int>(InputType::KEYBOARD_MOUSE);
	
	// Plane Sprite
	m_pPlaneSprite = new Plane();
	AddChild(m_pPlaneSprite);

	// Player Sprite
	m_pPlayer = new Player();
	AddChild(m_pPlayer);
	m_pPlayer->GetTransform()->position =
		glm::vec2(100, m_startingY);

	// Box Sprite
	m_pShip = new Ship();
	AddChild(m_pShip);
	m_pShip->GetTransform()->position = glm::vec2(200, m_startingY);

	m_pShip1 = new Ship();
	AddChild(m_pShip1);
	m_pShip1->GetTransform()->position = glm::vec2(450, m_startingY);

	m_pHalfPlane = new HalfPlane();
	AddChild(m_pHalfPlane);
	m_pHalfPlane->GetTransform()->position = glm::vec2(400, 550);

	Physics.AddObject(m_pShip->GetRigidBody());
	Physics.AddObject(m_pShip1->GetRigidBody());
	//Physics.AddObject(m_pPlaneSprite->GetRigidBody());
	//m_pPlaneSprite->GetRigidBody()->gravityScale = 0.0f;
	//m_pPlaneSprite->GetTransform()->position = glm::vec2(400, 400);
	Physics.AddObject(m_pHalfPlane->GetRigidBody());
	m_pHalfPlane->GetRigidBody()->gravityScale = 0.0f;
	m_pShip1->GetRigidBody()->gravityScale *= 0.0f;
	m_pShip->GetRigidBody()->gravityScale *= 0.0f;
	//m_pShip->GetRigidBody()->mass = 2.0f;
	//m_pShip1->GetRigidBody()->mass = 2.0f;

	Box* box = new Box();
	AddChild(box);
	box->GetRigidBody()->gravityScale = 0.0f;
	box->GetTransform()->position = glm::vec2(900, 590);
	box->colliderWidth = 450;
	box->GetRigidBody()->mass = 10000.0f;
	Physics.AddObject(box->GetRigidBody());

	/*Box* box1 = new Box();
	AddChild(box1);
	box1->GetRigidBody()->gravityScale = 0.0f;
	box1->GetTransform()->position = glm::vec2(900, 450);
	box1->colliderWidth = 100;
	box1->GetRigidBody()->mass = 10000.0f;
	Physics.AddObject(box1->GetRigidBody());

	Box* box2 = new Box();
	AddChild(box2);
	box2->GetRigidBody()->gravityScale = 0.0f;
	box2->GetTransform()->position = glm::vec2(900, 330);
	box2->colliderWidth = 100;
	box2->GetRigidBody()->mass = 10000.0f;
	Physics.AddObject(box2->GetRigidBody());

	Box* box3 = new Box();
	AddChild(box3);
	box3->GetRigidBody()->gravityScale = 0.0f;
	box3->GetTransform()->position = glm::vec2(900, 210);
	box3->colliderWidth = 100;
	box3->GetRigidBody()->mass = 10000.0f;
	Physics.AddObject(box3->GetRigidBody());*/

	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	/*ImGui::Text("Player Input");
	ImGui::RadioButton("Keyboard / Mouse", &m_pCurrentInputType, static_cast<int>(InputType::KEYBOARD_MOUSE)); ImGui::SameLine();
	ImGui::RadioButton("Game Controller", &m_pCurrentInputType, static_cast<int>(InputType::GAME_CONTROLLER)); ImGui::SameLine();
	ImGui::RadioButton("Both", &m_pCurrentInputType, static_cast<int>(InputType::ALL));*/

	ImGui::Separator();

	if (ImGui::Button("Example 1"))
	{
		std::cout << "My Button Pressed" << std::endl;
		m_pShip->GetTransform()->position = glm::vec2(200, m_startingY);
		m_pShip1->GetTransform()->position = glm::vec2(450, m_startingY);
		m_pShip->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pShip1->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);

		m_pShip1->GetRigidBody()->mass = 8.0f;
		m_pShip1->GetRigidBody()->bounsiness = 0.5f;
		m_pShip->GetRigidBody()->mass = 8.0f;
		m_pShip->GetRigidBody()->bounsiness = 0.5f;
	}

	if(ImGui::Button("Example 2"))
	{
		std::cout << "My Button Pressed" << std::endl;
		m_pShip->GetTransform()->position = glm::vec2(200, m_startingY);
		m_pShip1->GetTransform()->position = glm::vec2(450, m_startingY);
		m_pShip->GetRigidBody()->velocity = glm::vec2(0.0f,0.0f);
		m_pShip1->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);

		m_pShip1->GetRigidBody()->mass = 2.0f; 
		m_pShip1->GetRigidBody()->bounsiness = 2.0f;
		m_pShip->GetRigidBody()->mass = 8.0f;
		m_pShip->GetRigidBody()->bounsiness = 0.5f;
	}

	if (ImGui::Button("Example 3"))
	{
		std::cout << "My Button Pressed" << std::endl;
		m_pShip->GetTransform()->position = glm::vec2(200, m_startingY);
		m_pShip1->GetTransform()->position = glm::vec2(450, m_startingY);
		m_pShip->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pShip1->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);

		m_pShip1->GetRigidBody()->mass = 8.0f;
		m_pShip1->GetRigidBody()->bounsiness = 0.5f;
		m_pShip->GetRigidBody()->mass = 2.0f;
		m_pShip->GetRigidBody()->bounsiness = 2.0f;
	}

	if (ImGui::Button("Example 4"))
	{
		std::cout << "My Button Pressed" << std::endl;
		m_pShip->GetTransform()->position = glm::vec2(200, m_startingY);
		m_pShip1->GetTransform()->position = glm::vec2(450, m_startingY);
		m_pShip->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pShip1->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);

		m_pShip1->GetRigidBody()->mass = 12.0f;
		m_pShip1->GetRigidBody()->bounsiness = 0.5f;
		m_pShip->GetRigidBody()->mass = 2.0f;
		m_pShip->GetRigidBody()->bounsiness = 0.5f;
	}

	ImGui::Separator();
	//used for the line in the playscene
	ImGui::SliderFloat("Angle", &m_angleDegrees, 0, 360);
	ImGui::SliderFloat("Speed", &m_speed, 0, 2000);
	ImGui::SliderFloat2("Start Position", &(m_startPosition.x), 0, 600);

	glm::vec2 velocity = Util::AngleMagnitudeToVec2(m_angleDegrees, m_speed);
	ImGui::LabelText("Velocity Vector", "x:%f, y:%f", velocity.x, velocity.y);

	ImGui::Separator();

	
	if (ImGui::SliderFloat("HalfPlane Angle", &m_angleHalfPlane, 0, 360))
	{
		m_pHalfPlane->SetOrientation(m_angleHalfPlane);
	}
	ImGui::SliderFloat2("HalfPlanePosition", &(m_pHalfPlane->GetTransform()->position.x), 0, 800);
	// Add the rest of A, B, C, D, DT
	/*ImGui::SliderFloat("A", &a, 0.0f, 100.0f);
	ImGui::SliderFloat("B", &b, 0.0f, 100.0f);
	ImGui::SliderFloat("C", &c, 0.0f, 100.0f);
	ImGui::SliderFloat("D", &d, 0.0f, 100.0f);
	ImGui::SliderFloat("time", &t, 0.0f, 100.0f);*/
	//ImGui::SliderFloat("Delta Time", &PHYSICS_TIMESTEP, 0.0f, 100.0f);

	/*ImGui::Separator();
	ImGui::SliderFloat("Launch Degrees", &m_LaunchAngle, 0, 360);
	ImGui::SliderFloat("Launch Speed", &m_LaunchSpeed, 0, 800);
	ImGui::SliderFloat("Start Position", &m_startingY, 0, 600);
	ImGui::SliderFloat("AccelerationGravity", &m_AccelerationGravity, -100, 100);*/

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();
}
