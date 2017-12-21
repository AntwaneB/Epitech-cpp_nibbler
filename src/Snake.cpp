/*
 * File:   Snake.cpp
 * Author: buchse_a
 *
 * Created on March 21, 2015, 2:07 PM
 */

#include <iostream>
#include "Config.hpp"
#include "Exception.hpp"
#include "Snake.hpp"
#include "Food.hpp"

/*
 * CLASS Snake
 */

Snake::Snake()
	: _isAlive(true), _direction(LEFT)
{
	_exists = true;
	_type = AEntity::SNAKE;
	_typeName = "huge snake (you actually ate yourself)";
	setSpeed(Config::get().getValue<int>("entities.player.speed"));

	int size = Config::get().getValue<int>("entities.player.base_size");
	size = size == 0 ? 4 : size;
	for (int i = 0; i < size; i++)
		this->addSegment(NULL);

	setPosition(_segments.front()->getPosition());

	_actions.insert(std::map<AEntity::EntityType, bool (Snake::*)(AEntity const &)>::value_type(AEntity::SNAKE, &Snake::die));
	_actions.insert(std::map<AEntity::EntityType, bool (Snake::*)(AEntity const &)>::value_type(AEntity::SNAKESEGMENT, &Snake::die));
	_actions.insert(std::map<AEntity::EntityType, bool (Snake::*)(AEntity const &)>::value_type(AEntity::BLOCK, &Snake::die));
	_actions.insert(std::map<AEntity::EntityType, bool (Snake::*)(AEntity const &)>::value_type(AEntity::FOOD, &Snake::eat));
}

Snake::~Snake()
{
	if (this)
	{
		for (std::list<Snake::Segment*>::iterator it = _segments.begin(); it != _segments.end(); ++it)
		{
			delete *it;
		}
		_segments.clear();
	}
}

/*
 * Utiliser le fichier de config XML plutôt que config.hpp
 */
bool	Snake::addSegment(AEntity const * newBlock)
{
	(void)newBlock;
	int	gameWidth = Config::get().getValue<int>("level.width");
	int	gameHeight = Config::get().getValue<int>("level.height");

	if (_segments.empty())
	{
		size_t x = gameWidth / 2 - 2;
		size_t y = gameHeight / 2;
		_segments.push_back(new Snake::Segment(this, x, y));
	}
	else
	{
		Position position = _segments.back()->getPrevPosition();
		if (!position.isSet())
		{
			Position prevBlockPos = _segments.back()->getPosition();
			position = prevBlockPos;
			if (prevBlockPos.getX() < gameWidth - 1)
				position.setX(prevBlockPos.getX() + 1);
			else if (prevBlockPos.getY() < gameHeight - 1)
				position.setY(prevBlockPos.getY() + 1);
			else if (prevBlockPos.getX() > 1)
				position.setY(prevBlockPos.getX() - 1);
			else if (prevBlockPos.getY() > 1)
				position.setY(prevBlockPos.getY() - 1);
			else
				throw MovementException("Cannot add new segment to the snake.");
		}
		_segments.push_back(new Snake::Segment(this, position));
	}
	return (true);
}

bool	Snake::removeSegment(size_t count)
{
	if (_segments.empty())
		throw DeathException("You don't have segments anymore");

	for (size_t i = 0; i < count; i++)
	{
		delete _segments.back();
		_segments.pop_back();
	}

	if (_segments.empty())
		throw DeathException("You don't have segments anymore");

	return (true);
}

void	Snake::rotateLeft()
{
	Direction tmp = _direction;
	switch (tmp)
	{
		case UP:
			_direction = LEFT;
			break;
		case DOWN:
			_direction = RIGHT;
			break;
		case LEFT:
			_direction = DOWN;
			break;
		case RIGHT:
			_direction = UP;
			break;
	}
}

void	Snake::rotateRight()
{
	Direction tmp = _direction;
	switch (tmp)
	{
		case UP:
			_direction = RIGHT;
			break;
		case DOWN:
			_direction = LEFT;
			break;
		case LEFT:
			_direction = UP;
			break;
		case RIGHT:
			_direction = DOWN;
			break;
	}
}

bool	Snake::move()
{
	Position movement = _segments.front()->getPosition();

	switch (_direction)
	{
		case UP:
			movement.decY();
			break;
		case DOWN:
			movement.incY();
			break;
		case LEFT:
			movement.decX();
			break;
		case RIGHT:
			movement.incX();
			break;
	}

	setPosition(movement);

	delete _segments.back();
	_segments.pop_back();
	_segments.push_front(new Snake::Segment(this, movement));

	return (true);
}

bool	Snake::move(const Position& newPos)
{
	this->setPosition(newPos);
	return (true);
}

bool	Snake::move(int x, int y, int z)
{
	this->setPosition(x, y, z);
	return (true);
}

bool	Snake::collide(const AEntity& o)
{
	if (_actions.find(o.getType()) != _actions.end())
		return ((this->*(_actions.find(o.getType())->second))(o));
	else
		throw CollisionException("Error: invalid entity type.");
	return (true);
}

size_t Snake::getSize() const
{
	return (_segments.size());
}

bool Snake::getIsAlive() const
{
	return (_isAlive);
}

std::list<Snake::Segment*> Snake::getSegments() const
{
	return (_segments);
}

Direction	Snake::getDirection(void) const
{
	return (_direction);
}

bool Snake::die(AEntity const & o)
{
	std::cout << "You got killed by a " << o.getTypeName() << "." << std::endl;
	(void)o;
	delete this;

	throw DeathException();

	return (true);
}

bool Snake::eat(AEntity const & block)
{
	Food const * food = static_cast<const Food*>(&block);

	if (food->getSegmentAmount() < 0)
	{
		this->removeSegment(static_cast<size_t>(abs(food->getSegmentAmount())));
	}
	else
	{
		for (int i = food->getSegmentAmount(); i > 0; i--)
		{
			this->addSegment(&block);
		}
	}
	return (true);
}


/*
 * CLASS Snake::Segment
 */

Snake::Segment::Segment(Snake* self, Position const & pos)
	: _self(self), _position(pos)
{
}

Snake::Segment::Segment(Snake* self, int x, int y, int z)
	: _self(self), _position(x, y, z)
{
}

Snake::Segment::~Segment()
{
}

void	Snake::Segment::move(Direction direction)
{
	if (direction != UP && direction != DOWN && direction != LEFT && direction != RIGHT)
		throw MovementException("Error: Trying to move to an invalid direction.");

	_prevPosition = _position;

	switch (direction)
	{
		case UP:
			_position.decY();
			break;
		case DOWN:
			_position.incY();
			break;
		case LEFT:
			_position.decX();
			break;
		case RIGHT:
			_position.incX();
			break;
		default:
			throw MovementException("Error: Trying to move to an invalid direction.");
			break;
	}
}

Position const & Snake::Segment::getPosition(void) const
{
	return (_position);
}

Position const & Snake::Segment::getPrevPosition(void) const
{
	return (_prevPosition);
}

bool Snake::Segment::move()
{
	return (false);
}

bool Snake::Segment::move(const Position& position)
{
	(void)position;
	return (false);
}

bool Snake::Segment::move(int x, int y, int z)
{
	(void)x;
	(void)y;
	(void)z;
	return (false);
}

bool Snake::Segment::collide(const AEntity& o)
{
	return (_self->die(o));
}

Position const & Snake::Segment::getSprite()
{
	int spriteX = 0;
	int spriteY = 0;

	if (_self->getSegments().front() == this)
	{ // Le segment actuel est la tête
		switch (_self->getDirection())
		{
			case LEFT:
				spriteX = Config::get().getValue<int>("entities.player_head.spriteX_left");
				spriteY = Config::get().getValue<int>("entities.player_head.spriteY_left");
				break;

			case RIGHT:
				spriteX = Config::get().getValue<int>("entities.player_head.spriteX_right");
				spriteY = Config::get().getValue<int>("entities.player_head.spriteY_right");
				break;

			case UP:
				spriteX = Config::get().getValue<int>("entities.player_head.spriteX_up");
				spriteY = Config::get().getValue<int>("entities.player_head.spriteY_up");
				break;

			case DOWN:
				spriteX = Config::get().getValue<int>("entities.player_head.spriteX_down");
				spriteY = Config::get().getValue<int>("entities.player_head.spriteY_down");
				break;
		}
	}
	else
	{ // Le segment actuel fait partie du corps
		spriteX = Config::get().getValue<int>("entities.player.spriteX");
		spriteY = Config::get().getValue<int>("entities.player.spriteY");
	}

	_sprite.setX(spriteX);
	_sprite.setY(spriteY);
	return (_sprite);
}

int Snake::Segment::getColor() const
{
	int color;

	if (_self->getSegments().front() == this)
	{ // Le segment actuel est la tête
		color = strtol(Config::get().getValue<std::string>("entities.player_head.color").c_str(), NULL, 0);
	}
	else
	{ // Le segment actuel fait partie du corps
		color = strtol(Config::get().getValue<std::string>("entities.player.color").c_str(), NULL, 0);
	}

	return (color);
}
