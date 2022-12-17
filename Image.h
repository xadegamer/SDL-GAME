#pragma once

#include "UIObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"

class Image : public UIObject
{
protected:
	SpriteRenderer spriteRenderer;
		
public:
	Image(std::string ID, std::string imageID, Vector2 anchorPositon);
	virtual ~Image();

	virtual void Update(float deltaTime);
	virtual void Draw();
};

