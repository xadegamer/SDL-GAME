#include "Camera.h"

#include "Player.h"
#include "Game.h"


SDL_Rect Camera::viewBox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
Player* Camera::player = nullptr;

void Camera::SetUp(Player* currentPlayer)
{
	viewBox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	player = currentPlayer;
}

void Camera::Update()
{
	if (player)
	{
		viewBox.x = (player->GetTransform()->GetPosition().x + player->GetComponent<Collider>()->colliderRect->w / 2) - SCREEN_WIDTH / 2;
		viewBox.y = (player->GetTransform()->GetPosition().y + player->GetComponent<Collider>()->colliderRect->h / 2) - SCREEN_HEIGHT / 2;

		if (viewBox.x < 0) { viewBox.x = 0; }
		if (viewBox.y < 0) { viewBox.y = 0; }
		if (viewBox.x > LEVEL_WIDTH - viewBox.w) { viewBox.x = LEVEL_WIDTH - viewBox.w; }
		if (viewBox.y > LEVEL_HEIGHT - viewBox.h) { viewBox.y = LEVEL_HEIGHT - viewBox.h; }
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
