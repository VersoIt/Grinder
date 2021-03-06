#include "Configuration.hpp"

namespace Utility
{
	int showWarningMenu(EngineComponents::GUI& warningMenu, const char* what, const char* request, sf::RenderWindow& window, sf::Event& event)
	{
		sf::RectangleShape backgroundMenu({ 880.f, 1080.f });
		backgroundMenu.setOrigin(backgroundMenu.getSize().x / 2, backgroundMenu.getSize().y / 2);
		backgroundMenu.setFillColor(sf::Color(0, 0, 0, 128));
		backgroundMenu.setPosition(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2));

		EngineComponents::Object* excText = new EngineComponents::Object("", what);
		excText->text.setCharacterSize(static_cast<unsigned int>(backgroundMenu.getSize().x / 17.2));

		EngineComponents::Object* askText = new EngineComponents::Object(*excText);
		askText->setString(request);

		warningMenu.push(excText);
		warningMenu.push(askText);

		EngineComponents::SpriteManager backgroundSprite("");

		try
		{
			backgroundSprite.setTexture("Interface/MainMenu/Background.png");
			backgroundSprite.sprite.setPosition(static_cast<float>(backgroundSprite.texture.getSize().x / 2), static_cast<float>(backgroundSprite.texture.getSize().y / 2));
			excText->setFont("Fonts/Archive.ttf");
			askText->setFont("Fonts/Archive.ttf");
		}
		catch (...)
		{
			exit(EXIT_FAILURE);
		}

		excText->text.setPosition(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2));
		askText->text.setPosition(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2 + excText->text.getLocalBounds().height * 1.5));
		askText->text.setFillColor(sf::Color(255, 252, 0));

		sf::RectangleShape background({ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) });
		background.setFillColor(sf::Color(0, 0, 0, 128));

		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				warningMenu.catchMouseEvent(event, sf::Mouse::getPosition());
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(backgroundSprite);
			window.draw(background);
			window.draw(backgroundMenu);
			window.draw(warningMenu);
			window.display();

		}

		return EXIT_FAILURE;

	}

	void saveSettings(const char* path, EngineComponents::ScrollField& settings, const char* element)
	{
		tinyxml2::XMLDocument document;
		if (document.LoadFile(path) != tinyxml2::XML_SUCCESS)
			throw EngineComponents::SettingsFileMissing("The settings file is missing.");

		tinyxml2::XMLHandle docHandle(&document);
		tinyxml2::XMLElement* sound = docHandle.FirstChildElement("settings").FirstChildElement(element).ToElement();

		if (sound)
		{
			sound->SetAttribute("value", settings.getShare());
			document.SaveFile(path);
			return;
		}

		throw EngineComponents::SettingsFileMissing("The settings file is corrupted.");
	}

	int loadSettings(const char* path, const char* element)
	{
		tinyxml2::XMLDocument document;
		if (document.LoadFile(path) != tinyxml2::XML_SUCCESS)
			throw EngineComponents::SettingsFileMissing("The settings file is missing.");

		tinyxml2::XMLHandle docHandle(&document);
		tinyxml2::XMLElement* sound = docHandle.FirstChildElement("settings").FirstChildElement(element).ToElement();
		if (sound && sound->Attribute("value"))
			return std::stoi(sound->Attribute("value"));

		throw EngineComponents::SettingsFileMissing("The settings file is corrupted.");
	}

	void generateSettingsXML(const char* fileName)
	{
		tinyxml2::XMLDocument document;

		document.LinkEndChild(document.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
		document.LinkEndChild(document.NewComment("Settings file"));

		auto settingsElement = document.NewElement("settings");
		auto soundElement = document.NewElement("sound");
		auto musicElement = document.NewElement("music");

		soundElement->SetAttribute("value", 80);
		musicElement->SetAttribute("value", 80);

		settingsElement->LinkEndChild(soundElement);
		settingsElement->LinkEndChild(musicElement);

		document.LinkEndChild(settingsElement);

		document.SaveFile(fileName);
	}

	void generateMainMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
	{
		scene.push(new EngineComponents::Button("Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", [&]() {focus = Gui::GAME; }, { static_cast<float>(window.getSize().x / 2), 821.f }, "PLAY"));
		scene.push(new EngineComponents::Button("Interface/Buttons/Settings/SettingsButton.png", "Interface/Buttons/Settings/SettingsButton.png", [&]() {focus = Gui::SETTINGS; }, { 1848.f, 70.f }));
		scene.push(new EngineComponents::Object("", EngineComponents::TextManager("Grinder 1.0.0\nCopyright Elision AB. Do not distribute!", "Fonts/Archive.ttf", 20, { 250.f, 1030.f })));
		scene.push(new EngineComponents::Button("Interface/MainMenu/LogoText.png", "Interface/MainMenu/LogoText.png", []() {}, { static_cast<float>(window.getSize().x / 2), 233.f }));
		scene.push(new EngineComponents::Button({ 0.7f, 0.7f }, "Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", [&]() {window.close(); }, { 1750.f, 1000.f }, "EXIT"));
	}

	void generateSettingsMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
	{
		scene.push(new EngineComponents::Button({ 0.7f, 0.7f }, "Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", [&]() { focus = Gui::MAIN; }, { 150.f, 76.f }, "BACK"));
		scene.push(new EngineComponents::Button("Interface/SettingsMenu/SettingsText.png", "Interface/SettingsMenu/SettingsText.png", []() {}, { static_cast<float>(window.getSize().x / 2), 233.f }));
	}

	void generatePauseMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
	{
		scene.push(new EngineComponents::Button("Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", [&]() {focus = Gui::GAME; }, { static_cast<float>(window.getSize().x / 2), 535.f }, "RESUME"));
		scene.push(new EngineComponents::Button("Interface/Buttons/Settings/SettingsButton.png", "Interface/Buttons/Settings/SettingsButton.png", [&]() {focus = Gui::SETTINGS; }, { 110.f, 95.f }));
		scene.push(new EngineComponents::Button("Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", []() {}, { static_cast<float>(window.getSize().x / 2), 685.f }, "SAVE"));
		scene.push(new EngineComponents::Button({ 0.7f, 0.7f }, "Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", [&]() {focus = Gui::MAIN; }, { 175.f, 991.f }, "MENU"));
		scene.push(new EngineComponents::Button("Interface/Buttons/Settings/SoundButton.png", "Interface/Buttons/Settings/SoundButtonHover.png", [&]() {std::cout << "Sound" << std::endl; }, { 1570.f, 108.f }));
		scene.push(new EngineComponents::Button("Interface/Buttons/Settings/MusicButton.png", "Interface/Buttons/Settings/MusicButtonHover.png", [&]() {std::cout << "Music" << std::endl; }, { 1795.f, 108.f }));
	}

	void generateConfirmMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus)
	{
		scene.push(new EngineComponents::Button("Interface/PauseMenu/ResumeButton.png", "Interface/PauseMenu/ResumeButtonHover.png", [&]() {focus = Gui::GAME; }, { static_cast<float>(window.getSize().x / 2), 535.f }));
		scene.push(new EngineComponents::Button("Interface/PauseMenu/SettingsButton.png", "Interface/PauseMenu/SettingsButton.png", [&]() {focus = Gui::SETTINGS; }, { 110.f, 95.f }));
		scene.push(new EngineComponents::Button("Interface/PauseMenu/SaveButton.png", "Interface/PauseMenu/SaveButtonHover.png", []() {}, { static_cast<float>(window.getSize().x / 2), 685.f }));
		scene.push(new EngineComponents::Button("Interface/PauseMenu/MenuButton.png", "Interface/PauseMenu/MenuButtonHover.png", [&]() {focus = Gui::MAIN; }, { 175.f, 991.f }));
		scene.push(new EngineComponents::Button("Interface/PauseMenu/SoundButton.png", "Interface/PauseMenu/SoundButtonHover.png", [&]() {std::cout << "Sound" << std::endl; }, { 1570.f, 108.f }));
		scene.push(new EngineComponents::Button("Interface/PauseMenu/MusicButton.png", "Interface/PauseMenu/MusicButtonHover.png", [&]() {std::cout << "Music" << std::endl; }, { 1795.f, 108.f }));
	}

	void generateWarningMenu(EngineComponents::GUI& scene, sf::Window& window)
	{
		scene.text.setString("WARNING!");
		scene.text.setCharacterSize(80);
		scene.setFont("Fonts/Archive.ttf");
		scene.text.setFillColor(sf::Color::Red);
		scene.sprite.setPosition({ static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2) });
		scene.text.setPosition(static_cast<float>(window.getSize().x / 2), static_cast<float>(200.f));
		scene.push(new EngineComponents::Button({ 0.7f, 0.7f }, "Interface/Buttons/Basic/Button.png", "Interface/Buttons/Basic/ButtonHover.png", [&]() {exit(EXIT_FAILURE); }, { static_cast<float>(window.getSize().x / 2), 890.f }, "OK"));
	}

	void generateLoadingMenu(EngineComponents::GUI& scene, const sf::Window& window)
	{
		scene.push(new EngineComponents::Object("", EngineComponents::TextManager("Welcome back,", "Fonts/FutureTense.ttf", 105, { static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2 - 36.f) })));
		scene.push(new EngineComponents::Object("", EngineComponents::TextManager("commander!", "Fonts/FutureTense.ttf", 105, { static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2 + 64.f) })));
		scene.push(new EngineComponents::Object("", EngineComponents::TextManager("Loading...", "Fonts/FutureTense.ttf", 23, { 115.f, 45.f })));
		scene.push(new EngineComponents::Object("", EngineComponents::TextManager("Loading...", "Fonts/FutureTense.ttf", 23, { 1015.f, 1700.f })));
		scene.push(new EngineComponents::Object("", EngineComponents::TextManager("c 2021 ELISION INC.\nALL RIGHTS RESERVED", "Fonts/Archive.ttf", 30, { 1700.f, 1015.f })));
	}
}