#include "ToggleButton.h"

ToggleButton::ToggleButton(std::string id, std::vector <std::string> toggleTexts, Vector2 position, Vector2 startSize, bool isOn) : Button( id, position, startSize)
{
	this->isOn = isOn;
	this->toggleTexts = toggleTexts;
	OnClick = [=](){Toggle();};
	AddText(id + "ToggleText", toggleTexts[0], "Vorgang", { 255, 255, 255, 255 });
}

void ToggleButton::Toggle()
{	
	SetText(toggleTexts[isOn]);
	if(OnToggleChange)OnToggleChange(isOn = !isOn);
}
