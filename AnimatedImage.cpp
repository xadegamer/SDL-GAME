#include "AnimatedImage.h"

AnimatedImage::AnimatedImage(std::string ID, std::string imageID, Vector2 anchorPositon, int numberOfCell, float speed) : Image(ID, imageID, anchorPositon)
{
	animator.SetSprite(spriteRenderer.GetSprite());
	animator.AddAnimationClip("Idle", AssetManager::GetSprite(imageID), numberOfCell, speed);
	centerPositon = anchorPositon - Vector2(animator.GetCurrentAnimationClip()->animPixelWidth / 2, animator.GetCurrentAnimationClip()->animPixelHeight / 2);
}

AnimatedImage::~AnimatedImage()
{
	
}

void AnimatedImage::Update(float deltaTime)
{
	animator.Update(deltaTime);
}

void AnimatedImage::Draw()
{
	spriteRenderer.Draw(animator.GetSprite()->texture, centerPositon, 0, animator.GetRect());
}
