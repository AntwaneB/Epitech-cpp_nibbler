/*
 * File:   OpenGL2DGraphics.cpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 1:42 PM
 */

#include "OpenGL2DGraphics.hpp"

OpenGL2DGraphics::OpenGL2DGraphics()
{
	_score = 0;

	if (XInitThreads() == 0)
		throw GraphicsException("XInit Failed.");
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw GraphicsException("Init Failed.");
	if(TTF_Init() == -1)
	   throw GraphicsException(TTF_GetError());
	this->_font = TTF_OpenFont("assets/Chicken Butt.ttf", 35);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		throw GraphicsException(Mix_GetError());
	this->_sound = Mix_LoadMUS("assets/nibbler.ogg");
	Mix_PlayMusic(this->_sound, -1);
	Mix_AllocateChannels(1);
	Mix_Volume(0, MIX_MAX_VOLUME/2);
	this->_cry = Mix_LoadWAV("assets/murloc.wav");
	Mix_VolumeChunk(this->_cry, MIX_MAX_VOLUME);
}

extern "C" void* newIGraphics(void)
{
	return (new OpenGL2DGraphics);
}

OpenGL2DGraphics::~OpenGL2DGraphics()
{
	TTF_CloseFont(_font);
	Mix_FreeMusic(_sound);
	Mix_FreeChunk(_cry);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

Event::Key	OpenGL2DGraphics::pollEvent(void) const
{
	SDL_Event	event;
	Event::Key	ev;

	ev = Event::UNKNOWN;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					ev = Event::ESC;
					break;

				case SDLK_UP:
					ev = Event::UP;
					break;

				case SDLK_DOWN:
					ev = Event::DOWN;
					break;

				case SDLK_LEFT:
					ev = Event::LEFT;
					break;

				case SDLK_RIGHT:
					ev = Event::RIGHT;
					break;

				default:
					ev = Event::UNKNOWN;
					break;
			}
		}
	}
	return (ev);
}

void*	OpenGL2DGraphics::newWindow(Position const & size, int spriteWidth, int spriteHeight)
{
	SDL_Surface		*window;

	_spriteWidth = spriteWidth;
	_spriteHeight = spriteHeight;
	_sizeX = 2 / static_cast<float>(size.getX());
	_sizeY = 2 / static_cast<float>(size.getY());

	if ((window = SDL_SetVideoMode(size.getX() * _spriteWidth, size.getY() * _spriteHeight, 32, SDL_OPENGL)) == NULL)
		throw GraphicsException("Set Video Failed.");

	SDL_WM_SetCaption("Tu veux voir mon gros snake ?", NULL);

	glClear(GL_COLOR_BUFFER_BIT);

	return (window);
}

void	OpenGL2DGraphics::winRefresh(void* window)
{
	(void)window;
	glFlush();
	SDL_GL_SwapBuffers();
}

void	OpenGL2DGraphics::reset(void* window)
{
	(void)window;
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	SDL_GL_SwapBuffers();
}

float	OpenGL2DGraphics::convertX(float x) const
{
	float	res;

	res = -1;
	res += (x * _sizeX);
	return (res);
}

float	OpenGL2DGraphics::convertY(float y) const
{
	float	res;

	res = 1;
	res -= (y * _sizeY);
	return (res);
}

void	OpenGL2DGraphics::drawBlock(void* window, Position const & drawTo, Position const & drawFrom, std::string const & imgPath, int fallbackColor)
{
	this->drawBlock(window, drawTo, fallbackColor);
	(void)drawFrom;
	(void)imgPath;
}

void	OpenGL2DGraphics::drawBlock(void* window, Position const & drawTo, int color) const
{
	int	red;
	int	green;
	int	blue;

	red = color>>16;
	green = color>>8;
	blue = color;

	glBegin(GL_QUADS);

	glColor3ub(red, green, blue);

	glVertex2d(this->convertX(drawTo.getX()), this->convertY(drawTo.getY() + 1));
	glVertex2d(this->convertX(drawTo.getX()), this->convertY(drawTo.getY()));
	glVertex2d(this->convertX(drawTo.getX() + 1), this->convertY(drawTo.getY()));
	glVertex2d(this->convertX(drawTo.getX() + 1), this->convertY(drawTo.getY() + 1));

	glEnd();

	if (color == 0)
	{
		glBegin(GL_LINE_LOOP);

		glColor3ub(50, 50, 50);

		glVertex2d(this->convertX(drawTo.getX()), this->convertY(drawTo.getY() + 1));
		glVertex2d(this->convertX(drawTo.getX()), this->convertY(drawTo.getY()));
		glVertex2d(this->convertX(drawTo.getX() + 1), this->convertY(drawTo.getY()));
		glVertex2d(this->convertX(drawTo.getX() + 1), this->convertY(drawTo.getY() + 1));

		glEnd();
	}

	(void)window;
}

void	OpenGL2DGraphics::drawScore(void *window)
{
	SDL_Surface *win;
	SDL_Surface *text;
	SDL_Rect		pos;
	std::string result;
	std::stringstream sstm;

	sstm << "Score : ";
	sstm << _score;
	result = sstm.str();

	pos.x = 2;
	pos.y = -3;
	win = static_cast<SDL_Surface*>(window);
	SDL_Color col = {0, 0, 0, 0};
	text = TTF_RenderText_Blended(this->_font, result.c_str(), col);
	SDL_BlitSurface(text, NULL, win, &pos);
	pos.x = 0;
	pos.y = -5;
	col = {53, 97, 37, 0};
	text = TTF_RenderText_Blended(this->_font, result.c_str(), col);
	SDL_BlitSurface(text, NULL, win, &pos);
}

void	OpenGL2DGraphics::setScore(long score)
{
	Mix_PlayChannel(0, this->_cry, 0);
	_score = score;
}
