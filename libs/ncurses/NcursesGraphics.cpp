/*
 * File:   NcursesGraphics.cpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 1:42 PM
 */

#include <iostream>
#include "NcursesGraphics.hpp"

NcursesGraphics::NcursesGraphics()
	: _infosWindow(NULL)
{
	initscr();

	start_color();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_WHITE);
	init_pair(4, COLOR_GREEN, COLOR_GREEN);
	init_pair(5, COLOR_BLUE, COLOR_BLUE);
	init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
}

extern "C" void* newIGraphics(void)
{
	return (new NcursesGraphics);
}

NcursesGraphics::~NcursesGraphics()
{
	endwin();
}

void NcursesGraphics::error(std::string const & e)
{
	endwin();
	throw GraphicsException(e);
}

Event::Key	NcursesGraphics::pollEvent(void) const
{
	int			key;
	Event::Key	event;

	key = getch();

	switch (key)
	{
		case KEY_UP:
			event = Event::UP;
			break;
		case KEY_DOWN:
			event = Event::DOWN;
			break;
		case KEY_LEFT:
			event = Event::LEFT;
			break;
		case KEY_RIGHT:
			event = Event::RIGHT;
			break;
		case 27:
			event = Event::ESC;
			break;

		default:
			event = Event::UNKNOWN;
			break;
	}
	return (event);
}

void*	NcursesGraphics::newWindow(Position const & size, int spriteWidth, int spriteHeight)
{
	if (_infosWindow)
	{
		delwin(_infosWindow);
		_infosWindow = NULL;
	}

	_spriteWidth = spriteWidth > 4 ? 2 : spriteWidth;
	_spriteHeight = spriteHeight > 2 ? 1 : spriteHeight;

	int	h;
	int	w;

   getmaxyx(stdscr, h, w);

	int	x = size.getX() * _spriteWidth + 2;
	int	y = size.getY() * _spriteHeight + 2;
	if (x > w || y > h)
		error("Window too large for the screen.");

	WINDOW*	window = newwin(y, x, (h - y) / 2, (w - x) / 2);
	if (!window)
		error("Couldn't create new window.");

	box(window, 0, 0);

	return (window);
}

void	NcursesGraphics::winRefresh(void* window)
{
	refresh();
	wrefresh(static_cast<WINDOW*>(window));
}

void	NcursesGraphics::reset(void* window)
{
	wrefresh(static_cast<WINDOW*>(window));
}

void	NcursesGraphics::drawBlock(void* window, Position const & drawTo, Position const & drawFrom, std::string const & imgPath, int fallbackColor)
{
	(void)drawFrom;
	(void)imgPath;
	drawBlock(window, drawTo, fallbackColor);
}

void	NcursesGraphics::drawBlock(void* window, Position const & drawTo, int color) const
{
	int pairNb;

	switch (color)
	{
		case 0xff0000:
			pairNb = 1;
			break;

		case 0x000000:
			pairNb = 2;
			break;

		case 0xffffff:
			pairNb = 3;
			break;

		case 0x00ff00:
			pairNb = 4;
			break;

		case 0x0000ff:
			pairNb = 5;
			break;

		case 0xffff00:
			pairNb = 6;
			break;

		default:
			pairNb = 2;
			break;
	}

	for (int j = 0; j < _spriteHeight; j++)
	{
		for (int i = 0; i < _spriteWidth; i++)
		{
			mvwaddch(static_cast<WINDOW*>(window), drawTo.getY() * _spriteHeight + j + 1, drawTo.getX() * _spriteWidth + i + 1, 'X' | COLOR_PAIR(pairNb));
		}
	}
}

void	NcursesGraphics::setScore(long score)
{
	_score = score;
}

void	NcursesGraphics::drawScore(void* window)
{
	int	x;
	int	y;
	getmaxyx(static_cast<WINDOW*>(window), y, x);

	if (!_infosWindow)
	{

		int	h;
		int	w;
		getmaxyx(stdscr, h, w);
		(void)h;

		_infosWindow = newwin(3, x, h / 2 - y / 2 - 3, w / 2 - x / 2);
		if (!_infosWindow)
			error("Couldn't create new window.");

		box(_infosWindow, 0, 0);
	}

	std::string scoreStr = "Score : ";
	scoreStr = scoreStr + std::to_string(_score);
	int size = scoreStr.size();
	for (int i = 0; i < x - size - 3; i++) // Cleaning whole line
		scoreStr += ' ';
	wmove(_infosWindow, 1, 2);
	waddstr(_infosWindow, scoreStr.c_str());
	wrefresh(_infosWindow);
}

