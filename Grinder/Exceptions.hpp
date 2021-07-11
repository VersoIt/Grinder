#pragma once
#ifndef _EXCEPTIONS_HPP_
#define _EXCEPTIONS_HPP_

#include <stdexcept>

namespace EngineComponents
{
	class SettingsFileMissing : public std::exception
	{
	public:
		SettingsFileMissing(const char* msg) : std::exception(msg)
		{
		}

	private:

	};

	class FileMissing : public std::exception
	{
	public:
		FileMissing(const char* msg) : std::exception(msg)
		{
		}

	private:

	};

}

#endif // _EXCEPTIONS_HPP_