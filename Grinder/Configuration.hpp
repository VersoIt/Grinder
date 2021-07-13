#pragma once
#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "GUI.hpp"
#include "ScrollField.hpp"
#include "Exceptions.hpp"
#include "tinyxml2.h"

namespace Utility
{
	enum class Gui
	{
		MAIN,
		SETTINGS,
		PAUSE,
		GAME
	};

	int showWarningMenu(EngineComponents::GUI& warningMenu, const char* what, const char* request, sf::RenderWindow& window, sf::Event& event);

	void saveSettings(const char* path, EngineComponents::ScrollField& musicSettings, const char* element);

	int loadSettings(const char* path, const char* element);

	void generateSettingsXML(const char* fileName);

	void generateMainMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus);

	void generateSettingsMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus);

	void generatePauseMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus);

	void generateConfirmMenu(EngineComponents::GUI& scene, sf::Window& window, Gui& focus);

	void generateWarningMenu(EngineComponents::GUI& scene, sf::Window& window);

	void generateLoadingMenu(EngineComponents::GUI& scene, const sf::Window& window);

}

#endif // _CONFIGURATION_HPP_