#include "Camera.h"
#include "Engine.h"
#include "GameObject.h"
#include "Game.h"


SDL_Rect Camera::viewBox = { 0, 0, Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT };
GameObject* Camera::player = nullptr;

void Camera::SetUp(GameObject* currentPlayer)
{
	viewBox = { 0, 0,  Engine::SCREEN_WIDTH,  Engine::SCREEN_HEIGHT };
	player = currentPlayer;
	viewBox.x = (player->GetTransform()->GetPosition().x + player->GetComponent<Collider>()->GetColliderRect()->w / 2) - Engine::SCREEN_WIDTH / 2;
	viewBox.y = (player->GetTransform()->GetPosition().y + player->GetComponent<Collider>()->GetColliderRect()->h / 2) - Engine::SCREEN_HEIGHT / 2;
}

void Camera::Update()
{
	if (player)
	{
		viewBox.x = (player->GetTransform()->GetPosition().x + player->GetComponent<Collider>()->GetColliderRect()->w / 2) - Engine::SCREEN_WIDTH / 2;
		viewBox.y = (player->GetTransform()->GetPosition().y + player->GetComponent<Collider>()->GetColliderRect()->h / 2) - Engine::SCREEN_HEIGHT / 2;

		if (viewBox.x < 0) { viewBox.x = 0; }
		if (viewBox.y < 0) { viewBox.y = 0; }
		if (viewBox.x > Engine::LEVEL_WIDTH - viewBox.w) { viewBox.x = Engine::LEVEL_WIDTH - viewBox.w; }
		if (viewBox.y > Engine::LEVEL_HEIGHT - viewBox.h) { viewBox.y = Engine::LEVEL_HEIGHT - viewBox.h; }
	}
}

Vector2 Camera::GetPosition()
{
	return  Vector2(viewBox.x, viewBox.y);
}

void Camera::Clean()
{
	player = nullptr;
}
