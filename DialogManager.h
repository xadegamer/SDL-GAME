#pragma once

#include "UIManager.h"
#include "Text.h"
#include "vector"

struct Dialog
{
	std::string ID;
	std::vector<std::string> texts;

	Dialog(std::string id, std::vector<std::string> texts)
	{
		ID = id;
		this->texts = texts;
	}
};

class DialogManager
{
	
private:
	
	DialogManager() = delete;
	~DialogManager() = delete;
	
	static Dialog* currentDialog;
	static Text* dialogText;
	static std::vector<Dialog*> dialogs;
	static bool isDialogActive;

	static float dialogTimer;
	static float dialogMessageInterval;
	static int currentDialogIndex;
	static std::function <void()> OnFinishedEvent;
	
public:
	
	static void Init();
	static void ShowDialog(std::string id, std::function <void()> OnFinished = nullptr);
	static void Update(float deltaTime);
	static void EndDialog();
};

