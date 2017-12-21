/*
 ** App.hpp
 **
 ** Made by Antoine Buchser
 ** Login   <buchse_a@epitech.eu>
 **
 ** Started on February 6, 2015, 10:53 AM Antoine Buchser
 ** Updated on February 6, 2015, 10:53 AM Antoine Buchser
 */

#ifndef APP_HPP
#define	APP_HPP

#include <string>
#include "IGraphics.hpp"

class App
{
public:
	enum mode { CONFIG, ARGS };

public:
	App(int, char**);
	~App();

	int	run(void) const;

private:
	bool	validateArgs(void) const;
	bool	loop(IGraphics*, std::string const &) const;
	bool	replay(std::string & levelFile) const;

private:
	int			_ac;
	char**		_av;
	void*			_libHandler;
	App::mode	_mode;
	IGraphics*	(*_IGraphCtor)(void);
};

#endif /* !APP_HPP */
