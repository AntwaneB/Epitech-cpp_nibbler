/*
 * File:   OpenGL3DGraphics.cpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 1:42 PM
 */

#include "OpenGL3DGraphics.hpp"

OpenGL3DGraphics::OpenGL3DGraphics()
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
	return (new OpenGL3DGraphics);
}

OpenGL3DGraphics::~OpenGL3DGraphics()
{
	TTF_CloseFont(_font);
	Mix_FreeMusic(_sound);
	Mix_FreeChunk(_cry);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

Event::Key	OpenGL3DGraphics::pollEvent(void) const
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

void*	OpenGL3DGraphics::newWindow(Position const & size, int spriteWidth, int spriteHeight)
{
	SDL_Surface		*window;
	float			sizeX;
	float			sizeY;

	_spriteWidth = spriteWidth;
	_spriteHeight = spriteHeight;
	sizeX = 2 / static_cast<float>(size.getX());
	sizeY = 2 / static_cast<float>(size.getY());
	if (sizeX < sizeY)
		_size = sizeX;
	else
		_size = sizeY;
	_maxX = size.getX() - 1;
	_maxY = size.getY() - 1;
	if ((window = SDL_SetVideoMode(size.getX() * _spriteWidth, size.getY() * _spriteHeight, 32, SDL_OPENGL)) == NULL)
		throw GraphicsException("Set Video Failed.");

	SDL_WM_SetCaption("Tu veux voir mon gros snake ?", NULL);

	glEnable(GL_DEPTH_TEST);
//	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glRotatef(-45, 1.0, 0.0, 0.0);
	glRotatef(-45, 0.0, 1.0, 0.0);
	glScalef(0.7, 0.7, 0.7);

	return (window);
}

void	OpenGL3DGraphics::winRefresh(void* window)
{
	(void)window;
	glFlush();
	SDL_GL_SwapBuffers();
}

void	OpenGL3DGraphics::reset(void* window)
{
	(void)window;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glFlush();
	SDL_GL_SwapBuffers();
}

float	OpenGL3DGraphics::convertX(float x) const
{
	float	res;

	res = -1;
	res += (x * _size);
	return (res);
}

float	OpenGL3DGraphics::convertY(float y) const
{
	float	res;

	res = 1;
	res -= (y * _size);
	return (res);
}

void	OpenGL3DGraphics::drawBlock(void* window, Position const & drawTo, Position const & drawFrom, std::string const & imgPath, int fallbackColor)
{
	this->drawBlock(window, drawTo, fallbackColor);
	(void)drawFrom;
	(void)imgPath;
}

void	OpenGL3DGraphics::drawBlock(void* window, Position const & drawTo, int color) const
{
	int	red;
	int	green;
	int	blue;
	int	redDark;
	int	greenDark;
	int	blueDark;
	float	dark;
	float	height;

	height = _size * 2;

	red = color>>16;
	green = color>>8;
	blue = color;

	dark = 50;
	redDark = red - (dark < red ? (red - dark) : 0);
	greenDark = green - (dark < green ? (green - dark) : 0);
	blueDark = blue - (dark < blue ? (blue - dark) : 0);

	if (drawTo.getX() == 0 && drawTo.getY() == 0)
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 	if (color == 0)
	{
	// DOWN
		glBegin(GL_LINE_LOOP);

		glColor3ub(100, 100, 100);

		glVertex3d(this->convertX(drawTo.getX()), 0, this->convertY(drawTo.getY() + 1));
		glVertex3d(this->convertX(drawTo.getX()), 0,this->convertY(drawTo.getY()));
		glVertex3d(this->convertX(drawTo.getX() + 1), 0,this->convertY(drawTo.getY()));
		glVertex3d(this->convertX(drawTo.getX() + 1), 0,this->convertY(drawTo.getY() + 1));

		glEnd();
		return;
	}

	// BACK
	glBegin(GL_QUADS);

	glColor3ub(red, green, blue);

	glVertex3d(this->convertX(drawTo.getX()), height,this->convertY(drawTo.getY()));
	glVertex3d(this->convertX(drawTo.getX() + 1), height,this->convertY(drawTo.getY()));

	glColor3ub(redDark, greenDark, blueDark);

	glVertex3d(this->convertX(drawTo.getX() + 1), 0,this->convertY(drawTo.getY()));
	glVertex3d(this->convertX(drawTo.getX()), 0,this->convertY(drawTo.getY()));

	glEnd();

	// glEnd();

	// DOWN
	glBegin(GL_QUADS);

	glColor3ub(red, green, blue);

	glVertex3d(this->convertX(drawTo.getX()), 0, this->convertY(drawTo.getY() + 1));
	glVertex3d(this->convertX(drawTo.getX()), 0,this->convertY(drawTo.getY()));
	glVertex3d(this->convertX(drawTo.getX() + 1), 0,this->convertY(drawTo.getY()));
	glVertex3d(this->convertX(drawTo.getX() + 1), 0,this->convertY(drawTo.getY() + 1));

	glEnd();

	// LEFT
	glBegin(GL_QUADS);

	glColor3ub(red, green, blue);

	glVertex3d(this->convertX(drawTo.getX()), height,this->convertY(drawTo.getY()));
	glVertex3d(this->convertX(drawTo.getX()), height, this->convertY(drawTo.getY() + 1));

	glColor3ub(redDark, greenDark, blueDark);

	glVertex3d(this->convertX(drawTo.getX()), 0, this->convertY(drawTo.getY() + 1));
	glVertex3d(this->convertX(drawTo.getX()), 0,this->convertY(drawTo.getY()));

	glEnd();

	// RIGHT
	glBegin(GL_QUADS);

	glColor3ub(red, green, blue);

	glVertex3d(this->convertX(drawTo.getX() + 1), height,this->convertY(drawTo.getY()));
	glVertex3d(this->convertX(drawTo.getX() + 1), height, this->convertY(drawTo.getY() + 1));

	glColor3ub(redDark, greenDark, blueDark);

	glVertex3d(this->convertX(drawTo.getX() + 1), 0, this->convertY(drawTo.getY() + 1));
	glVertex3d(this->convertX(drawTo.getX() + 1), 0,this->convertY(drawTo.getY()));

	glEnd();

	// FRONT
	glBegin(GL_QUADS);

	glColor3ub(red, green, blue);

	glVertex3d(this->convertX(drawTo.getX() + 1), height, this->convertY(drawTo.getY() + 1));
	glVertex3d(this->convertX(drawTo.getX()), height, this->convertY(drawTo.getY() + 1));

	glColor3ub(redDark, greenDark, blueDark);

	glVertex3d(this->convertX(drawTo.getX()), 0,this->convertY(drawTo.getY() + 1));
	glVertex3d(this->convertX(drawTo.getX() + 1), 0,this->convertY(drawTo.getY() + 1));

	glEnd();

	// UP
	glBegin(GL_QUADS);

	glColor3ub(red, green, blue);

	glVertex3d(this->convertX(drawTo.getX()), height, this->convertY(drawTo.getY() + 1));
	glVertex3d(this->convertX(drawTo.getX()), height,this->convertY(drawTo.getY()));
	glVertex3d(this->convertX(drawTo.getX() + 1), height,this->convertY(drawTo.getY()));
	glVertex3d(this->convertX(drawTo.getX() + 1), height,this->convertY(drawTo.getY() + 1));

	glEnd();

	(void)window;
}

void	OpenGL3DGraphics::drawScore(void *window)
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

void	OpenGL3DGraphics::setScore(long score)
{
	Mix_PlayChannel(0, this->_cry, 0);
	_score = score;
}
