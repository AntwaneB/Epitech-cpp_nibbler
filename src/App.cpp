/*
 ** App.cpp
 **
 ** Made by Antoine Buchser
 ** Login   <buchse_a@epitech.eu>
 **
 ** Started on February 6, 2015, 10:53 AM Antoine Buchser
 ** Updated on February 6, 2015, 10:53 AM Antoine Buchser
 */

#include <iostream>
#include <unistd.h>
#include <dlfcn.h>
#include "Config.hpp"
#include "Exception.hpp"
#include "App.hpp"
#include "IGraphics.hpp"
#include "Clock.hpp"
#include "EventHandler.hpp"

App::App(int ac, char** av)
	: _ac(ac), _av(av), _libHandler(NULL), _IGraphCtor(NULL)
{
	if (!this->validateArgs())
		throw NoDeleteException("usage:\n" \
								  "   ./nibbler width(10+) height(10+) lib_nibbler_***.so\n" \
								  "   ./nibbler configFile.xml");

	_mode = _ac == 2 ? App::CONFIG : App::ARGS;

	if (_mode == App::CONFIG)
		Config::get().parseConfig(_av[1]);
	else
		Config::get().parseConfig("configurations/default.xml");

	std::string libPath = _mode == App::CONFIG ? Config::get().getValue<std::string>("tileset.library") : _av[3];
	libPath = _mode == App::CONFIG ? libPath : "./" + libPath;

	if ((_libHandler = dlopen(libPath.c_str(), RTLD_LAZY)) == NULL)
		throw InitException(dlerror());

	if ((_IGraphCtor = reinterpret_cast<IGraphics*(*)(void)>(dlsym(_libHandler, "newIGraphics"))) == NULL)
		throw InitException(dlerror());
}

App::~App()
{
	if (this)
	{
		if (_libHandler)
			dlclose(_libHandler);
	}
}

bool	App::validateArgs() const
{
	if (_ac == 4)
	{
		for (size_t i = 0; _av[1][i]; i++)
			if (!isdigit(_av[1][i]))
				return (false);
		for (size_t i = 0; _av[2][i]; i++)
			if (!isdigit(_av[2][i]))
				return (false);
		if (atoi(_av[1]) < 10 || atoi(_av[2]) < 10)
			return (false);

		std::string lib = std::string(_av[3]);
		if (lib.find("lib_nibbler_") != 0)
			return (false);
		if (lib.find(".so") != lib.size() - 3)
			return (false);
		if (lib.size() <= 15)
			return (false);

		if (access(lib.c_str(), R_OK) == -1)
			return (false);
	}
	else if (_ac == 2)
	{
		std::string config = std::string(_av[1]);
		if (config.find(".xml") != config.size() - 4)
			return (false);
		if (config.size() <= 4)
			return (false);

		if (access(config.c_str(), R_OK) == -1)
			return (false);
	}
	else
		return (false);

	return (true);
}

bool	App::loop(IGraphics* drawer, std::string const & levelFile) const
{
	Clock			clock;
	Event::Key	event;
	Level			level;

	if (_mode == App::CONFIG)
		level = Level(levelFile);
	else
		level = Level(atoi(_av[1]), atoi(_av[2]));

	int spriteWidth = Config::get().getValue<int>("tileset.block_width");
	int spriteHeight = Config::get().getValue<int>("tileset.block_height");
	void*	window = drawer->newWindow(Position(level.getWidth(), level.getHeight()), spriteWidth, spriteHeight);
	drawer->winRefresh(window);

	EventHandler::drawLevel(drawer, window, level);

	try
	{
		while ("supernaturalc'esttropbien") // c'est à dire "toujours"
		{
			if ((event = drawer->pollEvent()) != Event::UNKNOWN)
			{
				if (!(EventHandler::handle(&level, drawer, event)))
					return (false);
			}
			if (clock.tick(level))
			{
				EventHandler::drawLevel(drawer, window, level);
				drawer->winRefresh(window);
			}
		}
	} catch (DeathException const & e) {
		return (true);
	} catch (ExitException const & e) {
		return (false);
	}
	return (true);
}

bool	App::replay(std::string & levelFile) const
{
	(void)levelFile;

	return (false);
}

int	App::run() const
{
	bool promptReplay;
	bool play = true;

	IGraphics* drawer = (_IGraphCtor)();

	std::string levelFile = Config::get().getValue<std::string>("tileset.start_level");
	while (play && (promptReplay = this->loop(drawer, levelFile)) == true)
	{
		play = this->replay(levelFile);
	}

	delete drawer;

	return (0);
}
