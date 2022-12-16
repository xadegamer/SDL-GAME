#pragma once

#include "UIObject.h"
#include "SpriteRenderer.h"

class Image : public UIObject
{
private:
	Sprite* sprite;
		
public:
	Image(std::string ID, std::string imageID, Vector2 anchorPositon);
	virtual ~Image();

	virtual void Draw();
	virtual void Update();
};

