/*
 * File:   Food.cpp
 * Author: buchse_a
 *
 * Created on March 29, 2015, 12:15 PM
 */

#include <sstream>
#include "Config.hpp"
#include "Food.hpp"

Food::Food(Position const & position)
{
	setPosition(position);
	setSpeed(0);

	int	count = Config::get().getValue<int>("tileset.food_count");
	count = count < 1 ? 1 : count;
	int	version = rand() % count;
	std::stringstream	ss;
	ss << "food_";
	ss << version;

	_exists = true;
	_type = AEntity::FOOD;
	_typeName = ss.str();
	_color = strtol(Config::get().getValue<std::string>(std::string("entities.") + _typeName + ".color").c_str(), NULL, 0);
	_scoreAmount = Config::get().getValue<int>(std::string("entities.") + _typeName + ".scoreAmount");
	_segmentAmount = Config::get().getValue<int>(std::string("entities.") + _typeName + ".segmentAmount");
	_invertControls = Config::get().getValue<bool>(std::string("entities.") + _typeName + ".invertControls");
	_speedModifier = Config::get().getValue<double>(std::string("entities.") + _typeName + ".speedModifier");
	_speedModifier = _speedModifier == 0 ? 1 : _speedModifier;

	int spriteX = Config::get().getValue<int>(std::string("entities.") + _typeName + ".spriteX");
	int spriteY = Config::get().getValue<int>(std::string("entities.") + _typeName + ".spriteY");
	setSprite(spriteX, spriteY);
}

Food::Food(int x, int y, int z)
{
	setPosition(x, y, z);
	setSpeed(0);

	int	count = Config::get().getValue<int>("tileset.food_count");
	count = count < 1 ? 1 : count;
	int	version = rand() % count;
	std::stringstream	ss;
	ss << "food_";
	ss << version;

	_exists = true;
	_type = AEntity::FOOD;
	_typeName = ss.str();
	_color = strtol(Config::get().getValue<std::string>(std::string("entities.") + _typeName + ".color").c_str(), NULL, 0);
	_scoreAmount = Config::get().getValue<int>(std::string("entities.") + _typeName + ".scoreAmount");
	_segmentAmount = Config::get().getValue<int>(std::string("entities.") + _typeName + ".segmentAmount");
	_invertControls = Config::get().getValue<bool>(std::string("entities.") + _typeName + ".invertControls");
	_speedModifier = Config::get().getValue<double>(std::string("entities.") + _typeName + ".speedModifier");
	_speedModifier = _speedModifier == 0 ? 1 : _speedModifier;

	int spriteX = Config::get().getValue<int>(std::string("entities.") + _typeName + ".spriteX");
	int spriteY = Config::get().getValue<int>(std::string("entities.") + _typeName + ".spriteY");
	setSprite(spriteX, spriteY);
}

Food::~Food()
{
}

bool Food::move()
{
	return (false);
}

bool Food::move(const Position& newPos)
{
	this->setPosition(newPos);
	return (true);
}

bool Food::move(int x, int y, int z)
{
	this->setPosition(x, y, z);
	return (true);
}

bool Food::collide(AEntity const & o)
{
	_exists = false;
	(void)o;
	return (true);
}

int Food::getScoreAmount() const
{
	return (_scoreAmount);
}

int Food::getSegmentAmount() const
{
	return (_segmentAmount);
}

bool Food::invertControls() const
{
	return (_invertControls);
}

double Food::getSpeedModifier() const
{
	return (_speedModifier);
}

bool	Food::isMalus() const
{
	return (_invertControls || _segmentAmount < 0);
}