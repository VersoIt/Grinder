// 29.06.2021: 17:36
// By Ruslan Lyaschenko

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <iostream>

#include "Button.hpp"
#include "ScrollField.hpp"
#include "GUI.hpp"
#include "Game.hpp"

enum class Gui
{
	MAIN,
	SETTINGS,
	PAUSE,
	GAME
};

void generateMainMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
{
	scene.push(new EngineComponents::Button("Interface/MainMenu/PlayButton.png", "Interface/MainMenu/PlayButtonHover.png", { static_cast<float>(window.getSize().x / 2), 821.f }, [&]() {focus = Gui::GAME; }));
	scene.push(new EngineComponents::Button("Interface/MainMenu/SettingsButton.png", "Interface/MainMenu/SettingsButton.png", { 1848.f, 70.f }, [&]() {focus = Gui::SETTINGS; }));
	scene.push(new EngineComponents::Button("Interface/MainMenu/CompanyText.png", "Interface/MainMenu/CompanyText.png", { 110.f, 1055.f }, []() {}));
	scene.push(new EngineComponents::Button("Interface/MainMenu/LogoText.png", "Interface/MainMenu/LogoText.png", { static_cast<float>(window.getSize().x / 2), 233.f }, []() {}));
	scene.push(new EngineComponents::Button("Interface/SettingsMenu/BackButton.png", "Interface/SettingsMenu/BackButtonHover.png", { 1750.f, 1000.f }, []() {exit(EXIT_SUCCESS); }));
}

void generateSettingsMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
{
	scene.push(new EngineComponents::Button("Interface/SettingsMenu/BackButton.png", "Interface/SettingsMenu/BackButtonHover.png", { 150.f, 76.f }, [&]() { focus = Gui::MAIN; }));
	scene.push(new EngineComponents::Button("Interface/SettingsMenu/SettingsText.png", "Interface/SettingsMenu/SettingsText.png", { static_cast<float>(window.getSize().x / 2), 233.f }, []() {}));
	scene.push(new EngineComponents::ScrollField(window, new EngineComponents::Button("Interface/SettingsMenu/SoundButton.png", "Interface/SettingsMenu/SoundButtonHover.png", { 1500.f, 730.f }), new EngineComponents::Button("Interface/SettingsMenu/NoSoundButton.png", "Interface/SettingsMenu/NoSoundButtonHover.png"), new EngineComponents::Button("Interface/SettingsMenu/SoundButton.png", "Interface/SettingsMenu/SoundButtonHover.png"), "Interface/SettingsMenu/ScrollField.png", "Interface/SettingsMenu/ScrollField.png", { static_cast<float>(window.getSize().x / 2), 730.f }));
	scene.push(new EngineComponents::ScrollField(window, new EngineComponents::Button("Interface/SettingsMenu/MusicButton.png", "Interface/SettingsMenu/MusicButtonHover.png", { 1500.f, 955.f }), new EngineComponents::Button("Interface/SettingsMenu/NoMusicButton.png", "Interface/SettingsMenu/NoMusicButtonHover.png"), new EngineComponents::Button("Interface/SettingsMenu/MusicButton.png", "Interface/SettingsMenu/MusicButtonHover.png"), "Interface/SettingsMenu/ScrollField.png", "Interface/SettingsMenu/ScrollField.png", { static_cast<float>(window.getSize().x / 2), 955.f }));
}

void generatePauseMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
{
	scene.push(new EngineComponents::Button("Interface/PauseMenu/ResumeButton.png", "Interface/PauseMenu/ResumeButtonHover.png", { static_cast<float>(window.getSize().x / 2), 535.f }, [&]() {focus = Gui::GAME; }));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/SettingsButton.png", "Interface/PauseMenu/SettingsButton.png", { 110.f, 95.f }, [&]() {focus = Gui::SETTINGS; }));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/SaveButton.png", "Interface/PauseMenu/SaveButtonHover.png", { static_cast<float>(window.getSize().x / 2), 685.f }, []() {}));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/MenuButton.png", "Interface/PauseMenu/MenuButtonHover.png", { 175.f, 991.f }, [&]() {focus = Gui::MAIN; }));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/SoundButton.png", "Interface/PauseMenu/SoundButtonHover.png", { 1570.f, 108.f }, [&]() {std::cout << "Sound" << std::endl; }));
	scene.push(new EngineComponents::Button("Interface/PauseMenu/MusicButton.png", "Interface/PauseMenu/MusicButtonHover.png", { 1795.f, 108.f }, [&]() {std::cout << "Music" << std::endl; }));
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
	using namespace EngineComponents;

	sf::RenderWindow window;
	sf::Event event;
	Gui focus = Gui::MAIN;

	bool isSelect = true;

	EngineComponents::Game game("Utility/Map.tmx", "Game");

	GUI mainMenu("Interface/MainMenu/Background.png", "MainMenu");
	GUI settingsMenu("Interface/SettingsMenu/Background.png", "SettingsMenu");
	GUI pauseMenu("Interface/PauseMenu/Background.png", "PauseMenu");
	GUI confirmMenu("Interface/PauseMenu/Background.png", "PauseMenu");

	window.create(sf::VideoMode::getDesktopMode(), "Elision engine works!", sf::Style::Fullscreen);
	window.setFramerateLimit(120);

	// creating the scenes of interface
	generateMainMenu(mainMenu, window, focus);
	generateSettingsMenu(settingsMenu, window, focus);
	generatePauseMenu(pauseMenu, window, focus);

	GUIObject* currentScene = &mainMenu;

	while (window.isOpen())
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
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

		window.display();
	}
	return EXIT_SUCCESS;
}