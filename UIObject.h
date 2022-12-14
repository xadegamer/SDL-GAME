#pragma once

#include "SDLManager.h"
#include "AssetManager.h"
#include "MathUtility.h"
#include "Vector2.h"
#include "Transform.h"
#include "InputManager.h"

#include <iostream>
#include <functional>

class UIObject
{
protected:
	std::string ID;

	Vector2 anchorPositon;
	Vector2 centerPositon;
	Vector2 size;

	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Color color;

	int layer = 0;
	bool isStatic;

public:
	
	UIObject();
	virtual ~UIObject();

	virtual void Draw();
	virtual void Update();

	inline void SetID(std::string id) { ID = id; }
	inline std::string GetID() { return ID; }
	
	inline void SetAnchorPosition(Vector2 pos) { anchorPositon = pos; }
	inline Vector2 GetAnchorPosition() { return anchorPositon; }
	
	inline void SetCenterPosition(Vector2 pos) { centerPositon = pos; }
	inline Vector2 GetCenterPosition() { return centerPositon; }
	
	inline void SetSize(Vector2 size) { this->size = size; }
	inline Vector2 GetSize() { return size; }

	inline void SetTexture(SDL_Texture* texture) { this->texture = texture; }
	inline SDL_Texture* GetTexture() { return texture; }

	inline void SetRect(SDL_Rect rect) { this->rect = rect; }
	inline SDL_Rect GetRect() { return rect; }

	inline void SetColor(SDL_Color color) { this->color = color; }
	inline SDL_Color GetColor() { return color; }

	inline void SetLayer(int layer) { this->layer = layer; }
	inline int GetLayer() { return layer; }
	
	inline void SetStatic(bool isStatic) { this->isStatic = isStatic; }
	inline bool GetStatic() { return isStatic; }
};

