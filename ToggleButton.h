#pragma once

#include "Button.h"

#include <vector>

class ToggleButton : public Button
{
	
private:	
	bool isOn;
	
	std::vector <std::string> toggleTexts;
	

public:
	
	std::function <void(bool)> OnToggleChange;
	
	ToggleButton(std::string id, std::vector <std::string> toggleTexts, Vector2 position, Vector2 startSize, bool isOn = true);
	
	void Toggle();
};

