#include "UIManager.h"
#include "Engine.h"
#include "AudioManager.h"

std::vector<Canvas*> UIManager::activeCanvases;
float UIManager::refreshRate = 0.01f;
float UIManager::currrentRefreshRate = 0.0f;
Canvas* UIManager::lastActiveCanvas = nullptr;
Canvas* UIManager::activeCanvas = nullptr;

void UIManager::Init()
{
	SetUpMainMenuCanvas();
	SetUpOptionCanvas();
	SetUpGameCanvas();
	SetUpPauseCanvas();
	SetUpWinCanvas();
	SetUpGameOverCanvas();
}

void UIManager::SetUpMainMenuCanvas()
{
	Canvas* canvas = new Canvas("MainMenu", Vector2(Engine::SCREEN_WIDTH, Engine::Engine::SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2);

	Text* title = new Text("TitleText", "WILD WEST RANGER", "Vorgang _Large", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200), 50);
	canvas->AddUIObject(title);

	Button* playButton = new Button("PlayButton",midscreen, Vector2(200, 50));
	playButton->AddText("StartButtonText","Play", "Vorgang", { 255, 255, 255, 255 });
	playButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	playButton->OnClick() = []()
	{
		Engine::GetGame()->StartGame();
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		EnableCanvasByID("GameMenu");
	};
	canvas->AddUIObject(playButton);

	Button* optionButton = new Button("OptionButton",midscreen - Vector2(0, -100), Vector2(200, 50));
	optionButton->AddText("OptionButtonText","Options", "Vorgang", { 255, 255, 255, 255 });
	optionButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	optionButton->OnClick() = []()
	{
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		EnableCanvasByID("OptionsMenu");
	};
	canvas->AddUIObject(optionButton);

	Button* quitButton = new Button("QuitButton",midscreen - Vector2(0, -200), Vector2(200, 50));
	quitButton->AddText("QuitButtonText", "Quit", "Vorgang", { 255, 255, 255, 255 });
	quitButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	quitButton->OnClick() = []()
	{
		Engine::GetGame()->Quit();
	}; 
	canvas->AddUIObject(quitButton);

	Image* background = new Image("MenuImage","BarrelSmall", midscreen - Vector2(0, 300));
	canvas->AddUIObject(background);

	// create animated image 
	AnimatedImage* animatedImage1 = new AnimatedImage("AnimatedImage1", "Cow_Guitar", midscreen - Vector2(300, 0), 12, 0.05f);
	canvas->AddUIObject(animatedImage1);

	AnimatedImage* animatedImage2 = new AnimatedImage("AnimatedImage2", "CowBoy_6_Pistol_Shoot", midscreen - Vector2(-300, 0),8, 0.01f);
	canvas->AddUIObject(animatedImage2);

	// add money image and text
	Vector2 topRightScreenCorner = Vector2(Engine::SCREEN_WIDTH, 0);
	Image* moneyImage = new Image("MenuMoneyImage", "Money", topRightScreenCorner - Vector2(150, -50));
	canvas->AddUIObject(moneyImage);
	
	Text* moneyText = new Text("MenuMoneyText", "1000", "Vorgang", { 255, 255, 255, 255 }, topRightScreenCorner - Vector2(90, -50), 20);
	canvas->AddUIObject(moneyText);

	activeCanvas = lastActiveCanvas = canvas;
	canvas->Show();
	activeCanvases.push_back(canvas);
}

void UIManager::SetUpOptionCanvas()
{
	Canvas* canvas = new Canvas("OptionsMenu", Vector2(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2);

	Text* title = new Text("TitleText","Options", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	// show debug toggle
	ToggleButton* showDebugToggle = new ToggleButton("ToggleMusicButton", { "Debug On", "Debug Off" }, midscreen - Vector2(0, 100), Vector2(200, 50), false);
	showDebugToggle->AddText("ShowDebugToggleText", "Debug Off", "Vorgang", { 255, 255, 255, 255 });
	showDebugToggle->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	showDebugToggle->OnToggleChange() = [](bool toggle)
	{
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		Engine::GetGame()->ToggleDebug(toggle);
	};
	canvas->AddUIObject(showDebugToggle);

	// create toggle button
	ToggleButton* musicToggleButton = new ToggleButton("ToggleMusicButton", { "Music On", "Music Off" }, midscreen, Vector2(200, 50));
	musicToggleButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	musicToggleButton->OnToggleChange() = [](bool toggle)
	{
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		AudioManager::ToggleMusicOnOff(toggle);
	};
	canvas->AddUIObject(musicToggleButton);

	// sfx toggle button
	ToggleButton* sfxToggleButton = new ToggleButton("ToggleSFXButton", { "SFX On", "SFX Off " }, midscreen - Vector2(0, -100), Vector2(200, 50));
	sfxToggleButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	sfxToggleButton->OnToggleChange() = [](bool toggle)
	{
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		AudioManager::ToggleSoundEffectOnOff(toggle);
	};
	canvas->AddUIObject(sfxToggleButton);

	Button* backButton = new Button("BackButton", midscreen - Vector2(0, -200), Vector2(200, 50));
	backButton->AddText("BackButtonText","Back", "Vorgang", { 255, 255, 255, 255 });
	backButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	backButton->OnClick() = []()
	{
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		EnableCanvasByID(lastActiveCanvas->GetID());
	};
	canvas->AddUIObject(backButton);

	activeCanvases.push_back(canvas);
}

void UIManager::SetUpGameCanvas()
{
	Canvas* canvas = new Canvas("GameMenu", Vector2(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT), Vector2(0, 0),false);

	Vector2 midscreen = Vector2(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2);
	Vector2 topRightScreenCorner = Vector2(Engine::SCREEN_WIDTH, 0);
	Vector2 topLeftScreenCorner = Vector2(0, 0);
	
	Button* pauseButton = new Button("PauseButton",topRightScreenCorner - Vector2(50, -50), Vector2(50, 50));
	pauseButton->AddText("PauseButtonText","||", "Vorgang", { 255, 255, 255, 255 });
	pauseButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	pauseButton->OnClick() = []()
	{
		Engine::GetGame()->ChangeGameState(GameState::PauseMode);
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		EnableCanvasByID("PauseMenu");
	};
	canvas->AddUIObject(pauseButton);

	Slider* slider = new Slider("HealthSlider",topLeftScreenCorner + Vector2(200, 50), Vector2(300,30));
	slider->AddText("HealthSliderText","100", "Vorgang_Small", { 255, 255, 255, 255 },20);
	canvas->AddUIObject(slider);

	// create score text
	
	Text* scoreText = new Text("MoneyText", "Money: 0", "Vorgang", { 255, 255, 255, 255 }, topLeftScreenCorner + Vector2(100, 100));
	canvas->AddUIObject(scoreText);

	// add a dialog text in lower middle of screen
	Text* dialogText = new Text("DialogText", "Hello World", "Vorgang", { 255, 255, 255, 255 }, midscreen + Vector2(0, 450));
	canvas->AddUIObject(dialogText);

	activeCanvases.push_back(canvas);
}

void UIManager::SetUpPauseCanvas()
{
	Canvas* canvas = new Canvas("PauseMenu", Vector2(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2);

	Text* title = new Text("PauseMenuTitle","Paused", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	Button* optionButton = new Button("OptionButton", midscreen - Vector2(0, 100), Vector2(200, 50));
	optionButton->AddText("OptionButtonText", "Options", "Vorgang", { 255, 255, 255, 255 });
	optionButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	optionButton->OnClick() = []()
	{
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		EnableCanvasByID("OptionsMenu");
	};
	canvas->AddUIObject(optionButton);

	Button* resumeButton = new Button("ResumeButton",midscreen, Vector2(200, 50));
	resumeButton->AddText("ResumeButtonText","Resume", "Vorgang", { 255, 255, 255, 255 });
	resumeButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	resumeButton->OnClick() = []()
	{
		Engine::GetGame()->ChangeGameState(GameState::PlayMode);
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		EnableCanvasByID("GameMenu");
	};
	canvas->AddUIObject(resumeButton);

	Button* menuButton = new Button("MenuButton",midscreen - Vector2(0, -100), Vector2(200, 50));
	menuButton->AddText("MenuButtonText","Menu", "Vorgang", { 255, 255, 255, 255 });
	menuButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	menuButton->OnClick() = []()
	{
		Engine::GetGame()->ChangeGameState(GameState::MainMenu);
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		EnableCanvasByID("MainMenu");
	};
	canvas->AddUIObject(menuButton);

	activeCanvases.push_back(canvas);
}

void UIManager::SetUpWinCanvas()
{
	Canvas* canvas = new Canvas("WinMenu", Vector2(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2);

	Text* title = new Text("WinMenuTitle", "You Win!", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	Button* menuButton = new Button("MenuButton", midscreen, Vector2(200, 50));
	menuButton->AddText("MenuButtonText", "Menu", "Vorgang", { 255, 255, 255, 255 });
	menuButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	menuButton->OnClick() = []()
	{
		Engine::GetGame()->ChangeGameState(GameState::MainMenu);
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		EnableCanvasByID("MainMenu");
	};
	canvas->AddUIObject(menuButton);

	Text* thanksText = new Text("ThanksText", "Thanks for playing!", "Vorgang", { 255, 255, 255, 255 }, midscreen - Vector2(0, -100));
	canvas->AddUIObject(thanksText);
	
	activeCanvases.push_back(canvas);
}

void UIManager::SetUpGameOverCanvas()
{
	Canvas* canvas = new Canvas("GameOverMenu", Vector2(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT), Vector2(0, 0));

	Vector2 midscreen = Vector2(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2);

	Text* title = new Text("GameOverMenuTitle", "Game Over", "Vorgang", { 0, 255, 255, 255 }, midscreen - Vector2(0, 200));
	canvas->AddUIObject(title);

	// retry button
	Button* retryButton = new Button("RetryButton", midscreen, Vector2(200, 50));
	retryButton->AddText("RetryButtonText", "Retry", "Vorgang", { 255, 255, 255, 255 });
	retryButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	retryButton->OnClick() = []()
	{
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
		Engine::GetGame()->RetryGame();
		EnableCanvasByID("GameMenu");
	};
	canvas->AddUIObject(retryButton);

	
	// menu button
	Button* menuButton = new Button("MenuButton", midscreen - Vector2(0, -100), Vector2(200, 50));
	menuButton->AddText("MenuButtonText", "Menu", "Vorgang", { 255, 255, 255, 255 });
	menuButton->OnMouseOver() = []() {AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonHover"), false); };
	menuButton->OnClick() = []()
	{
		Engine::GetGame()->ChangeGameState(GameState::MainMenu);
		AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("ButtonClick"), false);
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
		for (auto& canvas : activeCanvases) canvas->Update(deltaTime);
		currrentRefreshRate = 0;
	}
}

void UIManager::EnableCanvasByID(std::string id)
{
	for (auto& canvas : activeCanvases)
	{
		if (canvas->GetID() == id)
		{
			lastActiveCanvas = activeCanvas;		
			activeCanvas = canvas;	
			canvas->Show();
		} else canvas->Hide();
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
