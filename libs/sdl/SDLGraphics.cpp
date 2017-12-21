/*
 * Author: buchse_a
 * File:   SDLGraphics.cpp
 *
 * Created on March 24, 2015, 1:42 PM
 */

#include  "SDLGraphics.hpp"

SDLGraphics::SDLGraphics()
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
	return (new SDLGraphics);
}

SDLGraphics::~SDLGraphics()
{
	TTF_CloseFont(_font);
	Mix_FreeMusic(_sound);
	Mix_FreeChunk(_cry);
  Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

Event::Key	SDLGraphics::pollEvent(void) const
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

void*	SDLGraphics::newWindow(Position const & size, int spriteWidth, int spriteHeight)
{
	_spriteWidth = spriteWidth;
	_spriteHeight = spriteHeight;

	SDL_Surface		*window;

	if ((window = SDL_SetVideoMode(size.getX() * _spriteWidth, size.getY() * _spriteHeight, 32, SDL_ANYFORMAT)) == NULL)
		throw GraphicsException("Set Video Failed.");

	SDL_WM_SetCaption("Tu veux voir mon gros snake ?", NULL);

	return (window);
}

void	SDLGraphics::winRefresh(void* window)
{
	SDL_Flip(static_cast<SDL_Surface*>(window));
}

void	SDLGraphics::reset(void* window)
{
	(void)window;
}

void	SDLGraphics::drawBlock(void* window, Position const & drawTo, Position const & drawFrom, std::string const & imgPath, int fallbackColor)
{
	std::map<std::string, SDL_Surface*>::const_iterator	it;
	SDL_Surface*														image = NULL;

	if (!_images.empty() && (it = _images.find(imgPath)) != _images.end())
	{ // L'image est déjà chargée, elle est stockée dans it->second
		image = it->second;
	}
	else
	{ // L'image n'est pas encore loadée, on la charge
		if ((image = IMG_Load(imgPath.c_str())) == NULL)
			this->drawBlock(window, drawTo, fallbackColor);
		else
			_images.insert(std::map<std::string, SDL_Surface*>::value_type(imgPath, image));
	}

	if (image)
	{ // Sinon c'est qu'on a dessiné un carré de fallbackColor à la place
		SDL_Rect			to;
		SDL_Rect			from;

		from.x = drawFrom.getX() * _spriteWidth;
		from.y = drawFrom.getY() * _spriteHeight;
		from.w = _spriteWidth;
		from.h = _spriteHeight;
		to.x = drawTo.getX() * _spriteWidth;
		to.y = drawTo.getY() * _spriteHeight;
		SDL_BlitSurface(image, &from, static_cast<SDL_Surface*>(window), &to);
	}
}

void	SDLGraphics::drawBlock(void* window, Position const & drawTo, int color) const
{
	SDL_Rect		body;
	SDL_Surface	*win;

	win = static_cast<SDL_Surface*>(window);
	body.x = drawTo.getX() * _spriteWidth;
	body.y = drawTo.getY() * _spriteHeight;
	body.w = _spriteWidth;
	body.h = _spriteHeight;

	/*TODO couleur rgb a changer*/
	SDL_FillRect(win, &body, SDL_MapRGB(win->format, 255, 0, 0));
	(void)color;
}

void	SDLGraphics::drawScore(void *window)
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

void	SDLGraphics::setScore(long score)
{
	Mix_PlayChannel(0, this->_cry, 0);
	_score = score;
}
