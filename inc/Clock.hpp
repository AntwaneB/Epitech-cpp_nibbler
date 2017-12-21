/*
 * File:   Clock.hpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 1:27 PM
 */

#ifndef CLOCK_HPP
#define	CLOCK_HPP

#include <time.h>
#include "Snake.hpp"
#include "Level.hpp"

class Clock
{
public:
	Clock();
	virtual ~Clock();

	clock_t	getTimer(void) const;
	bool		tick(Level &);
	clock_t	elapsedTime(void) const;
	void		restart(void);

private:
	bool		collideWithSnake(AEntity* entity, Snake* other) const;

private:
	clock_t	_timer;
};

#endif	/* CLOCK_HPP */
