#pragma once

#include "Image.h"
#include "Animator.h"

class AnimatedImage : public Image
{
	
private:
	
	Animator animator;
	
public:
	
	AnimatedImage(std::string ID, std::string imageID, Vector2 anchorPositon, int numberOfCell, float speed);
	virtual ~AnimatedImage();
	
	virtual void Update(float deltaTime);
	virtual void Draw();
};

