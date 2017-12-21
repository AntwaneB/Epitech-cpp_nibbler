/*
 * File:   EventHandler.cpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 8:46 PM
 */

#include <iostream>
#include "Config.hpp"
#include "Exception.hpp"
#include "EventHandler.hpp"

EventHandler::~EventHandler()
{
}

bool	EventHandler::handle(Level* level, IGraphics* drawer, Event::Key event)
{
	(void)level;
	(void)drawer;

	switch (event)
	{
		case Event::ESC:
			throw ExitException("ESC key pressed.");
			break;

		case Event::RIGHT:
		case Event::LEFT:
		{
			std::list<AEntity*>	entities = level->getEntities();
			for (std::list<AEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			{
				if ((*it)->getType() == AEntity::SNAKE)
				{
					Snake*	snake = dynamic_cast<Snake*>(*it);
					if (!level->controlsInverted())
					{
						if (event == Event::RIGHT)
							snake->rotateRight();
						else
							snake->rotateLeft();
					}
					else
					{
						if (event == Event::RIGHT)
							snake->rotateLeft();
						else
							snake->rotateRight();
					}
				}
			}
			break;
		}

		default:
			return (true);
			break;
	}
	return (true);
}


void	EventHandler::drawLevel(IGraphics* drawer, void* window, Level& level)
{
	static int oldScore = 0;

	std::string tilesetPath = level.getTilesetPath();

	std::vector<std::vector<Block*> > map = level.getMap();

	size_t height = map.size();
	for (size_t y = 0; y < height; y++)
	{
		size_t width = map[y].size();
		for (size_t x = 0; x < width; x++)
		{
			Block*	block = map[y][x];
			if (block)
				drawer->drawBlock(window, block->getPosition(), block->getSprite(), tilesetPath, block->getColor());
		}
	}

	std::list<AEntity*> entities = level.entities();
	for (std::list<AEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		AEntity*	entity = *it;

		if (entity->getExists())
		{
			if (entity->getType() == AEntity::SNAKE)
				EventHandler::drawSnake(drawer, window, static_cast<Snake*>(entity), tilesetPath);
			else
				drawer->drawBlock(window, entity->getPosition(), entity->getSprite(), tilesetPath, entity->getColor());
		}
	}

	if (level.getScore() != oldScore)
	{
		oldScore = level.getScore();
		drawer->setScore(oldScore);
	}
	drawer->drawScore(window);
	drawer->winRefresh(window);
}

void	EventHandler::drawSnake(IGraphics* drawer, void* window, Snake* snake, std::string const & tilesetPath)
{
	std::list<Snake::Segment*>	segments = snake->getSegments();

	for (std::list<Snake::Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
	{
		drawer->drawBlock(window, (*it)->getPosition(), (*it)->getSprite(), tilesetPath, (*it)->getColor());
	}
}
