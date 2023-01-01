#include "DialogManager.h"

Dialog* DialogManager::currentDialog = nullptr;
Text* DialogManager::dialogText = nullptr;
std::vector<Dialog*> DialogManager::dialogs;
bool DialogManager::isDialogActive = false;
float DialogManager::dialogTimer = 0.0f;
float DialogManager::dialogMessageInterval = 1.5f;
int DialogManager::currentDialogIndex = 0;

void DialogManager::Init()
{
	dialogText = UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Text>("DialogText");
	EndDialog();
	PopulateDialogs();
}

void DialogManager::PopulateDialogs()
{
	std::vector<std::string> introDialogTexts = { "Welcome to the game!","Use WASD to move", "Use the mouse to aim", "Left click to shoot" };
	dialogs.push_back(new Dialog("Intro", introDialogTexts));
}

void DialogManager::ShowDialog(std::string id)
{
	EndDialog();
	
	for (Dialog* dialog : dialogs)
	{
		if (dialog->ID == id)
		{
			currentDialog = dialog;
			break;
		}
	}
}

void DialogManager::Update(float deltaTime)
{
	if (currentDialog != nullptr)
	{
		if (dialogTimer >= dialogMessageInterval)
		{
			if (currentDialogIndex < currentDialog->texts.size())
			{
				dialogText->SetText(currentDialog->texts[currentDialogIndex]);
				currentDialogIndex++;
				dialogTimer = 0.0f;
			}
			else EndDialog();
		}
		else dialogTimer += deltaTime;
	}
}

void DialogManager::EndDialog()
{
	currentDialogIndex = 0;
	currentDialog = nullptr;
	dialogText->SetText(" ");
}
