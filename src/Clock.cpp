/*
 * File:   Clock.cpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 1:27 PM
 */

#include "Food.hpp"
#include "Clock.hpp"

Clock::Clock()
{
	_timer = clock();
}

Clock::~Clock()
{
}

clock_t	Clock::getTimer() const
{
	return (_timer);
}

clock_t	Clock::elapsedTime() const
{
	return (clock() - _timer);
}

void	Clock::restart()
{
	_timer = clock();
}

#include <iostream>
bool	Clock::tick(Level & level)
{
	bool						eventHappened = false;
	static long double	total = 0;
	static unsigned long	deciseconds = 0;
	Food*						foodEaten = NULL;

	double					speedModifier = level.getSpeedModifier();

	total += this->elapsedTime() / static_cast<double>(CLOCKS_PER_SEC);
	if (static_cast<int>(total * 100 * 2) - deciseconds >= 1)
	{
		deciseconds++;

		/*
		** Triggering events
		*/
		std::list<AEntity*>	entities = level.entities();
		for (std::list<AEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			AEntity*	entity = *it;

			int	realSpeed = static_cast<double>(entity->getSpeed()) * speedModifier;
			realSpeed = realSpeed > 1000 ? 1000 : realSpeed;
			if (entity->getExists() && entity->getSpeed() != 0 && deciseconds % (1000 / realSpeed) == 0)
			{
				entity->move();
				eventHappened = true;

				std::list<AEntity*>						entitiesTmp = level.entities();
				for (std::list<AEntity*>::iterator	jt = entitiesTmp.begin(); jt != entitiesTmp.end(); ++jt)
				{
					AEntity*	entityTmp = *jt;

					if (entityTmp->getExists() && ((entityTmp->getType() == AEntity::SNAKE && collideWithSnake(entity, static_cast<Snake*>(entityTmp)))
						|| (entityTmp->getPosition() == entity->getPosition() && entityTmp != entity)))
					{
						entity->collide(*entityTmp);
						entityTmp->collide(*entity);
						if (entityTmp->getType() == AEntity::FOOD)
							foodEaten = static_cast<Food*>(entityTmp);
					}
				}

				if (entity->getPosition().getY() >= 0  && entity->getPosition().getX() >= 0
					 && entity->getPosition().getY() < level.getHeight() && entity->getPosition().getX() < level.getWidth())
				{
					std::vector<std::vector<Block*> >	map = level.map();
					Block*	block = map[entity->getPosition().getY()][entity->getPosition().getX()];
					if (block->getIsSolid())
						entity->collide(*block);
				}
			}
		}

	}

	if (foodEaten != NULL)
	{
		level.incScore(foodEaten->getScoreAmount());
		level.generateFood();
		level.invertControls(foodEaten->invertControls());
		level.modifySpeed(foodEaten->getSpeedModifier());
	}

	this->restart();

	return (eventHappened);
}

bool	Clock::collideWithSnake(AEntity* entity, Snake* other) const
{
	std::list<Snake::Segment*>	segments = other->getSegments();
	bool	collide = false;

	std::list<Snake::Segment*>::iterator it = segments.begin();
	++it;
	for (it = it; it != segments.end() && !collide; ++it)
	{
		if (*it != entity && (*it)->getPosition() == entity->getPosition())
			collide = true;
	}

	return (collide);
}
