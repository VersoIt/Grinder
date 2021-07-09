#pragma once
#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include <iostream>
#include <string>

#include "ScrollField.hpp"
#include "Exceptions.hpp"
#include "tinyxml2.h"

namespace Utility
{
	void saveSettings(const char* path, EngineComponents::ScrollField& musicSettings, const char* element);
	int loadSettings(const char* path, const char* element);
	void generateSettingsXML(const char* fileName);
}

#endif // _CONFIGURATION_HPP_