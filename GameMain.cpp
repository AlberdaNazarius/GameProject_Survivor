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
#include "Bar.h"

using namespace sf;
using namespace std;

enum Bars
{
	HungerBar,
	ThirstBar,
	WarmthBar,
	EnergyBar,
	ConditionBar
};
Text eventsDescription;

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
	map<int, string>::iterator it;
	srand(time(0));
	int randValue = rand() % 2;
	int minutes = 10 + rand() % 51;
	Character::ChangeEnergyLevel(spentEnergy);
	GeneralTime::AddTime(0, minutes);
	Character::ChangeHungerLevel(-10 * minutes / 60);
	Character::ChangeThirstLevel(-15 * minutes / 60);
	eventsDescription.setString("Energy-" + to_string(spentEnergy) + "\nHunger-" + to_string(-10 * minutes / 60) + "\nThirst-" + to_string(-15 * minutes / 60));
	if (randValue)
	{
		Character::ChangeConditionLevel(-5);
		eventsDescription.setString("You were bitten by snake\nCondition-5\nEnergy-" + to_string(spentEnergy) + "\nHunger-" + to_string(-10 * minutes / 60) + "\nThirst-" + to_string(-15 * minutes / 60));

	}// because of beating by snake etc.
	randValue = rand() % 3;
	if (randValue)
	{
		if (indexOfEnvironment == 1)
		{
			Forest forest;
			it = forest.Hunt(maxIndex);
			Inventory::Change_Item("food", it->first);
			eventsDescription.setString(it->second+"\nEnergy-" + to_string(spentEnergy) + "\nHunger-" + to_string(-10 * minutes / 60) + "\nThirst-" + to_string(-15 * minutes / 60));
		}
		if (indexOfEnvironment == 2)
		{
			Lake lake;
			it = lake.Hunt(maxIndex);
			Inventory::Change_Item("food", it->first);
			eventsDescription.setString(it->second + "\nEnergy-" + to_string(spentEnergy) + "\nHunger-" + to_string(-10 * minutes / 60) + "\nThirst-" + to_string(-15 * minutes / 60));
		}
		if (indexOfEnvironment == 3)
		{
			River river;
			it = river.Hunt(maxIndex);
			Inventory::Change_Item("food",it->first);
			eventsDescription.setString(it->second + "\nEnergy-" + to_string(spentEnergy) + "\nHunger-" + to_string(-10 * minutes / 60) + "\nThirst-" + to_string(-15 * minutes / 60));
		}
	}
	else  eventsDescription.setString("It's nothing hunted\nEnergy-" + to_string(spentEnergy) + "\nHunger-" + to_string(-10 * minutes / 60) + "\nThirst-" + to_string(-15 * minutes / 60));
	Character::DisplayCharacteristics();
}

#pragma endregion

#pragma region ExploreArea

void UseAxe()
{
	srand(time(0));
	Inventory::wood += 3 + rand() % 8;
	Character::ChangeEnergyLevel(-15);
	GeneralTime::AddTime(0, 30);
	Character::ChangeHungerLevel(-5);
	Character::ChangeThirstLevel(-7);
}
void DontUseAxe(Container* container)
{
	container->setVisible(false);
}
#pragma endregion

#pragma region StartFire

void StayAtFireSetVisible(Container* cont, bool value, int minutes, int takenEnergy)
{
	cont->setVisible(value);
	GeneralTime::AddTime(0, minutes);
	Character::ChangeEnergyLevel(takenEnergy);
	Character::ChangeHungerLevel(-10 * minutes / 60);
	Character::ChangeThirstLevel(-15 * minutes / 60);
	Character::DisplayCharacteristics();
	Character::SetStayAtFire(true);
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
		Container* MainContainer = new Container;
		Panel* MainPanel = new Panel(Vector2f((float)0, (float)windowHeight * 0.8), windowWidth, windowHeight * 0.2);

		MainContainer->addChild(MainPanel);

#pragma region Events


		Panel* EventsPanel = new Panel("Pictures/defaultPanelForText.png", Vector2f(MainPanel->getWidth() / 32, MainPanel->getHeight() / 21.6), MainPanel->getWidth() / 2.29, MainPanel->getHeight() / 1.1);

		MainPanel->addChild(EventsPanel);

		Font font;
		font.loadFromFile("CALIBRI.TTF");

		eventsDescription.setFont(font);
		eventsDescription.setString("");
		eventsDescription.setCharacterSize(windowHeight / 50);
		eventsDescription.setPosition(Vector2f(windowWidth / 20, windowHeight / 1.2));
		eventsDescription.setFillColor(Color::Black);

#pragma endregion

#pragma region StartFire

		Container* StartFireContainer = new Container;
		Panel* StartFirePanel = new Panel(Vector2f((float)windowWidth / 10, (float)windowHeight / 10), windowWidth * 0.8, windowHeight * 0.6);
		StartFireContainer->setVisible(false);

		Button<void(*)(Container*, bool)>* StartFire = new Button<void(*)(Container*, bool)>(Vector2f((float)MainPanel->getWidth() / 2, (float)MainPanel->getHeight() / 54), Vector2f((float)MainPanel->getWidth() / 6.4, (float)MainPanel->getHeight() / 2.16), "Start fire");
		StartFire->setDelegate(ContainerSetVisible);

		Container* StayAtFireContainer = new Container;
		Panel* StayAtFirePanel = new Panel(Vector2f((float)windowWidth / 2.5, (float)windowHeight / 2), windowWidth * 0.08, windowHeight * 0.15);
		
		if (Character::IsStayAtFire())
		{
			StayAtFireContainer->setVisible(true);
			StayAtFireContainer->setActive(true);
		}
		else
			StayAtFireContainer->setVisible(false);

		Button<void(*)(int)>* StayAtFire = new Button<void(*)(int)>(Vector2f((float)StayAtFirePanel->getWidth() * 0, (float)StayAtFirePanel->getHeight() * 0), Vector2f(StayAtFirePanel->getWidth(), StayAtFirePanel->getHeight()), "Stay at fire");
		StayAtFire->setDelegate(Character::ChangeWarmthLevel);

		Button<void(*)(Container*, bool, int, int)>* FireLighter = new Button<void(*)(Container*, bool, int, int)>(Vector2f((float)StartFirePanel->getWidth()/426.5, (float)StartFirePanel->getHeight() / 2.36), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Lighter");
		FireLighter->setDelegate(StayAtFireSetVisible);

		Button<void(*)(Container*, bool, int, int)>* FireStone = new Button<void(*)(Container*, bool, int, int)>(Vector2f((float)StartFirePanel->getWidth() / 4.94, (float)StartFirePanel->getHeight() / 2.36), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Flint and Stone");
		FireStone->setDelegate(StayAtFireSetVisible);

		Button<void(*)(Container*, bool, int, int)>* FireMatches = new Button<void(*)(Container*, bool, int, int)>(Vector2f((float)StartFirePanel->getWidth() / 2.49, (float)StartFirePanel->getHeight() / 2.36), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Matches");
		FireMatches->setDelegate(StayAtFireSetVisible);

		Button<void(*)(Container*, bool, int, int)>* FireBow = new Button<void(*)(Container*, bool, int, int)>(Vector2f((float)StartFirePanel->getWidth() / 1.66, (float)StartFirePanel->getHeight() / 2.36), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Bow method");
		FireBow->setDelegate(StayAtFireSetVisible);

		Button<void(*)(Container*, bool, int, int)>* FireLens = new Button<void(*)(Container*, bool, int, int)>(Vector2f((float)StartFirePanel->getWidth() / 1.25, (float)StartFirePanel->getHeight() / 2.36), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Lens");
		FireLens->setDelegate(StayAtFireSetVisible);

		StartFireContainer->addChild(StartFirePanel);

		StartFirePanel->addChild(FireStone);
		StartFirePanel->addChild(FireBow);
		StartFirePanel->addChild(FireLighter);
		StartFirePanel->addChild(FireLens);
		StartFirePanel->addChild(FireMatches);

		if (!Inventory::Check_Tool("lighter")) FireLighter->setVisible(false);
		if (!Inventory::Check_Tool("lens")) FireLens->setVisible(false);
		if (!Inventory::Check_Tool("matches")) FireMatches->setVisible(false);

		StayAtFireContainer->addChild(StayAtFirePanel);

		StayAtFirePanel->addChild(StayAtFire);

#pragma endregion 

#pragma region ExploreArea

		Button<string(*)(int)>* ExploreArea = new Button<string(*)(int)>(Vector2f((float)MainPanel->getWidth() / 2, (float)MainPanel->getHeight() / 1.93), Vector2f((float)MainPanel->getWidth() / 6.4, (float)MainPanel->getHeight() / 2.16), "Explore Area");
		ExploreArea->setDelegate(Inventory::ExploreArea);

		Container* IsUsedAxeContainer = new Container;
		Panel* IsUsedAxePanel = new Panel(Vector2f((float)windowWidth / 10, (float)windowHeight / 10), windowWidth * 0.8, windowHeight * 0.6);
		IsUsedAxeContainer->setVisible(false);

		Button<void(*)()>* UseAxeButton = new Button<void(*)()>(Vector2f((float)IsUsedAxePanel->getWidth() / 4, (float)IsUsedAxePanel->getHeight() / 2.5), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Use Axe");
		UseAxeButton->setDelegate(UseAxe);

		Button<void(*)(Container*)>* DontUseAxeButton = new Button<void(*)(Container*)>(Vector2f((float)IsUsedAxePanel->getWidth() / 1.8, (float)IsUsedAxePanel->getHeight() / 2.5), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Don't Use Axe");
		DontUseAxeButton->setDelegate(DontUseAxe);

		IsUsedAxeContainer->addChild(IsUsedAxePanel);

		IsUsedAxePanel->addChild(UseAxeButton);
		IsUsedAxePanel->addChild(DontUseAxeButton);

#pragma endregion

#pragma region ChooseWhereToGo

		Generator::GenerateEnvironments(3, 3);

		Container* ChooseWhereToGoContainer = new Container;
		Panel* ChooseWhereToGoPanel = new Panel ("Pictures/transparent.png", Vector2f(0, (float)windowHeight / 7), windowWidth, windowHeight * 0.07);

		Button<void(*)(int)>* FirstVariantToTravel = new Button<void(*)(int)>(Vector2f((float)ChooseWhereToGoPanel->getWidth() /100, (float)0), Vector2f(ChooseWhereToGoPanel->getWidth() * 0.1, ChooseWhereToGoPanel->getHeight()), "Forest");
		FirstVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
		FirstVariantToTravel->setVisible(true);

		Button<void(*)(int)>* SecondVariantToTravel = new Button<void(*)(int)>(Vector2f((float)ChooseWhereToGoPanel->getWidth() / 2.3, (float)0), Vector2f(ChooseWhereToGoPanel->getWidth() * 0.1, ChooseWhereToGoPanel->getHeight()), "Lake");
		SecondVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
		SecondVariantToTravel->setVisible(true);

		Button<void(*)(int)>* ThirdVariantToTravel = new Button<void(*)(int)>(Vector2f((float)ChooseWhereToGoPanel->getWidth() / 1.12, (float)0), Vector2f(ChooseWhereToGoPanel->getWidth() * 0.1, ChooseWhereToGoPanel->getHeight()), "River");
		ThirdVariantToTravel->setDelegate(Location::CheckWhatEnvironment);
		ThirdVariantToTravel->setVisible(true);

		ChooseWhereToGoContainer->addChild(ChooseWhereToGoPanel);

		ChooseWhereToGoPanel->addChild(FirstVariantToTravel);
		ChooseWhereToGoPanel->addChild(SecondVariantToTravel);
		ChooseWhereToGoPanel->addChild(ThirdVariantToTravel);

#pragma endregion

#pragma region Hunt

		Container* HuntContainer = new Container;
		Panel* HuntPanel = new Panel(Vector2f((float)windowWidth / 10, (float)windowHeight / 10), windowWidth * 0.8, windowHeight * 0.6);
		HuntContainer->setVisible(false);

		Button<void(*)(Container*, bool)>* HuntButton = new Button<void(*)(Container*, bool)>(Vector2f((float)MainPanel->getWidth() / 1.5, (float)MainPanel->getHeight() / 1.93), Vector2f((float)MainPanel->getWidth() / 6.4, (float)MainPanel->getHeight() / 2.16) , "Hunt");
		HuntButton->setDelegate(ContainerSetVisible);

		Button<void(*)(int, int, int)>* FallTrap = new Button<void(*)(int, int, int)>(Vector2f((float)HuntPanel->getWidth() / 14.5, (float)HuntPanel->getHeight() / 2.5), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Fall Trap");
		FallTrap->setDelegate(HuntOveriwrite);

		Button<void(*)(int, int, int)>* SpringTrap = new Button<void(*)(int, int, int)>(Vector2f((float)HuntPanel->getWidth() / 2.49, (float)HuntPanel->getHeight() / 2.5), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Spring Trap");
		SpringTrap->setDelegate(HuntOveriwrite);

		Button<void(*)(int, int, int)>* BirdTrap = new Button<void(*)(int, int, int)>(Vector2f((float)HuntPanel->getWidth() / 1.36, (float)HuntPanel->getHeight() / 2.5), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Birds Trap");
		BirdTrap->setDelegate(HuntOveriwrite);

		HuntContainer->addChild(HuntPanel);

		HuntPanel->addChild(FallTrap);
		HuntPanel->addChild(SpringTrap);
		HuntPanel->addChild(BirdTrap);

		Container* FishContainer = new Container;
		Panel* FishPanel = new Panel(Vector2f((float)windowWidth / 10, (float)windowHeight / 10), windowWidth * 0.8, windowHeight * 0.6);
		FishContainer->setVisible(false);

		Button<void(*)(Container*, bool)>* FishButton = new Button<void(*)(Container*, bool)>(Vector2f((float)MainPanel->getWidth() / 1.5, (float)MainPanel->getHeight() / 1.93), Vector2f((float)MainPanel->getWidth() /6.4, (float)MainPanel->getHeight() / 2.16), "Fish");
		FishButton->setDelegate(ContainerSetVisible);

		Button<void(*)(int, int, int)>* FishingRod = new Button<void(*)(int, int, int)>(Vector2f((float)FishPanel->getWidth() / 4, (float)FishPanel->getHeight() / 2.5), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Fishing Rod");
		FishingRod->setDelegate(HuntOveriwrite);

		Button<void(*)(int, int, int)>* SpearFishing = new Button<void(*)(int, int, int)>(Vector2f((float)FishPanel->getWidth() / 1.8, (float)FishPanel->getHeight() / 2.5), Vector2f(StartFirePanel->getWidth() / 5.12, StartFirePanel->getHeight() / 6.48), "Spear Fishing");
		SpearFishing->setDelegate(HuntOveriwrite);

		FishContainer->addChild(FishPanel);

		FishPanel->addChild(FishingRod);
		FishPanel->addChild(SpearFishing);

		if (!Inventory::Check_Tool("fishing rod")) FishingRod->setVisible(false);
		if (!Inventory::Check_Tool("spear")) SpearFishing->setVisible(false);

#pragma endregion

#pragma region Rest

		Button<void(*)(int)>* RestButton = new Button<void(*)(int)>(Vector2f((float)MainPanel->getWidth() / 1.5, (float)MainPanel->getHeight() / 54), Vector2f((float)MainPanel->getWidth() / 6.4, (float)MainPanel->getHeight() / 2.16), "Rest");
		RestButton->setDelegate(Character::Rest);

#pragma endregion

#pragma region EatAndDrink

		Button<void(*)(int)>* EatButton = new Button<void(*)(int)>(Vector2f(windowWidth * 0.55, windowHeight / 6.9), Vector2f(windowWidth / 40, windowHeight / 40), "Use");
		EatButton->setDelegate(Character::ChangeHungerLevel);

		Button<void(*)(int)>* DrinkButton = new Button<void(*)(int)>(Vector2f(windowWidth * 0.55, windowHeight / 5.8), Vector2f(windowWidth / 40, windowHeight / 40), "Use");
		DrinkButton->setDelegate(Character::ChangeThirstLevel);

		Button<void(*)(int)>* CosumeMedicineButton = new Button<void(*)(int)>(Vector2f(windowWidth * 0.55, windowHeight / 4.25), Vector2f(windowWidth / 40, windowHeight / 40), "Use");
		CosumeMedicineButton->setDelegate(Character::ChangeConditionLevel);

#pragma endregion

#pragma region OpenInventory

		Container* OpenInventoryContainer = new Container;
		Panel* OpenInventoryPanel = new Panel(Vector2f((float)windowWidth / 10, (float)windowHeight / 10), windowWidth * 0.8, windowHeight * 0.6);
		OpenInventoryContainer->setVisible(false);

		Button<void(*)(Container*, bool)>* OpenInventory = new Button<void(*)(Container*, bool)>(Vector2f((float)MainPanel->getWidth() / 1.2, (float)MainPanel->getHeight() / 1.93), Vector2f((float)MainPanel->getWidth() / 6.4, (float)MainPanel->getHeight() / 2.16), "OpenInventory");
		OpenInventory->setDelegate(InventorySetVisible);

		Button<void(*)(Container*, bool)>* CloseInventory = new Button<void(*)(Container*, bool)>(Vector2f((float)windowWidth * 0.63, (float)windowHeight * 0.47), Vector2f(windowWidth * 0.15, windowHeight * 0.1), "CloseInventory");
		CloseInventory->setDelegate(InventorySetVisible);
		CloseInventory->setVisible(false);

		OpenInventoryContainer->addChild(OpenInventoryPanel);
		OpenInventoryPanel->addChild(CloseInventory);
		OpenInventoryPanel->addChild(EatButton);
		OpenInventoryPanel->addChild(DrinkButton);
		OpenInventoryPanel->addChild(CosumeMedicineButton);

#pragma endregion

#pragma region Menu

		Container* OpenMenuContainer = new Container;
		Panel* OpenMenuPanel = new Panel("Pictutes/transparent.png", Vector2f((float)windowWidth / 1.07, 0), windowWidth * 0.07, windowHeight * 0.07);

		Button<void(*)(RenderWindow&, Menu&)>* OpenMenu = new Button<void(*)(RenderWindow&, Menu&)>(Vector2f(0, 0), Vector2f(OpenMenuPanel->getWidth(), OpenMenuPanel->getHeight()), "Menu");
		OpenMenu->setDelegate(CallMenu);

		OpenMenuContainer->addChild(OpenMenuPanel);
		OpenMenuPanel->addChild(OpenMenu);

#pragma endregion

#pragma region LostTheGame
		Container* FailMenu = new Container;
		Panel* FailPanel = new Panel(Vector2f((float)windowWidth / 10, (float)windowHeight / 10), windowWidth * 0.8, windowHeight * 0.6);

		Button<void(*)()>* Restart = new Button<void(*)()>(Vector2f((float)FailPanel->getWidth() / 4, (float)FailPanel->getHeight() / 2.5), Vector2f(FailPanel->getWidth() / 5.12, FailPanel->getHeight() / 6.48), "Restart");
		Restart->setDelegate(Data::SetDeffaultCharacteristics);

		Button<void(*)(RenderWindow&, Menu&)>* OpenMainMenu = new Button<void(*)(RenderWindow&, Menu&)>(Vector2f((float)FailPanel->getWidth() / 1.8, (float)FailPanel->getHeight() / 2.5), Vector2f(FailPanel->getWidth() / 5.12, FailPanel->getHeight() / 6.48), "Menu");
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
		Button<void(*)(vector<Panel*>*, Panel*)>* openCraftBut = new Button<void(*)(vector<Panel*>*, Panel*)>(Vector2f((float)MainPanel->getWidth() / 1.2, (float)MainPanel->getHeight() / 54), Vector2f((float)MainPanel->getWidth() / 6.4, (float)MainPanel->getHeight() / 2.16), "Open craft menu");
		openCraftBut->setDelegate(Craft::changeCraftMenu);
		Craft::InitializeCraftMenus(&craftMenus, &craftBut, &closeCraftBut, &switchCraftBut, MainContainer, Vector2f((float)windowWidth / 10, (float)windowHeight / 10));
		MainPanel->addChild(openCraftBut);

#pragma endregion 

#pragma region StartFire

		MainPanel->addChild(StartFire);

#pragma endregion 

#pragma region ExploreArea

		MainPanel->addChild(ExploreArea);

#pragma endregion

#pragma region Hunt

		MainPanel->addChild(HuntButton);
		MainPanel->addChild(FishButton);

#pragma endregion

#pragma region Rest

		MainPanel->addChild(RestButton);

#pragma endregion

#pragma region DisplayStats
		Container* DisplayContainer = new Container;

		double timeCoefficient[] = {20, 20};
		double temperatureCoefficient[] = {6, 20};
		double characteristicsCoefficient[] = {50, 2.5};

		int barWidth = 150;
		int barHeitght = 50; 
		int distance = 60;

		Label* TimeLabel = new Label(Vector2f(windowWidth / timeCoefficient[0], windowHeight / timeCoefficient[1]), GeneralTime::GetTime(), 30, Color::Red);
		Label* TemperatureLabel = new Label(Vector2f(windowWidth / temperatureCoefficient[0], windowHeight / temperatureCoefficient[1]), to_string(Location::GetTemperature()) + "°t", 30, Color::Red);

		Bar bars[] = 
		{
			Bar("Pictures/Bars/ButtonOutline.png", "Pictures/Bars/Scale.png", "Pictures/Bars/BackScale.png", barWidth, barHeitght, "Hunger", Color::Black),
			Bar("Pictures/Bars/ButtonOutline.png", "Pictures/Bars/Scale.png", "Pictures/Bars/BackScale.png", barWidth, barHeitght, "Thirst", Color::Black),
			Bar("Pictures/Bars/ButtonOutline.png", "Pictures/Bars/Scale.png", "Pictures/Bars/BackScale.png", barWidth, barHeitght, "Warmth", Color::Black),
			Bar("Pictures/Bars/ButtonOutline.png", "Pictures/Bars/Scale.png", "Pictures/Bars/BackScale.png", barWidth, barHeitght, "Energy", Color::Black),
			Bar("Pictures/Bars/ButtonOutline.png", "Pictures/Bars/Scale.png", "Pictures/Bars/BackScale.png", barWidth, barHeitght, "Condition", Color::Black)
		};

		for (int i = 0; i < 5; i++)
			bars[i].SetPosition(windowWidth / characteristicsCoefficient[0], windowHeight / characteristicsCoefficient[1] + i * distance);

		DisplayContainer->addChild(TimeLabel);
		DisplayContainer->addChild(TemperatureLabel);
		MainContainer->addChild(DisplayContainer);
#pragma endregion

#pragma region OpenInventory

		MainPanel->addChild(OpenInventory);

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
							Character::startedHour = GeneralTime::GetHours();
							Character::startedDay = GeneralTime::GetDay();
							HuntContainer->setVisible(false);
							FishContainer->setVisible(false);
							IsUsedAxeContainer->setVisible(false);
						}
						if (FireLighter->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							eventsDescription.setString("You have more than 2 hours until fire burns out\nEnergy-3");

							FireLighter->Action(StayAtFireContainer, true, 5, -3);
							Inventory::Change_Item("wood", -5);
							StartFireContainer->setVisible(false);
						}
						if (FireStone->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							eventsDescription.setString("You have more than 2 hours until fire burns out\nEnergy-20");

							FireStone->Action(StayAtFireContainer, true, 40, -20);
							Inventory::Change_Item("wood", -5);
							StartFireContainer->setVisible(false);
						}
						if (FireMatches->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							eventsDescription.setString("You have more than 2 hours until fire burns out\nEnergy-5");

							FireMatches->Action(StayAtFireContainer, true, 5, -5);
							Inventory::Change_Item("wood", -5);
							StartFireContainer->setVisible(false);
						}
						if (FireBow->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							eventsDescription.setString("You have more than 2 hours until fire burns out\nEnergy-25");

							FireBow->Action(StayAtFireContainer, true, 60, -25);
							Inventory::Change_Item("wood", -5);
							StartFireContainer->setVisible(false);
						}
						if (FireLens->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							eventsDescription.setString("You have more than 2 hours until fire burns out\nEnergy-15");

							FireLens->Action(StayAtFireContainer, true, 30, -15);
							Inventory::Change_Item("wood", -5);
							StartFireContainer->setVisible(false);
						}
						if (StayAtFire->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							eventsDescription.setString("Warmth+60\nEnergy+10\nHunger-5\nThirst-7");

							int minutes = 60;
							GeneralTime::AddTime(0, minutes);
							Character::ChangeHungerLevel(minutes / 60 * -5);
							Character::ChangeThirstLevel(minutes / 60 * -7);
							StayAtFire->Action(minutes);
							Character::ChangeEnergyLevel(minutes / 6);
							Character::DisplayCharacteristics();
						}
#pragma endregion 

#pragma region ExploreArea

						if (ExploreArea->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							Inventory::checkClickExploreArea++;
							string value = ExploreArea->Action(Inventory::checkClickExploreArea);
							eventsDescription.setString(value);
							if (Inventory::Check_Tool("axe")) IsUsedAxeContainer->setVisible(true);
							FirstVariantToTravel->setText(CaptionOfButton(0));
							SecondVariantToTravel->setText(CaptionOfButton(1));
							ThirdVariantToTravel->setText(CaptionOfButton(2));
							StartFireContainer->setVisible(false);
							HuntContainer->setVisible(false);
							FishContainer->setVisible(false);
						}
						if (UseAxeButton->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							int previousValue = Inventory::wood;
							UseAxeButton->Action();
							if (Inventory::wood - previousValue) eventsDescription.setString("Wood+" + to_string(Inventory::wood) + "\n");
							IsUsedAxeContainer->setVisible(false);
						}
						if (DontUseAxeButton->checkClick((Vector2f)Mouse::getPosition(window))) DontUseAxeButton->Action(IsUsedAxeContainer);

#pragma endregion

#pragma region ChooseWhereToGo

						if (FirstVariantToTravel->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							srand(time(0));
							Inventory::checkClickExploreArea = 0;
							int posibilityOfBeingHurted = rand() % 2;
							FirstVariantToTravel->Action(Data::GetEnvironment(0));
							Location::LocationCurrent = Data::GetEnvironment(0);
							Character::ChangeEnergyLevel(-15);
							GeneralTime::AddTime(1, 0);
							Character::ChangeHungerLevel(-10);
							Character::ChangeThirstLevel(-15);
							string value = Inventory::LoseInventory();
							eventsDescription.setString("Energy-15\nHunger-10\nThirst-15" + value);
							if (posibilityOfBeingHurted)
							{
								Character::ChangeConditionLevel(-5);
								//cout << "You were hurted during travelling" << endl;
								eventsDescription.setString("Energy-15\nHunger-10\nThirst-15\nYou were hurted during travelling\nCondition-5" + value);
							}
							Character::DisplayCharacteristics();
							StartFireContainer->setVisible(false);
							HuntContainer->setVisible(false);
							FishContainer->setVisible(false);
							IsUsedAxeContainer->setVisible(false);
							StayAtFireContainer->setVisible(false);
						}
						if (SecondVariantToTravel->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							srand(time(0));
							Inventory::checkClickExploreArea = 0;
							int posibilityOfBeingHurted = rand() % 2;
							SecondVariantToTravel->Action(Data::GetEnvironment(1));
							Location::LocationCurrent = Data::GetEnvironment(1);
							Character::ChangeEnergyLevel(-15);
							GeneralTime::AddTime(1, 0);
							Character::ChangeHungerLevel(-10);
							Character::ChangeThirstLevel(-15);
							string value = Inventory::LoseInventory();
							eventsDescription.setString("Energy-15\nHunger-10\nThirst-15" + value);
							if (posibilityOfBeingHurted)
							{
								Character::ChangeConditionLevel(-5);
								//cout << "You were hurted during travelling" << endl;
								eventsDescription.setString("Energy-15\nHunger-10\nThirst-15\nYou were hurted during travelling\nCondition-5" + value);
							}
							Character::DisplayCharacteristics();
							StartFireContainer->setVisible(false);
							HuntContainer->setVisible(false);
							FishContainer->setVisible(false);
							IsUsedAxeContainer->setVisible(false);
							StayAtFireContainer->setVisible(false);
						}
						if (ThirdVariantToTravel->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							srand(time(0));
							Inventory::checkClickExploreArea = 0;
							int posibilityOfBeingHurted = rand() % 2;
							ThirdVariantToTravel->Action(Data::GetEnvironment(2));
							Location::LocationCurrent = Data::GetEnvironment(2);
							Character::ChangeEnergyLevel(-15);
							GeneralTime::AddTime(1, 0);
							Character::ChangeHungerLevel(-10);
							Character::ChangeThirstLevel(-15);
							string value = Inventory::LoseInventory();
							eventsDescription.setString("Energy-15\nHunger-10\nThirst-15" + value);
							if (posibilityOfBeingHurted)
							{
								Character::ChangeConditionLevel(-5);
								//cout << "You were hurted during travelling" << endl;
								eventsDescription.setString("Energy-15\nHunger-10\nThirst-15\nYou were hurted during travelling\nCondition-5" + value);
							}
							Character::DisplayCharacteristics();
							StartFireContainer->setVisible(false);
							HuntContainer->setVisible(false);
							FishContainer->setVisible(false);
							IsUsedAxeContainer->setVisible(false);
							StayAtFireContainer->setVisible(false);
						}

#pragma endregion

#pragma region Hunt

						if (HuntButton->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							HuntButton->Action(HuntContainer, true);
							IsUsedAxeContainer->setVisible(false);
							StartFireContainer->setVisible(false);
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
							IsUsedAxeContainer->setVisible(false);
							StartFireContainer->setVisible(false);
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

						if (RestButton->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							RestButton->Action(4);
							eventsDescription.setString("Energy+52\nHunger-28\nThirst-20");
							StartFireContainer->setVisible(false);     
							HuntContainer->setVisible(false);
							FishContainer->setVisible(false);
							IsUsedAxeContainer->setVisible(false);
						}

#pragma endregion 

#pragma region OpenInventory

						if (OpenInventory->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							OpenInventory->Action(OpenInventoryContainer, !OpenInventoryContainer->getVisible());
							CloseInventory->setVisible(!CloseInventory->getVisible());
							StartFireContainer->setVisible(false);
							HuntContainer->setVisible(false);
							FishContainer->setVisible(false);
							IsUsedAxeContainer->setVisible(false);
						}
						if (CloseInventory->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							OpenInventory->Action(OpenInventoryContainer, false);
							CloseInventory->setVisible(false);
						}

#pragma endregion

#pragma region EatAndDrink

						if (EatButton->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							EatButton->Action(5); 
							eventsDescription.setString("Hunger+5");
							Inventory::food -= 1;
						}
						if (DrinkButton->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							DrinkButton->Action(5);
							eventsDescription.setString("Thirst+5");
							Inventory::water -= 1;
						}
						if (CosumeMedicineButton->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							CosumeMedicineButton->Action(5);
							eventsDescription.setString("Condition+5");
							Inventory::medicine -= 1;
						}

#pragma endregion

#pragma region LostTheGame

						if (Restart->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							eventsDescription.setString("");
							MainContainer->setActive(true);
							HuntContainer->setActive(true);
							FishContainer->setActive(true);
							OpenInventoryContainer->setActive(true);
							StartFireContainer->setActive(true);
							StayAtFireContainer->setActive(true);
							IsUsedAxeContainer->setActive(true);
							FailMenu->setActive(false);
							Restart->Action();
						}

#pragma endregion

#pragma region Menu

						if (OpenMenu->checkClick((Vector2f)Mouse::getPosition(window)) || OpenMainMenu->checkClick((Vector2f)Mouse::getPosition(window)))
						{
							MainContainer->setActive(true);
							HuntContainer->setActive(true);
							FishContainer->setActive(true);
							OpenInventoryContainer->setActive(true);
							StartFireContainer->setActive(true);
							StayAtFireContainer->setActive(true);
							IsUsedAxeContainer->setVisible(false);

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
							StartFireContainer->setVisible(false);
							HuntContainer->setVisible(false);
							FishContainer->setVisible(false);
							IsUsedAxeContainer->setVisible(false);
						}
						for (map<Button<bool(*)(string)>*, string>::iterator it = craftBut.begin(); it != craftBut.end(); ++it)
						{
							if (it->first->checkClick((Vector2f)Mouse::getPosition(window)))
							{
								if (it->first->Action(it->second))
									eventsDescription.setString("Successfully crafted");
								else
									eventsDescription.setString("Not enough resources or this tool already exist");
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
			UseAxeButton->update((Vector2f)Mouse::getPosition(window));
			DontUseAxeButton->update((Vector2f)Mouse::getPosition(window));


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

#pragma region EatAndDrink

			EatButton->update((Vector2f)Mouse::getPosition(window));
			DrinkButton->update((Vector2f)Mouse::getPosition(window));
			CosumeMedicineButton->update((Vector2f)Mouse::getPosition(window));

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

#pragma region ChooseWhereToGo

			ChooseWhereToGoContainer->render(window, Vector2f(0, 0));

#pragma endregion

#pragma region StartFire

			if (!Character::IsStayAtFire())
			{
				StayAtFireContainer->setVisible(false);
				StayAtFireContainer->setActive(false);
			}

			if (GeneralTime::DeltaTime(Character::startedDay, Character::startedHour) > 2)
			{
				StayAtFireContainer->setVisible(false); // an example; it's not necessary must be 5
				Character::SetStayAtFire(false);
			}
			if (StayAtFireContainer->getVisible()) StartFire->setActive(false);
			else StartFire->setActive(true);
			if (Inventory::wood < 5) StartFire->setActive(false);
			StartFireContainer->render(window, Vector2f(0, 0));
			StayAtFireContainer->render(window, Vector2f(0, 0));

#pragma endregion 

#pragma region ExploreArea

			if (!Inventory::checkClickExploreArea || Character::CheckIFCharacteristicsBelowZero()) ChooseWhereToGoContainer->setVisible(false);
			else ChooseWhereToGoContainer->setVisible(true);
			if (IsUsedAxeContainer->getVisible()) ExploreArea->setActive(false);
			else ExploreArea->setActive(true);

#pragma endregion

#pragma region EatAndDrink

			if (!Inventory::food) EatButton->setVisible(false);
			else EatButton->setVisible(true);
			if (!Inventory::water) DrinkButton->setVisible(false);
			else DrinkButton->setVisible(true);
			if (!Inventory::medicine) CosumeMedicineButton->setVisible(false);
			else CosumeMedicineButton->setVisible(true);

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

			if (!Inventory::Check_Tool("fall trap")) FallTrap->setVisible(false);
			if (!Inventory::Check_Tool("spring trap")) SpringTrap->setVisible(false);
			if (!Inventory::Check_Tool("bird trap")) BirdTrap->setVisible(false);

#pragma endregion

#pragma region OpenInventory

			OpenInventoryContainer->render(window, Vector2f(0, 0));

#pragma endregion

			//Update text
			TimeLabel->setText(GeneralTime::GetTime());
			TemperatureLabel->setText(to_string(Location::GetTemperature()) + "°t");

			//Update Bars
			bars[Bars::HungerBar].SetScale(Character::GetHungerLevel());
			bars[Bars::HungerBar].Render(window);

			bars[Bars::ThirstBar].SetScale(Character::GetThirstLevel());
			bars[Bars::ThirstBar].Render(window);
			
			bars[Bars::WarmthBar].SetScale(Character::GetWarmthLevel());
			bars[Bars::WarmthBar].Render(window);

			bars[Bars::EnergyBar].SetScale(Character::GetEnergyLevel());
			bars[Bars::EnergyBar].Render(window);

			bars[Bars::ConditionBar].SetScale(Character::GetConditionLevel());
			bars[Bars::ConditionBar].Render(window);


			Data::SaveGamePerSomeTime(23); // Save data per some time (in hours)	
			MainContainer->render(window, Vector2f(0, 0)); // render themself and all ui that contain

#pragma region Hunt	

			HuntContainer->render(window, Vector2f(0, 0));
			FishContainer->render(window, Vector2f(0, 0));

#pragma endregion

			OpenInventoryContainer->render(window, Vector2f(0, 0));

			IsUsedAxeContainer->render(window, Vector2f(0, 0));

#pragma region Menu

			OpenMenuContainer->render(window, Vector2f(0, 0));

#pragma endregion

#pragma region LostMenu
			if (Character::CheckIFCharacteristicsBelowZero())
			{
				MainContainer->setActive(false);
				HuntContainer->setActive(false);
				FishContainer->setActive(false);
				OpenInventoryContainer->setActive(false);
				StartFireContainer->setActive(false);
				StayAtFireContainer->setActive(false);
				ChooseWhereToGoContainer->setActive(false);
				IsUsedAxeContainer->setActive(false);
				FailMenu->setActive(true);

				StayAtFireContainer->setVisible(false);
				ChooseWhereToGoContainer->setVisible(false);
				HuntContainer->setVisible(false);
				OpenInventoryContainer->setVisible(false);
				StartFireContainer->setVisible(false);
				IsUsedAxeContainer->setVisible(false);
				Craft::changeCraftMenu(&craftMenus, NULL);

				FailMenu->render(window, Vector2f(0, 0));
			}
#pragma endregion

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

				Items_Title.setPosition((float)windowWidth * 0.5, (float)windowHeight * 0.12);
				Items.setPosition((float)windowWidth * 0.5, (float)windowHeight * 0.21);
				Items_Values.setPosition((float)windowWidth * 0.6, (float)windowHeight * 0.21);
				Tools_Title.setPosition((float)windowWidth * 0.15, (float)windowHeight * 0.12);
				Tools.setPosition((float)windowWidth * 0.15, (float) windowHeight * 0.21);
				Tools_Values.setPosition((float)windowWidth * 0.27, (float)windowHeight * 0.21);

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

			window.draw(eventsDescription);

			window.display();
		}
	}

	// Deleteing dynamic objects

	return 0;
}