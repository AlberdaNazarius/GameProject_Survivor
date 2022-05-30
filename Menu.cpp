#include "Menu.h"
#include "Character.h"
#include <ctime>

RenderWindow Menu::MenuWindow(sf::VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Menu"/*, sf::Style::Fullscreen*/);

Texture BackgroundTexture;
Sprite BackgroundPicture;
bool Menu::openMainWindow = false;

void ForButtonPlay(bool value)
{
	Menu::openMainWindow = value;
	Menu::MenuWindow.close();
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

	NewGame = new Button<void(*)(bool)>(Vector2f(MenuPanel->getWidth() / 3.76, MenuPanel->getHeight() / 16), Vector2f(MenuPanel->getWidth() / 2.1, MenuPanel->getHeight() / 4.8), "New Game");
	NewGame->setDelegate(ForButtonPlay);

	LoadSavedGame = new Button<void(*)(bool)>(Vector2f(MenuPanel->getWidth() / 3.76, MenuPanel->getHeight()/2.53), Vector2f(MenuPanel->getWidth() / 2.1, MenuPanel->getHeight() / 4.8), "Load Saved Game");
	LoadSavedGame->setDelegate(ForButtonPlay);
	Data::ReloadAllStaticData();
	if (Character::CheckIFCharacteristicsBelowZero()) LoadSavedGame->setActive(false);
	else LoadSavedGame->setActive(true);

	Quit = new Button<void(*)(RenderWindow&)>(Vector2f(MenuPanel->getWidth() / 3.76, MenuPanel->getHeight() / 1.37), Vector2f(MenuPanel->getWidth() / 2.1, MenuPanel->getHeight() / 4.8), "Quit");
	Quit->setDelegate(ForButtonQuit);

	MenuContainer->addChild(MenuPanel);
	MenuPanel->addChild(LoadSavedGame);
	MenuPanel->addChild(NewGame);
	MenuPanel->addChild(Quit);
}
Menu::~Menu()
{
	delete MenuContainer;
	delete MenuPanel;
	delete NewGame;
	delete LoadSavedGame;
	delete Quit;
}
void Menu::Draw()
{
	Forest::SetPicture("Pictures/Environments/Forest.png");
	Lake::SetPicture("Pictures/Environments/Lake.png");
	River::SetPicture("Pictures/Environments/River.png");
	while (MenuWindow.isOpen())
	{
		while (MenuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (NewGame->checkClick((Vector2f)Mouse::getPosition(MenuWindow)))
					{
						cout << "NewGame->checkClick() == true" << endl;
						srand(time(0));
						Data::SetDeffaultCharacteristics();
						Generator::GenerateEnvironments(3, 3);
						Location::LocationCurrent = Data::GetEnvironment(0);
						Location::CheckWhatEnvironment(Location::LocationCurrent);
						NewGame->Action(true);
						cout << "Data::SetDeffaultCharacteristics();\nGenerator::GenerateEnvironments(3, 3);" << endl;
						cout << "________________________________________" << endl;
					}
					if (LoadSavedGame->checkClick((Vector2f)Mouse::getPosition(MenuWindow)))
					{
						cout << "LoadSavedGame->checkClick() == true" << endl;
						Data::ReloadAllStaticData();
						Location::CheckWhatEnvironment(Location::LocationCurrent);
						LoadSavedGame->Action(true);
						cout << "Data::ReloadAllStaticData();" << endl;
						cout << "________________________________________" << endl;
					}
					if (Quit->checkClick((Vector2f)Mouse::getPosition(MenuWindow))) Quit->Action(MenuWindow);
				}
				break;
			}
		}
		NewGame->update((Vector2f)Mouse::getPosition(MenuWindow));
		LoadSavedGame->update((Vector2f)Mouse::getPosition(MenuWindow));
		Quit->update((Vector2f)Mouse::getPosition(MenuWindow));

		if (Character::CheckIFCharacteristicsBelowZero()) LoadSavedGame->setActive(false);
		else LoadSavedGame->setActive(true);

		MenuWindow.clear();

		MenuWindow.draw(BackgroundPicture);
		MenuContainer->render(MenuWindow, Vector2f(0, 0));

		MenuWindow.display();
	}
}