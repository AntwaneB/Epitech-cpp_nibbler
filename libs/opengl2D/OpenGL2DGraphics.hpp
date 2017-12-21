/*
 * File:   OpenGLGraphics.hpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 1:42 PM
 */

#ifndef OPENGL2DGRAPHICS_HPP
#define	OPENGL2DGRAPHICS_HPP

#include "IGraphics.hpp"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include <iostream>
#include <sstream>
#include <map>


class OpenGL2DGraphics : public IGraphics
{
public:
	OpenGL2DGraphics();
	virtual ~OpenGL2DGraphics();

	virtual void*	newWindow(Position const & size, int, int);
	virtual void	winRefresh(void* window);
	virtual void	reset(void* window);

	virtual Event::Key	pollEvent(void) const;

	virtual void	drawBlock(void* window, Position const & drawTo, Position const & drawFrom, std::string const & imgPath, int fallbackColor);

	virtual void	setScore(long score);
	virtual void	drawScore(void*);

private:
	virtual void	drawBlock(void* window, Position const & drawTo, int color) const;
	float			convertX(float) const;
	float			convertY(float) const;

private:
	long											_score;
	TTF_Font									*_font;
	Mix_Music 								*_sound;
	Mix_Chunk									*_cry;
	std::map<std::string, SDL_Surface*>	_images;
	float								_sizeX;
	float								_sizeY;
};

#endif	/* OPENGL2DGRAPHICS_HPP */
