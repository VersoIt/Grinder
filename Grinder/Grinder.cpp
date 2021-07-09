// 29.06.2021: 17:36
// By Ruslan Lyaschenko

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <iostream>

#include "Button.hpp"
#include "ScrollField.hpp"
#include "GUI.hpp"
#include "Game.hpp"
#include "Configuration.hpp"

using namespace EngineComponents;

inline void saveAndExit()
{
	exit(EXIT_SUCCESS);
}

enum class Gui
{
	MAIN,
	SETTINGS,
	PAUSE,
	GAME
};

void generateMainMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
{
	scene.push(new EngineComponents::Button("Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", { static_cast<float>(window.getSize().x / 2), 821.f }, [&]() {focus = Gui::GAME; }, "PLAY"));
	scene.push(new EngineComponents::Button("Interface/Buttons/Settings/SettingsButton.png", "Interface/Buttons/Settings/SettingsButton.png", { 1848.f, 70.f }, [&]() {focus = Gui::SETTINGS; }));
	scene.push(new EngineComponents::Button("Interface/MainMenu/CompanyText.png", "Interface/MainMenu/CompanyText.png", { 110.f, 1055.f }, []() {}));
	scene.push(new EngineComponents::Button("Interface/MainMenu/LogoText.png", "Interface/MainMenu/LogoText.png", { static_cast<float>(window.getSize().x / 2), 233.f }, []() {}));
	scene.push(new EngineComponents::Button({0.7f, 0.7f}, "Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", { 1750.f, 1000.f }, []() {exit(EXIT_SUCCESS); }, "EXIT"));
}

void generateSettingsMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
{
	scene.push(new EngineComponents::Button({ 0.7f, 0.7f }, "Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", { 150.f, 76.f }, [&]() { focus = Gui::MAIN; }, "BACK"));
	scene.push(new EngineComponents::Button("Interface/SettingsMenu/SettingsText.png", "Interface/SettingsMenu/SettingsText.png", { static_cast<float>(window.getSize().x / 2), 233.f }, []() {}));
}

void generatePauseMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
{
	scene.push(new EngineComponents::Button("Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", { static_cast<float>(window.getSize().x / 2), 535.f }, [&]() {focus = Gui::GAME; }, "RESUME"));
	scene.push(new EngineComponents::Button("Interface/Buttons/Settings/SettingsButton.png", "Interface/Buttons/Settings/SettingsButton.png", { 110.f, 95.f }, [&]() {focus = Gui::SETTINGS; }));
	scene.push(new EngineComponents::Button("Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", { static_cast<float>(window.getSize().x / 2), 685.f }, []() {}, "SAVE"));
	scene.push(new EngineComponents::Button({ 0.7f, 0.7f }, "Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", { 175.f, 991.f }, [&]() {focus = Gui::MAIN; }, "MENU"));
	scene.push(new EngineComponents::Button("Interface/Buttons/Settings/SoundButton.png", "Interface/Buttons/Settings/SoundButtonHover.png", { 1570.f, 108.f }, [&]() {std::cout << "Sound" << std::endl; }));
	scene.push(new EngineComponents::Button("Interface/Buttons/Settings/MusicButton.png", "Interface/Buttons/Settings/MusicButtonHover.png", { 1795.f, 108.f }, [&]() {std::cout << "Music" << std::endl; }));
}

void generateConfirmMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
{
	scene.push(new EngineComponents::Button("Interface/PauseMenu/ResumeButton.png", "Interface/PauseMenu/ResumeButtonHover.png", { static_cast<float>(window.getSize().x / 2), 535.f }, [&]() {focus = Gui::GAME; }));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/SettingsButton.png", "Interface/PauseMenu/SettingsButton.png", { 110.f, 95.f }, [&]() {focus = Gui::SETTINGS; }));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/SaveButton.png", "Interface/PauseMenu/SaveButtonHover.png", { static_cast<float>(window.getSize().x / 2), 685.f }, []() {}));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/MenuButton.png", "Interface/PauseMenu/MenuButtonHover.png", { 175.f, 991.f }, [&]() {focus = Gui::MAIN; }));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/SoundButton.png", "Interface/PauseMenu/SoundButtonHover.png", { 1570.f, 108.f }, [&]() {std::cout << "Sound" << std::endl; }));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/MusicButton.png", "Interface/PauseMenu/MusicButtonHover.png", { 1795.f, 108.f }, [&]() {std::cout << "Music" << std::endl; }));
}

int main()
{
	try
	{
		sf::RenderWindow window;
		sf::Event event;
		Gui focus = Gui::MAIN;

		bool isSelect = true;

		EngineComponents::Game game("Utility/Map.tmx");

		GUI mainMenu("Interface/MainMenu/Background.png");
		GUI settingsMenu("Interface/SettingsMenu/Background.png");
		GUI pauseMenu("Interface/PauseMenu/Background.png");

		window.create(sf::VideoMode::getDesktopMode(), "Elision engine works!", sf::Style::Default);
		window.setFramerateLimit(300);

		EngineComponents::ScrollField* soundSettings = new EngineComponents::ScrollField(window, new EngineComponents::Button("Interface/Buttons/Settings/SoundButton.png", "Interface/Buttons/Settings/SoundButtonHover.png", { 700.f, 730.f }), new EngineComponents::Button("Interface/Buttons/Settings/NoSoundButton.png", "Interface/Buttons/Settings/NoSoundButtonHover.png"), new EngineComponents::Button("Interface/Buttons/Settings/SoundButton.png", "Interface/Buttons/Settings/SoundButtonHover.png"), "Interface/SettingsMenu/ScrollField.png", "Interface/SettingsMenu/ScrollField.png", { static_cast<float>(window.getSize().x / 2), 730.f }, Utility::loadSettings("Settings.tmx", "sound"));
		EngineComponents::ScrollField* musicSettings = new EngineComponents::ScrollField(window, new EngineComponents::Button("Interface/Buttons/Settings/MusicButton.png", "Interface/Buttons/Settings/MusicButtonHover.png", { 700.f, 955.f }), new EngineComponents::Button("Interface/Buttons/Settings/NoMusicButton.png", "Interface/Buttons/Settings/NoMusicButtonHover.png"), new EngineComponents::Button("Interface/Buttons/Settings/MusicButton.png", "Interface/Buttons/Settings/MusicButtonHover.png"), "Interface/SettingsMenu/ScrollField.png", "Interface/SettingsMenu/ScrollField.png", { static_cast<float>(window.getSize().x / 2), 955.f }, Utility::loadSettings("Settings.tmx", "music"));

		settingsMenu.push(soundSettings);
		settingsMenu.push(musicSettings);

		// creating the scenes of interface
		generateMainMenu(mainMenu, window, focus);
		generateSettingsMenu(settingsMenu, window, focus);
		generatePauseMenu(pauseMenu, window, focus);

		RenderObject* currentScene = &mainMenu;
		while (window.isOpen())
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			currentScene->catchMouseEvent(event, mousePos);

			while (window.pollEvent(event))
			{
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
							exit(EXIT_SUCCESS);
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
		std::cout << exc.what() << std::endl;
		std::cout << "Please, reload game." << std::endl;
		Utility::generateSettingsXML("Settings.tmx");
	}
	catch (...)
	{
		std::cout << "Something is wrong..." << std::endl;
		return EXIT_FAILURE;
	}
}