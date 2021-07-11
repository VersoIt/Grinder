#pragma once
#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include <iostream>
#include <string>

#include "GUI.hpp"
#include "ScrollField.hpp"
#include "Exceptions.hpp"
#include "tinyxml2.h"

namespace Utility
{
	int showWarningMenu(EngineComponents::GUI& warningMenu, const char* what, const char* request, sf::RenderWindow& window, sf::Event& event);
	void saveSettings(const char* path, EngineComponents::ScrollField& musicSettings, const char* element);
	int loadSettings(const char* path, const char* element);
	void generateSettingsXML(const char* fileName);
}

#endif // _CONFIGURATION_HPP_