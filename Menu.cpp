#include "Menu.h"
#include "Character.h"
#include <ctime>

RenderWindow Menu::MenuWindow(sf::VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Menu", sf::Style::Fullscreen);

Texture BackgroundTexture;
Sprite BackgroundPicture;
bool Menu::openMainWindow = false;

void ForButtonPlay(bool value)
{
	Menu::openMainWindow = value;
	Menu::MenuWindow.close();
}
void ForButtonOptions(Container* optionContainer, Container* menuContainer, bool value)
{
	optionContainer->setVisible(value);
	optionContainer->setActive(value);

	menuContainer->setVisible(!value);
	menuContainer->setActive(!value);
}
void ForButtonQuit(RenderWindow& window)
{
	Data::SaveAllStaticData();
	window.close();
	Menu::openMainWindow = false;
}
Menu::Menu()
{
	BackgroundTexture.loadFromFile("Pictures/Background.png", sf::IntRect(0, 0, 1920, 1080));
	BackgroundPicture.setTexture(BackgroundTexture);
	Game::errorTexture.setRepeated(true);
	if (!Game::errorTexture.loadFromFile("Pictures/Button.png"))
		throw std::invalid_argument("Failed to load ErrorTexture.png");
	if (!Game::defFont.loadFromFile("Fonts/Roboto-Regular.ttf"))
		throw std::invalid_argument("Failed to load Roboto-Light.ttf");
	Game::defIdleBut = Game::errorTexture;
	Game::defClickedBut = Game::errorTexture;
	Game::defHoverBut = Game::errorTexture;
	if (!Game::defPanel.loadFromFile("Pictures/DefaultPanel.png"))
	{
		Game::defPanel = Game::errorTexture;
		Game::defPanel.setRepeated(true);
	}
	MenuContainer = new Container;
	MenuPanel = new Panel(Vector2f(windowWidth / 3.2, windowHeight/3.6), windowWidth / 3, windowHeight / 2.25);

	OptionsContainer = new Container;
	OptionsPanel = new Panel(Vector2f(windowWidth / 3.2, windowHeight / 3.6), windowWidth / 3, windowHeight / 2.25);
	OptionsContainer->setVisible(false);

	LoadSavedGame = new Button<void(*)(bool)>(Vector2f(MenuPanel->getWidth() / 3.76, MenuPanel->getHeight()/3.7), Vector2f(MenuPanel->getWidth() / 2.1, MenuPanel->getHeight() / 4.8), "Load Saved Game");
	LoadSavedGame->setDelegate(ForButtonPlay);
	Data::ReloadAllStaticData();
	if (Character::CheckIFCharacteristicsBelowZero()) LoadSavedGame->setActive(false);
	else LoadSavedGame->setActive(true);

	NewGame = new Button<void(*)(bool)>(Vector2f(MenuPanel->getWidth() / 3.76, MenuPanel->getHeight() / 48), Vector2f(MenuPanel->getWidth() / 2.1, MenuPanel->getHeight() / 4.8), "New Game");
	NewGame->setDelegate(ForButtonPlay);

	OpenOptions = new Button<void(*)(Container*, Container*, bool)>(Vector2f(MenuPanel->getWidth() / 3.76, MenuPanel->getHeight() / 1.92), Vector2f(MenuPanel->getWidth() / 2.1, MenuPanel->getHeight() / 4.8), "Options");
	OpenOptions->setDelegate(ForButtonOptions);

	Quit = new Button<void(*)(RenderWindow&)>(Vector2f(MenuPanel->getWidth() / 3.76, MenuPanel->getHeight() / 1.3), Vector2f(MenuPanel->getWidth() / 2.1, MenuPanel->getHeight() / 4.8), "Quit");
	Quit->setDelegate(ForButtonQuit);

	CloseOptions = new Button<void(*)(Container*, Container*, bool)>(Vector2f(OptionsPanel->getWidth() / 2.1, OptionsPanel->getHeight() / 1.6), Vector2f(OptionsPanel->getWidth() / 2.1, OptionsPanel->getHeight() / 4.8), "Close Options");
	CloseOptions->setDelegate(ForButtonOptions);

	MenuContainer->addChild(MenuPanel);
	MenuPanel->addChild(LoadSavedGame);
	MenuPanel->addChild(NewGame);
	MenuPanel->addChild(OpenOptions);
	MenuPanel->addChild(Quit);


	OptionsContainer->addChild(OptionsPanel);
	OptionsPanel->addChild(CloseOptions);
}
Menu::~Menu()
{
	delete MenuContainer;
	delete MenuPanel;
	delete OptionsContainer;
	delete OptionsPanel;
	delete NewGame;
	delete LoadSavedGame;
	delete OpenOptions;
	delete Quit;
	delete CloseOptions; 
}
void Menu::Draw()
{
	while (MenuWindow.isOpen())
	{
		while (MenuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (LoadSavedGame->checkClick((Vector2f)Mouse::getPosition(MenuWindow)))
					{
						Data::ReloadAllStaticData();
						LoadSavedGame->Action(true);
					}
					if (NewGame->checkClick((Vector2f)Mouse::getPosition(MenuWindow)))
					{
						srand(time(0));
						Data::SetDeffaultCharacteristics();
						Forest::SetPicture("Pictures/Environment.jpg");
						Lake::SetPicture("Pictures/Lake.jpg");
						River::SetPicture("Pictures/River.jpg");
						Generator::GenerateEnvironments(3, 3);
						Location::LocationCurrent = Data::GetEnvironment(0);
						Location::CheckWhatEnvironment(Location::LocationCurrent);
						NewGame->Action(true);
					}
					if (Quit->checkClick((Vector2f)Mouse::getPosition(MenuWindow))) Quit->Action(MenuWindow);
					if (OpenOptions->checkClick((Vector2f)Mouse::getPosition(MenuWindow))) OpenOptions->Action(OptionsContainer, MenuContainer, true);
					else if (CloseOptions->checkClick((Vector2f)Mouse::getPosition(MenuWindow))) CloseOptions->Action(OptionsContainer, MenuContainer, false);

				}
				break;
			}
		}
		LoadSavedGame->update((Vector2f)Mouse::getPosition(MenuWindow));
		NewGame->update((Vector2f)Mouse::getPosition(MenuWindow));
		OpenOptions->update((Vector2f)Mouse::getPosition(MenuWindow));
		CloseOptions->update((Vector2f)Mouse::getPosition(MenuWindow));
		Quit->update((Vector2f)Mouse::getPosition(MenuWindow));

		if (Character::CheckIFCharacteristicsBelowZero()) LoadSavedGame->setActive(false);
		else LoadSavedGame->setActive(true);

		MenuWindow.clear();

		MenuWindow.draw(BackgroundPicture);
		MenuContainer->render(MenuWindow, Vector2f(0, 0));
		OptionsContainer->render(MenuWindow, Vector2f(0, 0));

		MenuWindow.display();
	}
}