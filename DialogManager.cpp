#include "DialogManager.h"

Dialog* DialogManager::currentDialog = nullptr;
Text* DialogManager::dialogText = nullptr;
std::vector<Dialog*> DialogManager::dialogs;
bool DialogManager::isDialogActive = false;
float DialogManager::dialogTimer = 0.0f;
float DialogManager::dialogMessageInterval = 1.5f;
int DialogManager::currentDialogIndex = 0;
std::function <void()> DialogManager::OnFinishedEvent = nullptr;

void DialogManager::Init()
{
	dialogText = UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Text>("DialogText");
	EndDialog();
}

void DialogManager::ShowDialog(std::string id, std::function <void()> OnFinished)
{
	EndDialog();
	currentDialog = AssetManager::GetDialog(id);
	OnFinishedEvent = OnFinished;
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
			else
			{
				if (OnFinishedEvent)
				{
					OnFinishedEvent();
					OnFinishedEvent = nullptr;
				}
				EndDialog();
			}
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
