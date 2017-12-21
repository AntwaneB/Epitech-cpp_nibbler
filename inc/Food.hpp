/*
 * File:   Food.hpp
 * Author: buchse_a
 *
 * Created on March 29, 2015, 12:15 PM
 */

#ifndef FOOD_HPP
#define	FOOD_HPP

#include "AEntity.hpp"

class Food : public AEntity
{
public:
	Food(Position const &);
	Food(int x, int y, int z = 0);
	virtual ~Food();

	virtual bool	move();
	virtual bool	move(Position const &);
	virtual bool	move(int x, int y, int z = 0);
	virtual bool	collide(AEntity const &);

	int	getScoreAmount(void) const;
	int	getSegmentAmount(void) const;
	bool	invertControls(void) const;
	double	getSpeedModifier(void) const;
	bool	isMalus(void) const;

private:
	int		_scoreAmount;
	int		_segmentAmount;
	bool		_invertControls;
	double	_speedModifier;
};

#endif	/* FOOD_HPP */
