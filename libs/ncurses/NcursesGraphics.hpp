/*
 * File:   NcursesGraphics.hpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 1:42 PM
 */

#ifndef NCURSESGRAPHICS_HPP
#define	NCURSESGRAPHICS_HPP

#include <curses.h>
#include <ncurses.h>
#include "IGraphics.hpp"

class NcursesGraphics : public IGraphics
{
public:
	NcursesGraphics();
	virtual ~NcursesGraphics();

	virtual void*	newWindow(Position const & size, int, int);
	virtual void	winRefresh(void* window);
	virtual void	reset(void* window);

	virtual Event::Key	pollEvent(void) const;

	virtual void	drawBlock(void* window, Position const &, Position const &, std::string const &, int);

	virtual void	setScore(long score);
	virtual void	drawScore(void* window);

private:
	virtual void	drawBlock(void* window, Position const & drawTo, int color) const;
	void				error(std::string const & e);

private:
	long		_score;
	WINDOW*	_infosWindow;
};

#endif	/* NCURSESGRAPHICS_HPP */
