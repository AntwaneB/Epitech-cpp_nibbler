/*
 * File:   AEntity.hpp
 * Author: buchse_a
 *
 * Created on March 9, 2015, 11:31 AM
 */

#ifndef AENTITY_HPP
#define	AENTITY_HPP

#include <string>
#include "Position.hpp"

class AEntity
{
public:
	enum EntityType { BLOCK, SNAKE, SNAKESEGMENT, FOOD };

public:
	virtual ~AEntity() = 0;

	void	setPosition(Position const &);
	void	setPosition(int x, int y, int z = 0);
	void	setIsSolid(bool);
	void	setType(EntityType);
	void	setSpeed(int);
	void	setTypeName(std::string const &);
	void	setColor(int);
	void	setSprite(Position const &);
	void	setSprite(int x, int y);
	void	setExists(bool);

	Position const &	getPosition(void) const;
	bool					getIsSolid(void) const;
	EntityType			getType(void) const;
	int					getSpeed(void) const;
	std::string			getTypeName(void) const;
	bool	getExists(void) const;
	virtual int						getColor(void) const;
	virtual Position const &	getSprite(void) const;

	virtual bool	move() = 0;
	virtual bool	move(Position const &) = 0;
	virtual bool	move(int x, int y, int z = 0) = 0;
	virtual bool	collide(AEntity const &) = 0;

protected:
	Position		_position;
	bool			_isSolid;
	EntityType	_type;
	std::string	_typeName;
	int			_speed;
	int			_color;
	Position		_sprite;
	bool			_exists;
};

#endif	/* AENTITY_HPP */

