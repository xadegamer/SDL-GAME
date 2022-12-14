#include "UIManager.h"
#include "Canvas.h"
#include "Game.h"
#include "Button.h"
#include "Text.h"
#include "Canvas.h"
#include "Slider.h"

std::vector<Canvas*> UIManager::activeCanvases;
float UIManager::refreshRate = 0.01f;
float UIManager::currrentRefreshRate = 0.0f;

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

	Text* title = new Text("TitleText", "Top Down Game", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	Button* startButton = new Button("StartButton",midscreen, Vector2(200, 50), 0);
	startButton->AddText("StartButtonText","Start", "Vorgang", { 255, 255, 255, 255 });
	startButton->OnMouseOver = []() {AudioManager::PlayMusic(AssetManager::GetMusic("ButtonHover"), false); };
	startButton->OnClick = []()
	{
		AudioManager::PlayMusic(AssetManager::GetMusic("ButtonClick"), false);
		EnableCanvasByID("GameMenu");
	};
	canvas->AddUIObject(startButton);

	Button* optionButton = new Button("OptionButton",midscreen - Vector2(0, -100), Vector2(200, 50), 0);
	optionButton->AddText("OptionButtonText","Options", "Vorgang", { 255, 255, 255, 255 });
	optionButton->OnMouseOver = []() {AudioManager::PlayMusic(AssetManager::GetMusic("ButtonHover"), false); };
	optionButton->OnClick = []() 
	{
		AudioManager::PlayMusic(AssetManager::GetMusic("ButtonClick"), false);
		EnableCanvasByID("OptionsMenu");
	};
	canvas->AddUIObject(optionButton);

	Button* quitButton = new Button("QuitButton",midscreen - Vector2(0, -200), Vector2(200, 50), 0);
	quitButton->AddText("QuitButtonText", "Quit", "Vorgang", { 255, 255, 255, 255 });
	quitButton->OnMouseOver = []() {AudioManager::PlayMusic(AssetManager::GetMusic("ButtonHover"), false); };
	quitButton->OnClick = Game::Quit;
	canvas->AddUIObject(quitButton);

	canvas->Show();

	activeCanvases.push_back(canvas);
}

void UIManager::SetUpOptionCanvas()
{
	Canvas* canvas = new Canvas("OptionsMenu", Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	Text* title = new Text("TitleText","Options", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	Button* backButton = new Button("BackButton",midscreen, Vector2(200, 50), 0);
	backButton->AddText("BackButtonText","Back", "Vorgang", { 255, 255, 255, 255 });
	backButton->OnMouseOver = []() {AudioManager::PlayMusic(AssetManager::GetMusic("ButtonHover"), false); };
	backButton->OnClick = []()
	{
		AudioManager::PlayMusic(AssetManager::GetMusic("ButtonClick"), false);
		EnableCanvasByID("MainMenu");
	};
	canvas->AddUIObject(backButton);

	activeCanvases.push_back(canvas);
}

void UIManager::SetUpGameCanvas()
{
	Canvas* canvas = new Canvas("GameMenu", Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), Vector2(0, 0),false);

	Vector2 midscreen = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	Vector2 topRightScreenCorner = Vector2(SCREEN_WIDTH, 0);
	Vector2 topLeftScreenCorner = Vector2(0, 0);
	
	Button* pauseButton = new Button("PauseButton",topRightScreenCorner - Vector2(50, -50), Vector2(50, 50), 0);
	pauseButton->AddText("PauseButtonText","||", "Vorgang", { 255, 255, 255, 255 });
	pauseButton->OnMouseOver = []() {AudioManager::PlayMusic(AssetManager::GetMusic("ButtonHover"), false); };
	pauseButton->OnClick = []()
	{
		AudioManager::PlayMusic(AssetManager::GetMusic("ButtonClick"), false);
		EnableCanvasByID("PauseMenu");
	};
	canvas->AddUIObject(pauseButton);

	Slider* slider = new Slider("HealthSlider",topLeftScreenCorner + Vector2(200, 50), Vector2(300,30), 0);
	slider->AddText("HealthSliderText","100", "Vorgang", { 255, 255, 255, 255 });
	canvas->AddUIObject(slider);

	//To Remove
	Button* testButton = new Button("TestButton",midscreen - Vector2(600, -600), Vector2(100, 100), 0);
	testButton->AddText("TestButtonText","Test", "Vorgang", { 255, 255, 255, 255 });
	testButton->OnMouseOver = []() {AudioManager::PlayMusic(AssetManager::GetMusic("ButtonHover"), false); };
	testButton->OnClick = [=]()
	{
		AudioManager::PlayMusic(AssetManager::GetMusic("ButtonClick"), false);	
		slider->SetValue(slider->GetValue() + .1f);
	};
	canvas->AddUIObject(testButton);

	activeCanvases.push_back(canvas);
}

void UIManager::SetUpPauseCanvas()
{
	Canvas* canvas = new Canvas("PauseMenu", Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	Text* title = new Text("PauseMenuTitle","Paused", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	Button* resumeButton = new Button("ResumeButton",midscreen, Vector2(200, 50), 0);
	resumeButton->AddText("ResumeButtonText","Resume", "Vorgang", { 255, 255, 255, 255 });
	resumeButton->OnMouseOver = []() {AudioManager::PlayMusic(AssetManager::GetMusic("ButtonHover"), false); };
	resumeButton->OnClick = []() 
	{
		AudioManager::PlayMusic(AssetManager::GetMusic("ButtonClick"), false);
		EnableCanvasByID("GameMenu");
	};
	canvas->AddUIObject(resumeButton);

	Button* menuButton = new Button("MenuButton",midscreen - Vector2(0, -100), Vector2(200, 50), 0);
	menuButton->AddText("MenuButtonText","Menu", "Vorgang", { 255, 255, 255, 255 });
	menuButton->OnMouseOver = []() {AudioManager::PlayMusic(AssetManager::GetMusic("ButtonHover"), false); };
	menuButton->OnClick = []() 
	{
		AudioManager::PlayMusic(AssetManager::GetMusic("ButtonClick"), false);
		EnableCanvasByID("MainMenu");
	};
	canvas->AddUIObject(menuButton);

	activeCanvases.push_back(canvas);
}

void UIManager::Draw()
{
	for (auto& canvas : activeCanvases) canvas->Draw();
}

void UIManager::Update(float deltaTime)
{
	currrentRefreshRate += deltaTime;
	
	if (currrentRefreshRate > refreshRate)
	{
		for (auto& canvas : activeCanvases) canvas->Update();
		currrentRefreshRate = 0;
	}
}

void UIManager::EnableCanvasByID(std::string id)
{
	std::cout << "Enabling canvas: " << id << std::endl;
	for (auto& canvas : activeCanvases)
	{
		if (canvas->GetID() == id) canvas->Show(); else canvas->Hide();
	}
}

void UIManager::Clean()
{
	for (auto& canvas : activeCanvases)
	{
		delete canvas;
		canvas = nullptr;
	}
	activeCanvases.clear();
}

Canvas* UIManager::GetCanvasByID(std::string id)
{
	for (auto& canvas : activeCanvases) if (canvas->GetID() == id) return canvas;
	return nullptr;
}
