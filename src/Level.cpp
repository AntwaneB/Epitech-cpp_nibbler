/*
 * File:   Level.cpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 3:51 PM
 */

#include "Exception.hpp"
#include "Level.hpp"
#include "Config.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "pugixml.hpp"

Level::Level(std::string const & levelFile)
	: _levelFile(levelFile), _score(0), _controlsInverted(false), _speedModifier(1)
{
	pugi::xml_document mapFile;

	pugi::xml_parse_result result = mapFile.load_file(_levelFile.c_str());
	if (!result)
		throw ParserException("Can't open map file.");

	/* Getting map size */
	_width = mapFile.child("map").attribute("width").as_int();
	_height = mapFile.child("map").attribute("height").as_int();
	if (_width <= 0 || _height <= 0)
		throw ParserException("Invalid map size.");
	Config::get().putValue("level.width", std::to_string(_width));
	Config::get().putValue("level.height", std::to_string(_height));

	/* Getting map cases */
	pugi::xml_node map = mapFile.child("map");
	int y = 0;
	for (pugi::xml_node row = map.child("row"); row; row = row.next_sibling("row"))
	{
		std::vector<Block*> line;
		int x = 0;
		for (pugi::xml_node block = row.child("case"); block; block = block.next_sibling("case"))
		{
			bool	isSolid = Config::get().getValue<bool>(std::string("entities.") + block.attribute("entity").value() + ".collision");
			line.push_back(new Block(block.attribute("entity").value(), isSolid, x, y));
			x++;
		}
		_map.push_back(line);
		y++;
	}

	/* Creating entities */
	_entities.push_back(new Snake());
	this->generateFood();

	/* Configuration */
	_tilesetPath = Config::get().getValue<std::string>("tileset.filename");
}

Level::Level(int width, int height)
	: _score(0), _controlsInverted(false), _speedModifier(1)
{
	_width = width;
	_height = height;
	if (_width <= 0 || _height <= 0)
		throw ParserException("Invalid map size.");
	Config::get().putValue("level.width", std::to_string(_width));
	Config::get().putValue("level.height", std::to_string(_height));

	for (int y = 0; y < _height; y++)
	{
		std::vector<Block*> line;

		for (int x = 0; x < _width; x++)
		{
			Block*	block;

			if (y == 0 || y == _height - 1 || x == 0 || x == _width - 1)
				block = new Block("wall", true, x, y);
			else
				block = new Block("floor", false, x, y);

			line.push_back(block);
		}
		_map.push_back(line);
	}

	/* Creating entities */
	_entities.push_back(new Snake());
	this->generateFood();

	/* Configuration */
	_tilesetPath = Config::get().getValue<std::string>("tileset.filename");
}

Level::~Level()
{
}

std::list<AEntity*> const & Level::getEntities() const
{
	return (_entities);
}

std::vector<std::vector<Block*> > const &	Level::getMap() const
{
	return (_map);
}

std::list<AEntity*>& Level::entities()
{
	return (_entities);
}

std::vector<std::vector<Block*> >&	Level::map()
{
	return (_map);
}

int	Level::getWidth() const
{
	return (_width);
}

int	Level::getHeight() const
{
	return (_height);
}

std::string const & Level::getTilesetPath(void) const
{
	return (_tilesetPath);
}

void	Level::generateFood(void)
{
	int x = -1;
	int y = -1;
	Position	spot;

	while (x == -1 || y == -1)
	{
		x = rand() % (_width - 2) + 1;
		y = rand() % (_height - 2) + 1;

		spot.setX(x);
		spot.setY(y);

		std::list<AEntity*>						entitiesTmp = _entities;
		for (std::list<AEntity*>::iterator	jt = entitiesTmp.begin(); jt != entitiesTmp.end(); ++jt)
		{
			AEntity*	entityTmp = *jt;

			if (entityTmp->getExists() && ((entityTmp->getType() == AEntity::SNAKE && collideWithSnake(spot, static_cast<Snake*>(entityTmp)))
				|| entityTmp->getPosition() == spot))
			{
				x = y = -1;
			}
		}

		if (x != -1 && y != -1 && _map[y][x]->getIsSolid())
			x = y = -1;
	}

	Food*	food = new Food(x, y);
	_entities.push_back(food);
	if (food->isMalus())
		generateFood();
}

bool	Level::collideWithSnake(Position const & spot, Snake* other) const
{
	std::list<Snake::Segment*>	segments = other->getSegments();
	bool	collide = false;

	std::list<Snake::Segment*>::iterator it = segments.begin();
	++it;
	for (it = it; it != segments.end() && !collide; ++it)
	{
		if ((*it)->getPosition() == spot)
			collide = true;
	}

	return (collide);
}

void	Level::incScore(int inc)
{
	_score += inc;
}

long	Level::getScore(void) const
{
	return (_score);
}

void	Level::invertControls(bool doit)
{
	if (doit)
		_controlsInverted = !_controlsInverted;
}

bool	Level::controlsInverted() const
{
	return (_controlsInverted);
}

void	Level::modifySpeed(double speedModifier)
{
	_speedModifier = speedModifier;
}

double	Level::getSpeedModifier(void) const
{
	return (_speedModifier);
}
