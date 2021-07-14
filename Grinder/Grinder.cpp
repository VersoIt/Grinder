// 29.06.2021: 17:36
// By Ruslan Lyaschenko

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <iostream>
#include "Button.hpp"
#include "ScrollField.hpp"
#include "GUI.hpp"
#include "Game.hpp"
#include "Configuration.hpp"

using namespace EngineComponents;
using namespace Utility;

int main()
{

	sf::Event event;
	EngineComponents::GUI warningMenu;
	GUI loadingMenu;
	sf::RenderWindow window;

	try
	{
		window.create(sf::VideoMode::getDesktopMode(), "Elision engine works!", sf::Style::Fullscreen);
		generateWarningMenu(warningMenu, window);
		loadingMenu.setTexture("Interface/LoadingMenu/Background.png");
		loadingMenu.sprite.move(static_cast<float>(loadingMenu.texture.getSize().x / 2), static_cast<float>(loadingMenu.texture.getSize().y / 2));
		generateLoadingMenu(loadingMenu, window);

		window.draw(loadingMenu);
		window.display();

		Gui focus = Gui::MAIN;
		bool isSelect = true;

		Game game("Utility/Map.tmx");
		GUI mainMenu("Interface/MainMenu/Background.png");
		GUI settingsMenu("Interface/SettingsMenu/Background.png");
		GUI pauseMenu("Interface/PauseMenu/Background.png");

		// creating the scenes of interface
		generateMainMenu(mainMenu, window, focus);
		generateSettingsMenu(settingsMenu, window, focus);
		generatePauseMenu(pauseMenu, window, focus);

		EngineComponents::ScrollField* soundSettings = new EngineComponents::ScrollField(window, new EngineComponents::Button("Interface/Buttons/Settings/SoundButton.png", "Interface/Buttons/Settings/SoundButtonHover.png", []() {}, { 700.f, 730.f }), new EngineComponents::Button("Interface/Buttons/Settings/NoSoundButton.png", "Interface/Buttons/Settings/NoSoundButtonHover.png"), new EngineComponents::Button("Interface/Buttons/Settings/SoundButton.png", "Interface/Buttons/Settings/SoundButtonHover.png"), "Interface/SettingsMenu/ScrollField.png", "Interface/SettingsMenu/ScrollField.png", { static_cast<float>(window.getSize().x / 2), 730.f }, Utility::loadSettings("Settings.tmx", "sound"));
		EngineComponents::ScrollField* musicSettings = new EngineComponents::ScrollField(window, new EngineComponents::Button("Interface/Buttons/Settings/MusicButton.png", "Interface/Buttons/Settings/MusicButtonHover.png", []() {}, { 700.f, 955.f }), new EngineComponents::Button("Interface/Buttons/Settings/NoMusicButton.png", "Interface/Buttons/Settings/NoMusicButtonHover.png"), new EngineComponents::Button("Interface/Buttons/Settings/MusicButton.png", "Interface/Buttons/Settings/MusicButtonHover.png"), "Interface/SettingsMenu/ScrollField.png", "Interface/SettingsMenu/ScrollField.png", { static_cast<float>(window.getSize().x / 2), 955.f }, Utility::loadSettings("Settings.tmx", "music"));

		settingsMenu.push(soundSettings);
		settingsMenu.push(musicSettings);

		EventObject* currentScene = &mainMenu;

		while (window.isOpen())
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			while (window.pollEvent(event))
			{

				currentScene->catchMouseEvent(event, mousePos);

				// handling keystrokes
				switch (event.type)
				{
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape && isSelect)
					{
						isSelect = false;
						switch (focus)
						{
						case Gui::GAME:
							focus = Gui::PAUSE;
							break;
						case Gui::PAUSE:
							focus = Gui::GAME;
							break;
						case Gui::SETTINGS:
							focus = Gui::MAIN;
							break;
						case Gui::MAIN:
							window.close();
							break;
						}
					}
					break;
				case sf::Event::KeyReleased:
					isSelect = true;
					break;
				}
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();

			switch (focus)
			{
			case Gui::GAME:
				currentScene = &game;
				window.draw(game);
				break;
			case Gui::PAUSE:
				currentScene = &pauseMenu;
				window.draw(game);
				window.draw(pauseMenu);
				break;
			case Gui::SETTINGS:
				currentScene = &settingsMenu;
				window.draw(settingsMenu);
				break;
			case Gui::MAIN:
				currentScene = &mainMenu;
				window.draw(mainMenu);
				break;
			}
			window.display();
		}
		Utility::saveSettings("Settings.tmx", *soundSettings, "sound");
		Utility::saveSettings("Settings.tmx", *musicSettings, "music");

		return EXIT_SUCCESS;
	}
	catch (EngineComponents::SettingsFileMissing& exc)
	{
		Utility::generateSettingsXML("Settings.tmx");
		Utility::showWarningMenu(warningMenu, exc.what(), "Please, reload the game.", window, event);
	}
	catch (EngineComponents::FileMissing& exc)
	{
		Utility::showWarningMenu(warningMenu, exc.what(), "Please, reinstall the game.", window, event);
	}
	catch (...)
	{
		Utility::showWarningMenu(warningMenu, "Something went wrong...", "Please, reload the game.", window, event);
		return EXIT_FAILURE;
	}
}