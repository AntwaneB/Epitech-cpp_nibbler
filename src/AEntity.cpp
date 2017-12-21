/*
 * File:   AEntity.cpp
 * Author: buchse_a
 *
 * Created on March 9, 2015, 11:31 AM
 */

#include "AEntity.hpp"

AEntity::~AEntity()
{
}

void AEntity::setPosition(const Position& position)
{
	_position = position;
}

void AEntity::setPosition(int x, int y, int z)
{
	_position = Position(x, y, z);
}

void	AEntity::setTypeName(std::string const & type)
{
	_typeName = type;
}

void AEntity::setIsSolid(bool isSolid)
{
	_isSolid = isSolid;
}

void AEntity::setType(AEntity::EntityType type)
{
	_type = type;
}

void AEntity::setColor(int color)
{
	_color = color;
}

void AEntity::setSprite(int x, int y)
{
	_sprite = Position(x, y);
}

void AEntity::setSprite(Position const & pos)
{
	_sprite = pos;
}

void AEntity::setExists(bool exists)
{
	_exists = exists;
}

Position const & AEntity::getPosition() const
{
	return (_position);
}

bool AEntity::getIsSolid() const
{
	return (_isSolid);
}

AEntity::EntityType AEntity::getType() const
{
	return (_type);
}

void	AEntity::setSpeed(int speed)
{
	_speed = speed;
}

int	AEntity::getSpeed() const
{
	return (_speed);
}

std::string	AEntity::getTypeName() const
{
	return (_typeName);
}

int	AEntity::getColor(void) const
{
	return (_color);
}

Position const &	AEntity::getSprite(void) const
{
	return (_sprite);
}

bool	AEntity::getExists(void) const
{
	return (_exists);
}
