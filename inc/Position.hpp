/*
 * File:   Position.hpp
 * Author: buchse_a
 *
 * Created on March 9, 2015, 11:31 AM
 */

#ifndef POSITION_HPP
#define	POSITION_HPP

enum Direction { UP, DOWN, LEFT, RIGHT };

class Position
{
public:
	Position();
	Position(int x, int y, int z = 0);
	Position(const Position& orig);
	Position& operator=(const Position& orig);
	virtual ~Position();

	bool	operator==(Position const & o) const;

   void	setZ(int z);
   void	incZ(int inc = 1);
   void	decZ(int dec = 1);
   int	getZ() const;
   void	setY(int y);
   void	incY(int inc = 1);
   void	decY(int dec = 1);
   int	getY() const;
   void	setX(int x);
   void	incX(int inc = 1);
   void	decX(int dec = 1);
   int	getX() const;
	bool	isSet() const;

private:
	int	_x;
	int	_y;
	int	_z;
	bool	_isSet;
};

#endif	/* POSITION_HPP */

