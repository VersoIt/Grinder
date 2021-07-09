#include "Configuration.hpp"

namespace Utility
{
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