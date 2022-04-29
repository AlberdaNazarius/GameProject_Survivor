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

#pragma region ChooseWhereToGo

string CaptionOfButton(int index)
{
	if (Data::GetEnvironment(index) == 1) return "Forest";
	if (Data::GetEnvironment(index) == 2) return "Lake";
	if (Data::GetEnvironment(index) == 3) return "River";
}

#pragma endregion

#pragma region Hunt

void HuntOveriwrite(int maxIndex, int spentEnergy, int indexOfEnvironment)
{
	srand(time(0));
	int randValue = rand() % 2;
	int minutes = 10 + rand() % 51;
	Character::ChangeEnergyLevel(spentEnergy);
	GeneralTime::AddTime(0, minutes);
	Character::ChangeHungerLevel(-10 * minutes / 60);
	Character::ChangeThirstLevel(-15 * minutes / 60);
	if (randValue)
	{
		Character::ChangeConditionLevel(-5);
		cout << "You were bitten by snake" << endl;
	}// because of beating by snake etc.
	randValue = rand() % 3;
	if (randValue)
	{
		if (indexOfEnvironment == 1)
		{
			Forest forest;
			Inventory::Change_Item("food", forest.Hunt(maxIndex)->first);
		}
		if (indexOfEnvironment == 2)
		{
			Lake lake;
			Inventory::Change_Item("food", lake.Hunt(maxIndex)->first);
		}
		if (indexOfEnvironment == 3)
		{
			River river;
			Inventory::Change_Item("food", river.Hunt(maxIndex)->first);
		}
	}
	else cout << "It's nothing hunted" << endl;
	Character::DisplayCharacteristics();
}

#pragma endregion

#pragma region StartFire

template <typename T>
void ButtonSetVisible(Button<T>* button, Container* cont, bool value, int minutes, int takenEnergy)
{
	button->setVisible(value);
	cont->setVisible(!value);
	GeneralTime::AddTime(0, minutes);
	Character::ChangeEnergyLevel(takenEnergy);
	Character::ChangeHungerLevel(-10 * minutes / 60);
	Character::ChangeThirstLevel(-15 * minutes / 60);
	Character::DisplayCharacteristics();
}
void ContainerSetVisible(Container* cont, bool value)
{
	cont->setVisible(value);
}

#pragma endregion

int main()
{
	const int windowWidth = 1280;
	const int windowHeight = 920;
	RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game"/*, sf::Style::Fullscreen */);
	Event event;
	Location location;
	location.SetWindowResolution(windowWidth, windowHeight);
	
	Data::ReloadAllStaticData();

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

	Container* StartFireContainer = new Container;
	Panel* StartFirePanel = new Panel(Vector2f(100, 490), IntRect(0, 0, 1040, 380));
	StartFireContainer->setVisible(false);

	Button<void(*)(Container*, bool)>* StartFire = new Button<void(*)(Container*, bool)>(Vector2f(40, 200), IntRect(0, 0, 200, 100), "Start fire");
	StartFire->setDelegate(ContainerSetVisible);

	Button<void(*)(int)>* StayAtFire = new Button<void(*)(int)>(Vector2f(260, 200), IntRect(0, 0, 128, 200), "Stay at fire");
	StayAtFire->setDelegate(Character::ChangeWarmthLevel);
	StayAtFire->setVisible(false);
	int startedHour = 0;
	int startedDay = 0;

	Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int)>* FireLighter = new Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int)>(Vector2f(10, 10), IntRect(0, 0, 150, 100), "Lighter");
	FireLighter->setDelegate(ButtonSetVisible);

	Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int)>* FireStone = new Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int)>(Vector2f(170, 10), IntRect(0, 0, 150, 100), "Flint and Stone");
	FireStone->setDelegate(ButtonSetVisible);

	Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int)>* FireMatches = new Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int)>(Vector2f(340, 10), IntRect(0, 0, 150, 100), "Matches");
	FireMatches->setDelegate(ButtonSetVisible);

	Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int)>* FireBow = new Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int) >(Vector2f(490, 10), IntRect(0, 0, 150, 100), "Bow method");
	FireBow->setDelegate(ButtonSetVisible);

	Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int)>* FireLens = new Button<void(*)(Button<void(*)(int)>*, Container*, bool, int, int)>(Vector2f(660, 510), IntRect(0, 0, 150, 100), "Lens");
	FireLens->setDelegate(ButtonSetVisible);

	StartFireContainer->addChild(StartFirePanel);

	StartFirePanel->addChild(FireStone);
	StartFirePanel->addChild(FireBow);
    StartFirePanel->addChild(FireLighter);
	StartFirePanel->addChild(FireLens);
	StartFirePanel->addChild(FireMatches);

	if (!Inventory::Check_Tool("lighter")) FireLighter->setVisible(false);
	if (!Inventory::Check_Tool("lens")) FireLens->setVisible(false);
	if (!Inventory::Check_Tool("matches")) FireMatches->setVisible(false);

#pragma endregion 

#pragma region ExploreArea

	Button<void(*)()>* ExploreArea = new Button<void(*)()>(Vector2f(400, 200), IntRect(0, 0, 200, 100), "Explore Area");
	ExploreArea->setDelegate(Inventory::ExploreArea);

#pragma endregion

#pragma region ChooseWhereToGo

	Generator::GenerateEnvironments(3, 3);

	Button<void(*)(int)>* FirstVariantToTravel = new Button<void(*)(int)>(Vector2f(20, 20), IntRect(0, 0, 150, 100), "Forest");
	FirstVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
	FirstVariantToTravel->setVisible(true);

	Button<void(*)(int)>* SecondVariantToTravel = new Button<void(*)(int)>(Vector2f(190, 20), IntRect(0, 0, 150, 100), "Lake");
	SecondVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
	SecondVariantToTravel->setVisible(true);

	Button<void(*)(int)>* ThirdVariantToTravel = new Button<void(*)(int)>(Vector2f(360, 20), IntRect(0, 0, 150, 100), "River");
	ThirdVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
	ThirdVariantToTravel->setVisible(true);

#pragma endregion

#pragma region Hunt

	Container* HuntContainer = new Container;
	Panel* HuntPanel = new Panel(Vector2f(100, 490), IntRect(0, 0, 1040, 380));
	HuntContainer->setVisible(false);

	Button<void(*)(Container*, bool)>* HuntButton = new Button<void(*)(Container*, bool)>(Vector2f(40, 310), IntRect(0, 0, 200, 100), "Hunt");
	HuntButton->setDelegate(ContainerSetVisible);

	Button<void(*)(int, int, int)>* FallTrap = new Button<void(*)(int, int, int)>(Vector2f(40, 40), IntRect(0, 0, 200, 100), "Fall Trap");
	FallTrap->setDelegate(HuntOveriwrite);

	Button<void(*)(int, int, int)>* SpringTrap = new Button<void(*)(int, int, int)>(Vector2f(250, 40), IntRect(0, 0, 200, 100), "Spring Trap");
	SpringTrap->setDelegate(HuntOveriwrite);

	Button<void(*)(int, int, int)>* BirdTrap = new Button<void(*)(int, int, int)>(Vector2f(460, 40), IntRect(0, 0, 200, 100), "Birs Trap");
	BirdTrap->setDelegate(HuntOveriwrite);

	HuntContainer->addChild(HuntPanel);

	HuntPanel->addChild(FallTrap);
	HuntPanel->addChild(SpringTrap);
	HuntPanel->addChild(BirdTrap);

	if (!Inventory::Check_Tool("fall trap")) FallTrap->setVisible(false);
	if (!Inventory::Check_Tool("spring trap")) SpringTrap->setVisible(false);
	if (!Inventory::Check_Tool("bird trap")) BirdTrap->setVisible(false);

	Container* FishContainer = new Container;
	Panel* FishPanel = new Panel(Vector2f(100, 490), IntRect(0, 0, 1040, 380));
	FishContainer->setVisible(false);

	Button<void(*)(Container*, bool)>* FishButton = new Button<void(*)(Container*, bool)>(Vector2f(40, 310), IntRect(0, 0, 200, 100), "Fish");
	FishButton->setDelegate(ContainerSetVisible);

	Button<void(*)(int, int, int)>* FishingRod = new Button<void(*)(int, int, int)>(Vector2f(40, 40), IntRect(0, 0, 200, 100), "Fishing Rod");
	FishingRod->setDelegate(HuntOveriwrite);

	Button<void(*)(int, int, int)>* SpearFishing = new Button<void(*)(int, int, int)>(Vector2f(250, 40), IntRect(0, 0, 200, 100), "Spear Fishing");
	SpearFishing->setDelegate(HuntOveriwrite);

	FishContainer->addChild(FishPanel);

	FishPanel->addChild(FishingRod);
	FishPanel->addChild(SpearFishing);

	if (!Inventory::Check_Tool("fishing rod")) FishingRod->setVisible(false);
	if (!Inventory::Check_Tool("spear")) SpearFishing->setVisible(false);

#pragma endregion

#pragma region Rest

	Button<void(*)(int)>* RestButton = new Button<void(*)(int)>(Vector2f(400, 310), IntRect(0, 0, 200, 100), "Rest");
	RestButton->setDelegate(Character::Rest);    

#pragma endregion

	Container* MainContainer = new Container;
	Panel* MainPanel = new Panel(Vector2f(300, 10), IntRect(0, 0, 640, 480));

	MainContainer->addChild(MainPanel);

#pragma region StartFire

	MainPanel->addChild(StayAtFire);
	MainPanel->addChild(StartFire);

#pragma endregion 

#pragma region ExploreArea

	MainPanel->addChild(ExploreArea);

#pragma endregion

#pragma region ChooseWhereToGo

	MainPanel->addChild(FirstVariantToTravel);
	MainPanel->addChild(SecondVariantToTravel);
	MainPanel->addChild(ThirdVariantToTravel);

#pragma endregion

#pragma region Hunt

	MainPanel->addChild(HuntButton);
	MainPanel->addChild(FishButton);

#pragma endregion

#pragma region Rest

	MainPanel->addChild(RestButton);

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
				Data::SaveAllStaticData();
				window.close();
				break;

			case Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
#pragma region StartFire

					if (StartFire->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						StartFire->Action(StartFireContainer, true);
						Inventory::Change_Item("wood", -5);
						startedHour = GeneralTime::GetHours();
						startedDay = GeneralTime::GetDay();
					}
					if (FireLighter->checkClick((Vector2f)Mouse::getPosition(window))) FireLighter->Action(StayAtFire, StartFireContainer, true, 5, -3);
					if (FireStone->checkClick((Vector2f)Mouse::getPosition(window)))  FireStone->Action(StayAtFire, StartFireContainer, true, 40, -20);
					if (FireMatches->checkClick((Vector2f)Mouse::getPosition(window)))  FireMatches->Action(StayAtFire, StartFireContainer, true, 5, -5);
					if (FireBow->checkClick((Vector2f)Mouse::getPosition(window)))  FireBow->Action(StayAtFire, StartFireContainer, true, 60, -25);
					if (FireLens->checkClick((Vector2f)Mouse::getPosition(window)))  FireLens->Action(StayAtFire, StartFireContainer, true, 30, -15);
					if (StayAtFire->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						int minutes = 60;
						GeneralTime::AddTime(0, minutes);
						Character::ChangeHungerLevel(minutes / 60 * -10);
						Character::ChangeThirstLevel(minutes / 60 * -15);
						StayAtFire->Action(minutes*2);
						Character::DisplayCharacteristics();
					}

#pragma endregion 

#pragma region ExploreArea

					if (ExploreArea->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						ExploreArea->Action();
						ExploreArea->setActive(false); // it becomes active with changing location;
						FirstVariantToTravel->setText(CaptionOfButton(0));
						SecondVariantToTravel->setText(CaptionOfButton(1));
						ThirdVariantToTravel->setText(CaptionOfButton(2));
					}

#pragma endregion

#pragma region ChooseWhereToGo

					if (FirstVariantToTravel->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						srand(time(0));
						int posibilityOfBeingHurted = rand() % 2;
						FirstVariantToTravel->Action(Data::GetEnvironment(0));
						Location::LocationCurrent = Data::GetEnvironment(0);
						Character::ChangeEnergyLevel(-15);
						GeneralTime::AddTime(1, 0);
						Character::ChangeHungerLevel(-10);
						Character::ChangeThirstLevel(-15);
						if (posibilityOfBeingHurted)
						{
							Character::ChangeConditionLevel(-5);
							cout << "You were hurted during travelling" << endl;
						}
						Character::DisplayCharacteristics();
						ExploreArea->setActive(true);
						StayAtFire->setVisible(false);
					}
					if (SecondVariantToTravel->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						srand(time(0));
						int posibilityOfBeingHurted = rand() % 2;
						SecondVariantToTravel->Action(Data::GetEnvironment(1));
						Location::LocationCurrent = Data::GetEnvironment(1);
						Character::ChangeEnergyLevel(-15);
						GeneralTime::AddTime(1, 0);
						Character::ChangeHungerLevel(-10);
						Character::ChangeThirstLevel(-15);
						if (posibilityOfBeingHurted)
						{
							Character::ChangeConditionLevel(-5);
							cout << "You were hurted during travelling" << endl;
						}
						Character::DisplayCharacteristics();
						ExploreArea->setActive(true);
						StayAtFire->setVisible(false);
					}
					if (ThirdVariantToTravel->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						srand(time(0));
						int posibilityOfBeingHurted = rand() % 2;
						ThirdVariantToTravel->Action(Data::GetEnvironment(2));
						Location::LocationCurrent = Data::GetEnvironment(2);
						Character::ChangeEnergyLevel(-15);
						GeneralTime::AddTime(1, 0);
						Character::ChangeHungerLevel(-10);
						Character::ChangeThirstLevel(-15);
						if (posibilityOfBeingHurted)
						{
							Character::ChangeConditionLevel(-5);
							cout << "You were hurted during travelling" << endl;
						}
						Character::DisplayCharacteristics();
						ExploreArea->setActive(true);
						StayAtFire->setVisible(false);
					}

#pragma endregion

#pragma region Hunt

					if (HuntButton->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						HuntButton->Action(HuntContainer, true);
						FishButton->Action(FishContainer, false);
					}
					if (FallTrap->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						Inventory::Change_Item("fall trap", 0);
						FallTrap->Action(3, -5, Location::LocationCurrent);
						HuntContainer->setVisible(false);
					}
					if (SpringTrap->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						Inventory::Change_Item("spring trap", 0);
						SpringTrap->Action(3, -5, Location::LocationCurrent);
						HuntContainer->setVisible(false);
					}
					if (BirdTrap->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						Inventory::Change_Item("bird trap", 0);
						BirdTrap->Action(15, -5, Location::LocationCurrent);
						HuntContainer->setVisible(false);
					}
					if (FishButton->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						FishButton->Action(FishContainer, true);
						HuntButton->Action(HuntContainer, false);
					}
					if (FishingRod->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						FishingRod->Action(5, -7, Location::LocationCurrent);
						FishContainer->setVisible(false);
					}
					if (SpearFishing->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						SpearFishing->Action(2, -10, Location::LocationCurrent);
						FishContainer->setVisible(false);
					}

#pragma endregion

#pragma region Rest

					if (RestButton->checkClick((Vector2f)Mouse::getPosition(window))) RestButton->Action(4);

#pragma endregion 

#pragma endregion
				}
				break;
			}
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel);
			else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel);
		}
		// Update 

#pragma region StartFire

		FireLighter->update((Vector2f)Mouse::getPosition(window));
		FireBow->update((Vector2f)Mouse::getPosition(window));
		FireMatches->update((Vector2f)Mouse::getPosition(window));
		FireLens->update((Vector2f)Mouse::getPosition(window));
		FireStone->update((Vector2f)Mouse::getPosition(window));
		StayAtFire->update((Vector2f)Mouse::getPosition(window));
	 	StartFire->update((Vector2f)Mouse::getPosition(window));

#pragma endregion 

#pragma region ExploreArea

		ExploreArea->update((Vector2f)Mouse::getPosition(window));

#pragma endregion

#pragma region ChooseWhereToGo

		FirstVariantToTravel->update((Vector2f)Mouse::getPosition(window));
		SecondVariantToTravel->update((Vector2f)Mouse::getPosition(window));
		ThirdVariantToTravel->update((Vector2f)Mouse::getPosition(window));

#pragma endregion

#pragma region Hunt

		HuntButton->update((Vector2f)Mouse::getPosition(window));
		FallTrap->update((Vector2f)Mouse::getPosition(window));
		SpringTrap->update((Vector2f)Mouse::getPosition(window));
		BirdTrap->update((Vector2f)Mouse::getPosition(window));
		FishButton->update((Vector2f)Mouse::getPosition(window));
		FishingRod->update((Vector2f)Mouse::getPosition(window));
		SpearFishing->update((Vector2f)Mouse::getPosition(window));

#pragma endregion

#pragma region Rest

		RestButton->update((Vector2f)Mouse::getPosition(window));

#pragma endregion

		// Draw
		window.clear();
		window.draw(location.Sprite);

#pragma region StartFire

		if (GeneralTime::DeltaTime(startedDay, startedHour) == 12) StayAtFire->setVisible(false); // an example; it's not necessary must be 5
		if (StayAtFire->getVisible()) StartFire->setActive(false);
		else StartFire->setActive(true);
		StartFireContainer->render(window, Vector2f(0, 0));

#pragma endregion 

#pragma region ExploreArea

		if (ExploreArea->getActive())
		{
			FirstVariantToTravel->setVisible(false);
			SecondVariantToTravel->setVisible(false);
			ThirdVariantToTravel->setVisible(false);
		}
		else
		{
			FirstVariantToTravel->setVisible(true);
			SecondVariantToTravel->setVisible(true);
			ThirdVariantToTravel->setVisible(true);
		}

#pragma endregion

		if (Location::LocationCurrent != 1)
		{
			HuntButton->setVisible(false);
			FishButton->setVisible(true);
		}
		if (Location::LocationCurrent == 1)
		{
			FishButton->setVisible(false);
			HuntButton->setVisible(true);
		}

		MainContainer->render(window, Vector2f(0, 0)); // render themself and all ui that contain
		HuntContainer->render(window, Vector2f(0, 0));
		FishContainer->render(window, Vector2f(0, 0));
		window.display();
	}

	// Deleteing dynamic objects

	return 0;
}