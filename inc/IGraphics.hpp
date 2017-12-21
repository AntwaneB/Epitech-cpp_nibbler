/*
 * File:   IGraphics.hpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 12:45 PM
 */

#ifndef IGRAPHICS_HPP
#define	IGRAPHICS_HPP

#include <string>
#include "Exception.hpp"
#include "Position.hpp"
#include "Config.hpp"
#include "Event.hpp"

class IGraphics
{
public:
	virtual ~IGraphics();

	virtual void*	newWindow(Position const & size, int, int) = 0;
	virtual void	winRefresh(void* window) = 0;
	virtual void	reset(void* window) = 0;

	virtual Event::Key	pollEvent(void) const = 0;

	virtual void	drawBlock(void* window, Position const & drawTo, Position const & drawFrom, std::string const & imgPath, int fallbackColor) = 0;

	virtual void	setScore(long score) = 0;
	virtual void	drawScore(void* window) = 0;

private:
	virtual void	drawBlock(void* window, Position const & drawTo, int color) const = 0;

private:
	long	_score;

protected:
	int _spriteWidth;
	int _spriteHeight;
};

#endif	/* IGRAPHICS_HPP */
