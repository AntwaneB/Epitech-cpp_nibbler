/*
 * File:   Snake.hpp
 * Author: buchse_a
 *
 * Created on March 21, 2015, 2:07 PM
 */

#ifndef SNAKE_HPP
#define	SNAKE_HPP

#include <list>
#include <vector>
#include <map>
#include "AEntity.hpp"
#include "Block.hpp"

class Snake : public AEntity
{
public:
	class Segment : public AEntity
	{
	public:
		Segment(Snake*, Position const &);
		Segment(Snake*, int x, int y, int z = 0);
		~Segment();

		void				move(Direction);
		virtual bool	collide(AEntity const &);

		virtual bool	move();
		virtual bool	move(Position const &);
		virtual bool	move(int x, int y, int z = 0);

		Position const &	getPosition(void) const;
		Position const &	getPrevPosition(void) const;
		virtual Position const &	getSprite(void);
		virtual int	getColor(void) const;

	private:
		Snake*	_self;
		Position	_position;
		Position	_prevPosition;
		Position _sprite;
	};

public:
	Snake();
	virtual ~Snake();

	virtual bool	move();
	virtual bool	move(Position const &);
	virtual bool	move(int x, int y, int z = 0);
	virtual bool	collide(AEntity const &);

	void	rotateLeft(void);
	void	rotateRight(void);

	size_t	getSize() const;
	bool		getIsAlive() const;
	std::list<Snake::Segment*>		getSegments() const;
	Direction	getDirection(void) const;

private:
	bool	eat(AEntity const &);
	bool	addSegment(AEntity const *);
	bool	removeSegment(size_t);
	bool	die(AEntity const &);

private:
	std::list<Snake::Segment*>		_segments;
	bool									_isAlive;
	std::map<AEntity::EntityType, bool (Snake::*)(AEntity const &)>	_actions;
	Direction							_direction;
};

#endif	/* SNAKE_HPP */
