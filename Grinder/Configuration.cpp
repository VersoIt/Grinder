#include "Configuration.hpp"

namespace Utility
{
	int showWarningMenu(EngineComponents::GUI& warningMenu, const char* what, const char* request, sf::RenderWindow& window, sf::Event& event)
	{
		sf::RectangleShape backgroundMenu({ 880.f, 1080.f });
		backgroundMenu.setOrigin(backgroundMenu.getSize().x / 2, backgroundMenu.getSize().y / 2);
		backgroundMenu.setFillColor(sf::Color(0, 0, 0, 128));
		backgroundMenu.setPosition(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2));

		EngineComponents::RenderObject* excText = new EngineComponents::RenderObject("", what);
		excText->getText().setCharacterSize(backgroundMenu.getSize().x / 17.2);
		excText->setFont("Fonts/Archive.ttf");

		EngineComponents::RenderObject* askText = new EngineComponents::RenderObject(*excText);
		askText->setString(request);

		warningMenu.push(excText);
		warningMenu.push(askText);

		excText->getText().setPosition(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2));
		askText->getText().setPosition(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2 + excText->getText().getLocalBounds().height * 1.5));
		askText->getText().setFillColor(sf::Color(255, 252, 0));

		EngineComponents::SpriteManager backgroundSprite("");

		try
		{
			backgroundSprite.setTexture("Interface/MainMenu/Background.png");
		}
		catch (EngineComponents::FileMissing& exc)
		{
		}


		sf::RectangleShape background({ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) });
		background.setFillColor(sf::Color(0.f, 0.f, 0.f, 128.f));

		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				warningMenu.catchMouseEvent(event, sf::Mouse::getPosition());
				if (event.type == sf::Event::Closed)
				{
					window.close();
					return EXIT_FAILURE;
				}
			}

			window.clear();
			window.draw(backgroundSprite);
			window.draw(background);
			window.draw(backgroundMenu);
			window.draw(warningMenu);
			window.display();

		}
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
		return 80;
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
}