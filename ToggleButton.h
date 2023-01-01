#pragma once

#include "Button.h"

#include <vector>

class ToggleButton : public Button
{
	
private:	
	
	bool isOn;
	std::vector <std::string> toggleTexts;
	std::function <void(bool)> onToggleChange;

public:
	
	ToggleButton(std::string id, std::vector <std::string> toggleTexts, Vector2 position, Vector2 startSize, bool isOn = true);

	inline  std::function <void(bool)>& OnToggleChange() { return onToggleChange; }
	
	void Toggle();
};

