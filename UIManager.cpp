#include "UIManager.h"
#include "Canvas.h"
#include "Game.h"

std::vector<Canvas*> UIManager::activeCanvases;

void UIManager::Init()
{
	SetUpMainMenuCanvas();
	SetUpOptionCanvas();
	SetUpGameCanvas();
	SetUpPauseCanvas();
}

void UIManager::SetUpMainMenuCanvas()
{
	Canvas* canvas = new Canvas("MainMenu", Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	Text* title = new Text("Top Down Game", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	Button* startButton = new Button(midscreen, Vector2(200, 50), 0);
	startButton->AddText("Start", "Vorgang", { 255, 255, 255, 255 });
	startButton->OnClick = []()
	{
		EnableCanvasByID("GameMenu");
	};
	canvas->AddUIObject(startButton);

	Button* optionButton = new Button(midscreen - Vector2(0, -100), Vector2(200, 50), 0);
	optionButton->AddText("Options", "Vorgang", { 255, 255, 255, 255 });
	optionButton->OnClick = []() 
	{
		EnableCanvasByID("OptionsMenu");
	};
	canvas->AddUIObject(optionButton);

	Button* quitButton = new Button(midscreen - Vector2(0, -200), Vector2(200, 50), 0);
	quitButton->AddText("Quit", "Vorgang", { 255, 255, 255, 255 });
	quitButton->OnClick = Game::Quit;
	canvas->AddUIObject(quitButton);

	canvas->Show();

	activeCanvases.push_back(canvas);
}

void UIManager::SetUpOptionCanvas()
{
	Canvas* canvas = new Canvas("OptionsMenu", Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	Text* title = new Text("Options", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	Button* backButton = new Button(midscreen, Vector2(200, 50), 0);
	backButton->AddText("Back", "Vorgang", { 255, 255, 255, 255 });
	backButton->OnClick = [=]()
	{
		EnableCanvasByID("MainMenu");
	};
	canvas->AddUIObject(backButton);

	activeCanvases.push_back(canvas);
}

void UIManager::SetUpGameCanvas()
{
	Canvas* canvas = new Canvas("GameMenu", Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), Vector2(0, 0),false);

	Vector2 midscreen = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	Button* startButton = new Button(midscreen, Vector2(200, 50), 0);
	startButton->AddText("Pause", "Vorgang", { 255, 255, 255, 255 });
	startButton->OnClick = [=]() 
	{
		EnableCanvasByID("MainMenu");
	};
	canvas->AddUIObject(startButton);

	activeCanvases.push_back(canvas);
}

void UIManager::SetUpPauseCanvas()
{
	Canvas* canvas = new Canvas("PauseMenu", Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	Text* title = new Text("Paused", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	Button* resumeButton = new Button(midscreen, Vector2(200, 50), 0);
	resumeButton->AddText("Resume", "Vorgang", { 255, 255, 255, 255 });
	resumeButton->OnClick = [=]() 
	{
		EnableCanvasByID("GameMenu");
	};
	canvas->AddUIObject(resumeButton);

	Button* menuButton = new Button(midscreen - Vector2(0, -100), Vector2(200, 50), 0);
	menuButton->AddText("Menu", "Vorgang", { 255, 255, 255, 255 });
	menuButton->OnClick = []() 
	{
		EnableCanvasByID("MainMenu");
	};
	canvas->AddUIObject(menuButton);

	activeCanvases.push_back(canvas);
}

void UIManager::Draw()
{
	for (auto& canvas : activeCanvases) canvas->Draw();
}

void UIManager::Update()
{
	for (auto& canvas : activeCanvases) canvas->Update();
}

void UIManager::EnableCanvasByID(std::string id)
{
	for (auto& canvas : activeCanvases)
	{
		if (canvas->ID == id) canvas->Show(); else canvas->Hide();
	}
}