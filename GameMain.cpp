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
#include "Menu.h"
#include "Craft.h"
#include "Label.h"

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

#pragma region OpenInventory

void InventorySetVisible(Container* cont, bool value)
{
	cont->setVisible(value);
}

#pragma endregion

#pragma region Menu

void CallMenu(RenderWindow& window, Menu& obj)
{
	window.create(sf::VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Menu", sf::Style::Fullscreen);
	obj.Draw();
}

#pragma endregion

int main()
{
	const int windowWidth = VideoMode::getDesktopMode().width;
	const int windowHeight = VideoMode::getDesktopMode().height;
	//const int windowWidth = 700;
	//const int windowHeight = 700;

	Menu menuObj;
	menuObj.Draw();

	if (Menu::OpenMainWindow())
	{
		RenderWindow window(sf::VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Game", sf::Style::Fullscreen);

		//RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game" /*, sf::Style::Fullscreen*/);
		Event event;
		Location location;

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
#pragma region StartFire

		Container* StartFireContainer = new Container;
		Panel* StartFirePanel = new Panel(Vector2f(windowWidth / 10, windowHeight / 10), IntRect(0, 0, windowWidth * 0.8, windowHeight * 0.6));
		StartFireContainer->setVisible(false);

		Button<void(*)(Container*, bool)>* StartFire = new Button<void(*)(Container*, bool)>(Vector2f(windowWidth * 0.18, windowHeight * 0.02), IntRect(0, 0, windowWidth * 0.14, windowHeight * 0.07), "Start fire");
		StartFire->setDelegate(ContainerSetVisible);

		Button<void(*)(int)>* StayAtFire = new Button<void(*)(int)>(Vector2f(windowWidth * 0.18, windowHeight * 0.11), IntRect(0, 0, windowWidth * 0.14, windowHeight * 0.07), "Stay at fire");
		StayAtFire->setDelegate(Character::ChangeWarmthLevel);
		StayAtFire->setVisible(false);
		StayAtFire->setActive(false);
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

		Button<void(*)()>* ExploreArea = new Button<void(*)()>(Vector2f(windowWidth * 0.34, windowHeight * 0.02), IntRect(0, 0, windowWidth * 0.14, windowHeight * 0.16), "Explore Area");
		ExploreArea->setDelegate(Inventory::ExploreArea);

#pragma endregion

#pragma region ChooseWhereToGo

		Generator::GenerateEnvironments(3, 3);

		Button<void(*)(int)>* FirstVariantToTravel = new Button<void(*)(int)>(Vector2f(1570, 20), IntRect(0, 0, 100, 100), "Forest");
		FirstVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
		FirstVariantToTravel->setVisible(true);

		Button<void(*)(int)>* SecondVariantToTravel = new Button<void(*)(int)>(Vector2f(1690, 20), IntRect(0, 0, 100, 100), "Lake");
		SecondVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
		SecondVariantToTravel->setVisible(true);

		Button<void(*)(int)>* ThirdVariantToTravel = new Button<void(*)(int)>(Vector2f(1810, 20), IntRect(0, 0, 100, 100), "River");
		ThirdVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
		ThirdVariantToTravel->setVisible(true);

#pragma endregion

#pragma region Hunt

		Container* HuntContainer = new Container;
		Panel* HuntPanel = new Panel(Vector2f(100, 490), IntRect(0, 0, 1040, 380));
		HuntContainer->setVisible(false);

		Button<void(*)(Container*, bool)>* HuntButton = new Button<void(*)(Container*, bool)>(Vector2f(windowWidth * 0.66, windowHeight * 0.02), IntRect(0, 0, windowWidth * 0.14, windowHeight * 0.16), "Hunt");
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

		Button<void(*)(Container*, bool)>* FishButton = new Button<void(*)(Container*, bool)>(Vector2f(windowWidth * 0.66, windowHeight * 0.02), IntRect(0, 0, windowWidth * 0.14, windowHeight * 0.16), "Fish");
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

		Button<void(*)(int)>* RestButton = new Button<void(*)(int)>(Vector2f(windowWidth * 0.5, windowHeight * 0.02), IntRect(0, 0, windowWidth * 0.14, windowHeight * 0.16), "Rest");
		RestButton->setDelegate(Character::Rest);

#pragma endregion

#pragma region OpenInventory

		Container* OpenInventoryContainer = new Container;
		Panel* OpenInventoryPanel = new Panel(Vector2f(windowWidth / 10, windowHeight / 10), IntRect(0, 0, windowWidth * 0.8, windowHeight * 0.6));
		OpenInventoryContainer->setVisible(false);

		Button<void(*)(Container*, bool)>* OpenInventory = new Button<void(*)(Container*, bool)>(Vector2f(windowWidth * 0.02, windowHeight * 0.02), IntRect(0, 0, windowWidth * 0.14, windowHeight * 0.16), "OpenInventory");
		OpenInventory->setDelegate(InventorySetVisible);

		Button<void(*)(Container*, bool)>* CloseInventory = new Button<void(*)(Container*, bool)>(Vector2f(windowWidth * 0.63, windowHeight * 0.47), IntRect(0, 0, windowWidth * 0.15, windowHeight * 0.1), "CloseInventory");
		CloseInventory->setDelegate(InventorySetVisible);
		CloseInventory->setVisible(false);

		OpenInventoryContainer->addChild(OpenInventoryPanel);
		OpenInventoryPanel->addChild(CloseInventory);

#pragma endregion

#pragma region Menu

		Button<void(*)(RenderWindow&, Menu&)>* OpenMenu = new Button<void(*)(RenderWindow&, Menu&)>(Vector2f(1810, 130), IntRect(0, 0, 100, 80), "Open Menu");
		OpenMenu->setDelegate(CallMenu);

#pragma endregion
		Container* MainContainer = new Container;
		Panel* MainPanel = new Panel(Vector2f(0, windowHeight * 0.8), IntRect(0, 0, windowWidth, windowHeight * 0.2));

		MainContainer->addChild(MainPanel);

#pragma region LostTheGame

		Container* FailMenu = new Container;
		Panel* FailPanel = new Panel(Vector2f(windowWidth / 10, windowHeight / 5), IntRect(0, 0, windowWidth * 0.8, windowHeight * 0.3));

		Button<void(*)()>* Restart = new Button<void(*)()>(Vector2f(40, windowHeight / 7), IntRect(0, 0, 200, 100), "Restart");
		Restart->setDelegate(Data::SetDeffaultCharacteristics);

		Button<void(*)(RenderWindow&, Menu&)>* OpenMainMenu = new Button<void(*)(RenderWindow&, Menu&)>(Vector2f(320, windowHeight / 7), IntRect(0, 0, 200, 100), "Menu");
		OpenMainMenu->setDelegate(CallMenu);

		FailMenu->addChild(FailPanel);
		FailPanel->addChild(Restart);
		FailPanel->addChild(OpenMainMenu);
#pragma endregion


#pragma region Craft

		vector<Panel*> craftMenus;
		map<Button<bool(*)(string)>*, string> craftBut;
		vector<Button<void(*)(vector<Panel*>*, Panel*)>*> closeCraftBut;
		map<Button<void(*)(vector<Panel*>*, Panel*)>*, Panel*> switchCraftBut;
		Button<void(*)(vector<Panel*>*, Panel*)>* openCraftBut = new Button<void(*)(vector<Panel*>*, Panel*)>(Vector2f(windowWidth * 0.18, windowHeight * 0.11), IntRect(0, 0, windowWidth * 0.14, windowHeight * 0.07), "Open craft menu");
		openCraftBut->setDelegate(Craft::changeCraftMenu);
		Craft::InitializeCraftMenus(&craftMenus, &craftBut, &closeCraftBut, &switchCraftBut, MainContainer, Vector2f(windowWidth * 0.35, windowHeight * 0.3));
		MainPanel->addChild(openCraftBut);

#pragma endregion 

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

#pragma region OpenInventory

		MainPanel->addChild(OpenInventory);

#pragma endregion

#pragma region Menu

		MainPanel->addChild(OpenMenu);

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
							StayAtFire->Action(minutes * 2);
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

#pragma region OpenInventory

						if (OpenInventory->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							OpenInventory->Action(OpenInventoryContainer, !OpenInventoryContainer->getVisible());
							CloseInventory->setVisible(!CloseInventory->getVisible());
						}
						if (CloseInventory->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							OpenInventory->Action(OpenInventoryContainer, false);
							CloseInventory->setVisible(false);
						}

#pragma endregion

#pragma region LostTheGame

						if (Restart->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							MainContainer->setActive(true);
							HuntContainer->setActive(true);
							FishContainer->setActive(true);
							OpenInventoryContainer->setActive(true);
							StartFireContainer->setActive(true);

							Restart->Action();
						}

#pragma endregion


#pragma region Menu

						if (OpenMenu->checkClick((Vector2f)Mouse::getPosition(window)) || OpenMainMenu->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							Data::SaveAllStaticData();
							window.close();
							OpenMenu->Action(Menu::MenuWindow, menuObj);
							if (Menu::OpenMainWindow()) window.create(sf::VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Game", sf::Style::Fullscreen);
						}

#pragma endregion

#pragma region Craft
						if (openCraftBut->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							openCraftBut->Action(&craftMenus, craftMenus[0]);
						}
						for (map<Button<bool(*)(string)>*, string>::iterator it = craftBut.begin(); it != craftBut.end(); ++it)
						{
							if (it->first->checkClick((Vector2f)Mouse::getPosition(window)))
							{
								if (it->first->Action(it->second))
									cout << "Sucesfully crafted!" << endl;
								else
									cout << "Not enough resources or this tool already exist" << endl;
							}
						}
						for (int i = 0; i < closeCraftBut.size(); i++)
						{
							if (closeCraftBut[i]->checkClick((Vector2f)Mouse::getPosition(window)))
								closeCraftBut[i]->Action(&craftMenus, NULL);
						}
						for (map<Button<void(*)(vector<Panel*>*, Panel*)>*, Panel*>::iterator it = switchCraftBut.begin(); it != switchCraftBut.end(); ++it)
						{
							if (it->first->checkClick((Vector2f)Mouse::getPosition(window)))
							{
								it->first->Action(&craftMenus, it->second);
								break;
							}
						}
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

#pragma region OpenInventory

			OpenInventory->update((Vector2f)Mouse::getPosition(window));
			CloseInventory->update((Vector2f)Mouse::getPosition(window));

#pragma endregion

#pragma region LostTheGame

			Restart->update((Vector2f)Mouse::getPosition(window));
			OpenMainMenu->update((Vector2f)Mouse::getPosition(window));

#pragma endregion		

#pragma region Menu

			OpenMenu->update((Vector2f)Mouse::getPosition(window));

#pragma endregion

#pragma region Craft

			openCraftBut->update((Vector2f)Mouse::getPosition(window));
			for (map<Button<bool(*)(string)>*, string>::iterator it = craftBut.begin(); it != craftBut.end(); ++it)
			{
				it->first->update((Vector2f)Mouse::getPosition(window));
			}
			for (int i = 0; i < closeCraftBut.size(); i++)
			{
				closeCraftBut[i]->update((Vector2f)Mouse::getPosition(window));
			}
			for (map<Button<void(*)(vector<Panel*>*, Panel*)>*, Panel*>::iterator it = switchCraftBut.begin(); it != switchCraftBut.end(); ++it)
			{
				it->first->update((Vector2f)Mouse::getPosition(window));
			}
#pragma endregion

			// Draw
			window.clear();
			window.draw(location.Sprite);

#pragma region StartFire

			if (GeneralTime::DeltaTime(startedDay, startedHour) >= 12) StayAtFire->setVisible(false); // an example; it's not necessary must be 5
			if (StayAtFire->getVisible()) StartFire->setActive(false);
			else StartFire->setActive(true);
			StayAtFire->setActive(true);
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

#pragma region Hunt

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

#pragma endregion

#pragma region OpenInventory

			OpenInventoryContainer->render(window, Vector2f(0, 0));

#pragma endregion
	
			if (Character::CheckIFCharacteristicsBelowZero())
			{
				MainContainer->setActive(false);
				HuntContainer->setActive(false);
				FishContainer->setActive(false);
				OpenInventoryContainer->setActive(false);
				StartFireContainer->setActive(false);
				StayAtFire->setActive(false);

				StayAtFire->setVisible(false);
				Craft::changeCraftMenu(&craftMenus, NULL);
				HuntContainer->setVisible(false);
				OpenInventoryContainer->setVisible(false);
				StartFireContainer->setVisible(false);

				FailMenu->render(window, Vector2f(0, 0));
			}

			Data::SaveGamePerSomeTime(23); // Save data per some time (in hours)

			MainContainer->render(window, Vector2f(0, 0)); // render themself and all ui that contain
			HuntContainer->render(window, Vector2f(0, 0));
			FishContainer->render(window, Vector2f(0, 0));
			OpenInventoryContainer->render(window, Vector2f(0, 0));

#pragma region OpenInventory

			if (OpenInventoryContainer->getVisible())
			{
				Font font;
				font.loadFromFile("CALIBRI.TTF");
				Text Items, Items_Title, Items_Values, Tools, Tools_Title, Tools_Values;

				Items.setFont(font);
				Items_Title.setFont(font);
				Items_Values.setFont(font);
				Tools.setFont(font);
				Tools_Title.setFont(font);
				Tools_Values.setFont(font);

				Items_Title.setString("Items");
				Items.setString("Wood\nFood\nWater\nTinder\nMedicine");
				Items_Values.setString(to_string(Inventory::ReturnNumberOfItems("wood")) + "\n" +
					to_string(Inventory::ReturnNumberOfItems("food")) + "\n" +
					to_string(Inventory::ReturnNumberOfItems("water")) + "\n" +
					to_string(Inventory::ReturnNumberOfItems("tinder")) + "\n" +
					to_string(Inventory::ReturnNumberOfItems("medicine")));
				Tools_Title.setString("Tools");
				Tools.setString("Axe\nFlashlight\nLighter\nFishing rod\nCompass\nMap\nMatches\nLens\nKnife\nRope\nSpear\nSpring trap\nBird trap\nFall trap");
				Tools_Values.setString(to_string(Inventory::Check_Tool("axe")) + "\n" +
					to_string(Inventory::Check_Tool("flashlight")) + "\n" +
					to_string(Inventory::Check_Tool("lighter")) + "\n" +
					to_string(Inventory::Check_Tool("fishing rod")) + "\n" +
					to_string(Inventory::Check_Tool("compass")) + "\n" +
					to_string(Inventory::Check_Tool("map")) + "\n" +
					to_string(Inventory::Check_Tool("matches")) + "\n" +
					to_string(Inventory::Check_Tool("lens")) + "\n" +
					to_string(Inventory::Check_Tool("knife")) + "\n" +
					to_string(Inventory::Check_Tool("rope")) + "\n" +
					to_string(Inventory::Check_Tool("spear")) + "\n" +
					to_string(Inventory::Check_Tool("spring trap")) + "\n" +
					to_string(Inventory::Check_Tool("bird trap")) + "\n" +
					to_string(Inventory::Check_Tool("fall trap")));

				Items_Title.setCharacterSize(windowHeight / 20);
				Items.setCharacterSize(windowHeight / 40);
				Items_Values.setCharacterSize(windowHeight / 40);
				Tools_Title.setCharacterSize(windowHeight / 20);
				Tools.setCharacterSize(windowHeight / 40);
				Tools_Values.setCharacterSize(windowHeight / 40);

				Items_Title.setPosition(windowWidth * 0.5, windowHeight * 1.2 / 10);
				Items.setPosition(windowWidth * 0.5, windowHeight * 2.1 / 10);
				Items_Values.setPosition(windowWidth * 0.6, windowHeight * 2.1 / 10);
				Tools_Title.setPosition(windowWidth * 0.15, windowHeight * 1.2 / 10);
				Tools.setPosition(windowWidth * 0.15, windowHeight * 2.1 / 10);
				Tools_Values.setPosition(windowWidth * 0.27, windowHeight * 2.1 / 10);

				Items_Title.setFillColor(Color::Black);
				Items.setFillColor(Color::Black);
				Items_Values.setFillColor(Color::Black);
				Tools_Title.setFillColor(Color::Black);
				Tools.setFillColor(Color::Black);
				Tools_Values.setFillColor(Color::Black);

				window.draw(Items_Title);
				window.draw(Items);
				window.draw(Items_Values);
				window.draw(Tools_Title);
				window.draw(Tools);
				window.draw(Tools_Values);
			}

#pragma endregion

			window.display();
		}
	}

	// Deleteing dynamic objects

	return 0;
}