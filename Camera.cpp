#include "Camera.h"

#include "Player.h"
#include "Game.h"


SDL_Rect Camera::camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
Player* Camera::player = nullptr;


void Camera::SetUp(Player* currentPlayer)
{
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	player = currentPlayer;
}

void Camera::Update()
{
	camera.x = (player->transform->position.x + player->GetComponent<Collider>()->colliderRect->w / 2) - SCREEN_WIDTH / 2;
	camera.y = (player->transform->position.y + player->GetComponent<Collider>()->colliderRect->h / 2) - SCREEN_HEIGHT / 2;

	if (camera.x < 0) { camera.x = 0; }
	if (camera.y < 0) { camera.y = 0; }
	if (camera.x > LEVEL_WIDTH - camera.w) { camera.x = LEVEL_WIDTH - camera.w; }
	if (camera.y > LEVEL_HEIGHT - camera.h) { camera.y = LEVEL_HEIGHT - camera.h; }
}

Vector2 Camera::GetPosition()
{
	return  Vector2(camera.x, camera.y);
}

void Camera::Clean()
{
	player = nullptr;
}
