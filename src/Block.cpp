/*
 * File:   Block.cpp
 * Author: buchse_a
 *
 * Created on March 21, 2015, 2:18 PM
 */

#include "Config.hpp"
#include "Block.hpp"

Block::Block(std::string const & type, bool isSolid, Position const & position)
{
	setPosition(position);
	setIsSolid(isSolid);
	setSpeed(0);

	_exists = true;
	_type = AEntity::BLOCK;
	_typeName = type;
	_isVisible = Config::get().getValue<bool>(std::string("entities.") + _typeName + ".visible");
	_color = strtol(Config::get().getValue<std::string>(std::string("entities.") + _typeName + ".color").c_str(), NULL, 0);

	int spriteX = Config::get().getValue<int>(std::string("entities.") + _typeName + ".spriteX");
	int spriteY = Config::get().getValue<int>(std::string("entities.") + _typeName + ".spriteY");
	setSprite(spriteX, spriteY);
}

Block::Block(std::string const & type, bool isSolid, int x, int y, int z)
{
	setPosition(x, y, z);
	setIsSolid(isSolid);

	_exists = true;
	_type = AEntity::BLOCK;
	_typeName = type;
	_isVisible = Config::get().getValue<bool>(std::string("entities.") + _typeName + ".visible");
	_color = strtol(Config::get().getValue<std::string>(std::string("entities.") + _typeName + ".color").c_str(), NULL, 0);

	int spriteX = Config::get().getValue<int>(std::string("entities.") + _typeName + ".spriteX");
	int spriteY = Config::get().getValue<int>(std::string("entities.") + _typeName + ".spriteY");
	setSprite(spriteX, spriteY);
}

Block::~Block()
{
}

bool Block::move()
{
	return (false);
}

bool Block::move(const Position& newPos)
{
	this->setPosition(newPos);
	return (true);
}

bool Block::move(int x, int y, int z)
{
	this->setPosition(x, y, z);
	return (true);
}

bool Block::collide(AEntity const & o)
{
	(void)o;
	return (true);
}

bool	Block::isVisible() const
{
	return (_isVisible);
}
