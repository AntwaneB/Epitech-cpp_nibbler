/*
 * File:   EventHandler.hpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 8:46 PM
 */

#ifndef EVENTHANDLER_HPP
#define	EVENTHANDLER_HPP

#include "IGraphics.hpp"
#include "Snake.hpp"
#include "Level.hpp"
#include "Event.hpp"

class EventHandler
{
public:
	virtual ~EventHandler();

	static bool	handle(Level*, IGraphics*, Event::Key);
	static void	drawLevel(IGraphics* drawer, void* window, Level & level);
	static void	drawSnake(IGraphics* drawer, void* window, Snake* snake, std::string const & tilesetPath);

private:
	EventHandler() {};

};

#endif	/* EVENTHANDLER_HPP */
