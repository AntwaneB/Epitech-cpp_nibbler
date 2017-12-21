/*
 * File:   Position.cpp
 * Author: buchse_a
 *
 * Created on March 9, 2015, 11:31 AM
 */

#include "Exception.hpp"
#include "Position.hpp"

Position::Position(int x, int y, int z)
	: _x(x), _y(y), _z(z), _isSet(true)
{
}

Position::Position()
	: _x(0), _y(0), _z(0), _isSet(false)
{
}

Position::Position(const Position& orig)
	: _x(orig._x), _y(orig._y), _z(orig._z), _isSet(orig._isSet)
{
}

Position&	Position::operator=(const Position& orig)
{
	if (this != &orig)
	{
		_x = orig._x;
		_y = orig._y;
		_z = orig._z;
		_isSet = orig._isSet;
	}
	return (*this);
}


Position::~Position()
{
}

void Position::setZ(int z)
{
	this->_z = z;
	this->_isSet = true;
}

void Position::incZ(int inc)
{
	if (!_isSet)
		throw PositionException("Increasing unset position.");
	this->_z += inc;
}

void Position::decZ(int dec)
{
	if (!_isSet)
		throw PositionException("Decreasing unset position.");
	this->_z -= dec;
}

int Position::getZ() const
{
	if (!_isSet)
		throw PositionException("Getting unset position.");
	return _z;
}

void Position::setY(int y)
{
	this->_y = y;
	this->_isSet = true;
}

void Position::incY(int inc)
{
	if (!_isSet)
		throw PositionException("Increasing unset position.");
	this->_y += inc;
}

void Position::decY(int dec)
{
	if (!_isSet)
		throw PositionException("Decreasing unset position.");
	this->_y -= dec;
}

int Position::getY() const
{
	if (!_isSet)
		throw PositionException("Getting unset position.");
	return _y;
}

void Position::setX(int x)
{
	this->_x = x;
	this->_isSet = true;
}

void Position::incX(int inc)
{
	if (!_isSet)
		throw PositionException("Increasing unset position.");
	this->_x += inc;
}

void Position::decX(int dec)
{
	if (!_isSet)
		throw PositionException("Decreasing unset position.");
	this->_x -= dec;
}

int Position::getX() const
{
	if (!_isSet)
		throw PositionException("Getting unset position.");
	return _x;
}

bool	Position::isSet() const
{
	return (_isSet);
}

bool	Position::operator==(Position const & o) const
{
	return (o._x == _x && o._y == _y && o._z == _z);
}
