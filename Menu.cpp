#include "Menu.h"
RenderWindow Menu::MenuWindow(sf::VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Menu", sf::Style::Fullscreen);
bool Menu::openMainWindow = false;
void ForButtonPlay(bool value)
{
	Data::ReloadAllStaticData();
	Menu::openMainWindow = value;
	Menu::MenuWindow.close();
}
void ForButtonOptions(Container* contObj, bool value)
{
	contObj->setVisible(value);
}
void ForButtonQuit(RenderWindow& window)
{
	Data::SaveAllStaticData();
	window.close();
	Menu::openMainWindow = false;
}
Menu::Menu()
{
	Game::errorTexture.setRepeated(true);
	if (!Game::errorTexture.loadFromFile("Pictures/ErrorTexture.png"))
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
	MenuPanel = new Panel(Vector2f(600, 300), IntRect(0, 0, 640, 480));

	OptionsContainer = new Container;
	OptionsPanel = new Panel(Vector2f(600, 300), IntRect(0, 0, 640, 480));
	OptionsContainer->setVisible(false);

	LoadSavedGame = new Button<void(*)(bool)>(Vector2f(200, 130), IntRect(0, 0, 200, 100), "Load Saved Game");
	LoadSavedGame->setDelegate(ForButtonPlay);

	NewGame = new Button<void(*)(bool)>(Vector2f(200, 10), IntRect(0, 0, 200, 100), "New Game");
	NewGame->setDelegate(ForButtonPlay);

	Options = new Button<void(*)(Container*, bool)>(Vector2f(200, 250), IntRect(0, 0, 200, 100), "Options");
	Options->setDelegate(ForButtonOptions);

	Quit = new Button<void(*)(RenderWindow&)>(Vector2f(200, 370), IntRect(0, 0, 200, 100), "Quit");
	Quit->setDelegate(ForButtonQuit);

	CloseButton = new Button<void(*)(Container*, bool)>(Vector2f(300, 300), IntRect(0, 0, 200, 100), "Close Options");
	CloseButton->setDelegate(ForButtonOptions);

	MenuContainer->addChild(MenuPanel);
	MenuPanel->addChild(LoadSavedGame);
	MenuPanel->addChild(NewGame);
	MenuPanel->addChild(Options);
	MenuPanel->addChild(Quit);

	OptionsContainer->addChild(OptionsPanel);
	OptionsPanel->addChild(CloseButton);
}
void Menu::Draw()
{
	while (MenuWindow.isOpen())
	{
		while (MenuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				MenuWindow.close();
				break;
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (LoadSavedGame->checkClick((Vector2f)Mouse::getPosition(MenuWindow)))	LoadSavedGame->Action(true);
					if (NewGame->checkClick((Vector2f)Mouse::getPosition(MenuWindow)))
					{
						Data::ForbidDataReloading();
						NewGame->setActive(false);
						NewGame->Action(true);
					}
					if (Options->checkClick((Vector2f)Mouse::getPosition(MenuWindow))) Options->Action(OptionsContainer, !OptionsContainer->getVisible());
					if (Quit->checkClick((Vector2f)Mouse::getPosition(MenuWindow))) Quit->Action(MenuWindow);
					if (CloseButton->checkClick((Vector2f)Mouse::getPosition(MenuWindow))) CloseButton->Action(OptionsContainer, false);

				}break;
			}
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel);
			else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel);
		}
		LoadSavedGame->update((Vector2f)Mouse::getPosition(MenuWindow));
		NewGame->update((Vector2f)Mouse::getPosition(MenuWindow));
		Options->update((Vector2f)Mouse::getPosition(MenuWindow));
		Quit->update((Vector2f)Mouse::getPosition(MenuWindow));

		MenuWindow.clear();

		MenuContainer->render(MenuWindow, Vector2f(0, 0));
		OptionsContainer->render(MenuWindow, Vector2f(0, 0));

		MenuWindow.display();
	}
}