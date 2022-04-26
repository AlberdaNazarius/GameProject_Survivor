#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Location.h"
#include "Game.h"
#include "Button.h"
#include "Data.h"
#include "Character.h"
#include "UI.h"
#include "Container.h"
#include "Panel.h"
#include "Inventory.h"

using namespace sf;
using namespace std;

///* delete this after test
void testF()
{
	std::cout << "abcd";
}
//*/

#pragma region ChooseWhereToGo

//string CaptionOfButton(int index)
//{
//	if (Data::GetEnvironment(index) == 1) return "Forest";
//	if (Data::GetEnvironment(index) == 2) return "Lake";
//	if (Data::GetEnvironment(index) == 3) return "River";
//}

#pragma endregion

#pragma region StartFire

//template <typename T>
//void ButtonSetVisible(Button<T>* button, Container* cont, bool value)
//{
//	button->setVisible(value);
//	cont->setVisible(!value); 
//}
//void ContainerSetVisible(Container*  cont, bool value)
//{
//	cont->setVisible(value);
//}

#pragma endregion

int main()
{
	const int windowWidth = 1280;
	const int windowHeight = 920;
	RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game"/*, sf::Style::Fullscreen */);
	Event event;
	Location location;
	location.SetWindowResolution(windowWidth, windowHeight);

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
	
#pragma region StartFire

	//Container* StartFireContainer = new Container;
	//Panel* StartFirePanel = new Panel(Vector2f(100, 490), IntRect(0, 0, 1040, 380));
	//StartFireContainer->setVisible(false);

	//Button<void(*)(Container*, bool)>* StartFire = new Button<void(*)(Container*, bool)>(Vector2f(40, 40), IntRect(0, 0, 200, 100), "Start fire");
	//StartFire->setDelegate(ContainerSetVisible);

	//Button<void(*)(int)>* StayAtFire = new Button<void(*)(int)>(Vector2f(260, 40), IntRect(0, 0, 200, 100), "Stay at fire");
	//StayAtFire->setDelegate(Character::ChangeWarmthLevel);
	//StayAtFire->setVisible(false);
	//int startedHour = 0;
	//int startedDay = 0;


	//Button<void(*)(Button<void(*)(int)>*, Container*, bool)>* FireLighter = new Button<void(*)(Button<void(*)(int)>*, Container*, bool)>(Vector2f(10, 10), IntRect(0, 0, 150, 100), "Lighter");
	//FireLighter->setDelegate(ButtonSetVisible);

	//Button<void(*)(Button<void(*)(int)>*, Container*, bool)>* FireStone = new Button<void(*)(Button<void(*)(int)>*, Container*, bool)>(Vector2f(170, 10), IntRect(0, 0, 150, 100), "Flint and Stone");
	//FireStone->setDelegate(ButtonSetVisible);

	//Button<void(*)(Button<void(*)(int)>*, Container*, bool)>* FireMatches = new Button<void(*)(Button<void(*)(int)>*, Container*, bool)>(Vector2f(340, 10), IntRect(0, 0, 150, 100), "Matches");
	//FireMatches->setDelegate(ButtonSetVisible);

	//Button<void(*)(Button<void(*)(int)>*, Container*, bool)>* FireBow = new Button<void(*)(Button<void(*)(int)>*, Container*, bool) >(Vector2f(490, 10), IntRect(0, 0, 150, 100), "Bow method");
	//FireBow->setDelegate(ButtonSetVisible);

	//Button<void(*)(Button<void(*)(int)>*, Container*, bool)>* FireLens = new Button<void(*)(Button<void(*)(int)>*, Container*, bool)>(Vector2f(660, 510), IntRect(0, 0, 150, 100), "Lens");
	//FireLens->setDelegate(ButtonSetVisible);

	//StartFireContainer->addChild(StartFirePanel);

	//StartFirePanel->addChild(FireStone);
	//StartFirePanel->addChild(FireBow);
 //   StartFirePanel->addChild(FireLighter);
	//StartFirePanel->addChild(FireLens);
	//StartFirePanel->addChild(FireMatches);

	//if (!Inventory::Check_Tool("lighter")) FireLighter->setVisible(false);
	//if (!Inventory::Check_Tool("lens")) FireLens->setVisible(false);
	//if (!Inventory::Check_Tool("matches")) FireMatches->setVisible(false);

#pragma endregion 

#pragma region ExploreArea
    
	Button<void(*)()>* ExploreArea = new Button<void(*)()>(Vector2f(100, 200), IntRect(0, 0, 200, 100), "Explore Area");
	ExploreArea->setDelegate(Inventory::ExploreArea);

#pragma endregion


#pragma region ChooseWhereToGo

	//Generator::GenerateEnvironments(2, 3);

	//Button<void(*)(int)>* FirstVariantToTravel = new Button<void(*)(int)>(Vector2f(20, 20), IntRect(0, 0, 150, 100), CaptionOfButton(0));
	//FirstVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
	//FirstVariantToTravel->setVisible(false);

	//Button<void(*)(int)>* SecondVariantToTravel = new Button<void(*)(int)>(Vector2f(190, 20), IntRect(0, 0, 150, 100), CaptionOfButton(1));
	//SecondVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
	//SecondVariantToTravel->setVisible(false);

	//Button<void(*)(int)>* ThirdVariantToTravel = new Button<void(*)(int)>(Vector2f(360, 20), IntRect(0, 0, 150, 100), CaptionOfButton(2));
	//ThirdVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
	//ThirdVariantToTravel->setVisible(false);

#pragma endregion

	Button<void(*)()>* testButton = new Button<void(*)()>(Vector2f(400, 200), IntRect(0, 0, 128, 200), "ABC");
	testButton->setDelegate(testF);      // test

	Container* uiContainer = new Container;
	Panel* testPanel = new Panel(Vector2f(300,10), IntRect(0, 0, 640, 480));

	uiContainer->addChild(testPanel);

	testPanel->addChild(testButton);

#pragma region StartFire
	//testPanel->addChild(StayAtFire);
	//testPanel->addChild(StartFire);
#pragma endregion 

#pragma region ExploreArea

	//testPanel->addChild(ExploreArea);

#pragma endregion

#pragma region ChooseWhereToGo

	//testPanel->addChild(FirstVariantToTravel);
	//testPanel->addChild(SecondVariantToTravel);
	//testPanel->addChild(ThirdVariantToTravel);

#pragma endregion

	// Attaching pictures to environments
	Forest::SetPicture("Pictures/Environment.jpg");
	Lake::SetPicture("Pictures/Lake.jpg");
	
	//Main cycle
	while (window.isOpen())
	{
		// Event
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close(); // need to save game here
				break;
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (testButton->checkClick((Vector2f)Mouse::getPosition(window))) testButton->Action();
#pragma region StartFire
					//if (StartFire->checkClick((Vector2f)Mouse::getPosition(window)))
					//{
					//	StartFire->Action(StartFireContainer, true);
					//	startedHour = GeneralTime::GetHours();
					//	startedDay = GeneralTime::GetDay();
					//}
					//if (FireLighter->checkClick((Vector2f)Mouse::getPosition(window)))  FireLighter->Action(StayAtFire, StartFireContainer, true);
					//if (FireStone->checkClick((Vector2f)Mouse::getPosition(window)))  FireStone->Action(StayAtFire, StartFireContainer, true);
					//if (FireMatches->checkClick((Vector2f)Mouse::getPosition(window)))  FireMatches->Action(StayAtFire, StartFireContainer, true);
					//if (FireBow->checkClick((Vector2f)Mouse::getPosition(window)))  FireBow->Action(StayAtFire, StartFireContainer, true);
					//if (FireLens->checkClick((Vector2f)Mouse::getPosition(window)))  FireLens->Action(StayAtFire, StartFireContainer, true);
					//if (StayAtFire->checkClick((Vector2f)Mouse::getPosition(window))) StayAtFire->Action(10);
#pragma endregion 

#pragma region ExploreArea

					//if (ExploreArea->checkClick((Vector2f)Mouse::getPosition(window)))
					//{
					//	ExploreArea->Action();
					//	ExploreArea->setActive(false); // it becomes active with changing location;
					//	FirstVariantToTravel->setVisible(true);
					//	SecondVariantToTravel->setVisible(true);
					//	ThirdVariantToTravel->setVisible(true);
					//	FirstVariantToTravel->setText(CaptionOfButton(0));
					//	SecondVariantToTravel->setText(CaptionOfButton(1));
					//	ThirdVariantToTravel->setText(CaptionOfButton(2));
					//}

#pragma endregion

#pragma region ChooseWhereToGo

					//if (FirstVariantToTravel->checkClick((Vector2f)Mouse::getPosition(window)))
					//{
					//	FirstVariantToTravel->Action(Data::GetEnvironment(0));
					//	ExploreArea->setActive(true);
					//}
					//if (SecondVariantToTravel->checkClick((Vector2f)Mouse::getPosition(window)))
					//{
					//	SecondVariantToTravel->Action(Data::GetEnvironment(1));
					//	ExploreArea->setActive(true);
					//}
					//if (ThirdVariantToTravel->checkClick((Vector2f)Mouse::getPosition(window)))
					//{
					//	ThirdVariantToTravel->Action(Data::GetEnvironment(2));
					//	ExploreArea->setActive(true);
					//}

#pragma endregion
				}
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::A:
					uiContainer->setVisible(!uiContainer->getVisible());	// test
					break;
				case Keyboard::B:
					testButton->setVisible(!testButton->getVisible());		// test
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel);
			else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel);
		}
		// Update
		testButton->update((Vector2f)Mouse::getPosition(window));

#pragma region StartFire

		//FireLighter->update((Vector2f)Mouse::getPosition(window));
		//FireBow->update((Vector2f)Mouse::getPosition(window));
		//FireMatches->update((Vector2f)Mouse::getPosition(window));
		//FireLens->update((Vector2f)Mouse::getPosition(window));
		//FireStone->update((Vector2f)Mouse::getPosition(window));
		//StayAtFire->update((Vector2f)Mouse::getPosition(window));
	 //	StartFire->update((Vector2f)Mouse::getPosition(window));

#pragma endregion 

#pragma region ExploreArea

	//	ExploreArea->update((Vector2f)Mouse::getPosition(window));

#pragma endregion

#pragma region ChooseWhereToGo

		//FirstVariantToTravel->update((Vector2f)Mouse::getPosition(window));
		//SecondVariantToTravel->update((Vector2f)Mouse::getPosition(window));
		//ThirdVariantToTravel->update((Vector2f)Mouse::getPosition(window));

#pragma endregion

		// Draw
		window.clear();
		window.draw(location.Sprite);

#pragma region StartFire
		//if (GeneralTime::DeltaTime(startedDay, startedHour) == 5) StayAtFire->setVisible(false); // an example; it's not necessary must be 5
		//if (StayAtFire->getVisible()) StartFire->setActive(false);
		//StartFireContainer->render(window, Vector2f(0, 0));
#pragma endregion 

		uiContainer->render(window, Vector2f(0, 0)); // render themself and all ui that contain
		window.display();
	}

	// Deleteing dynamic objects

	return 0;
}