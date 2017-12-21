/*
 * File:   Block.hpp
 * Author: buchse_a
 *
 * Created on March 21, 2015, 2:18 PM
 */

#ifndef BLOCK_HPP
#define	BLOCK_HPP

#include <map>
#include "AEntity.hpp"

class Block : public AEntity
{
public:
	Block(std::string const &, bool isSolid, Position const &);
	Block(std::string const &, bool isSolid, int x, int y, int z = 0);
	virtual ~Block();

	virtual bool	move();
	virtual bool	move(Position const &);
	virtual bool	move(int x, int y, int z = 0);
	virtual bool	collide(AEntity const &);

	bool	isVisible(void) const;

private:
	std::map<AEntity::EntityType, bool (Block::*)(AEntity const &)>	_actions;
	bool	_isVisible;
};

#endif	/* BLOCK_HPP */
