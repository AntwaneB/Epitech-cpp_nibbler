/*
 * File:   Level.hpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 3:51 PM
 */

#ifndef LEVEL_HPP
#define	LEVEL_HPP

#include <vector>
#include <list>
#include <string>
#include "Block.hpp"
#include "AEntity.hpp"
#include "Snake.hpp"

class Level
{
public:
	explicit Level() {};
	Level(std::string const & levelFile);
	Level(int width, int height);
	virtual ~Level();

	std::vector<std::vector<Block*> > const &	getMap() const;
	std::list<AEntity*> const &					getEntities() const;
	std::vector<std::vector<Block*> >&	map();
	std::list<AEntity*>&					entities();

	int	getWidth(void) const;
	int	getHeight(void) const;
	std::string const & getTilesetPath(void) const;

	void	generateFood(void);
	void	incScore(int inc = 1);
	long	getScore(void) const;

	void	invertControls(bool);
	bool	controlsInverted(void) const;

	void		modifySpeed(double speedModifier);
	double	getSpeedModifier(void) const;

private:
	bool		collideWithSnake(Position const & spot, Snake* other) const;

private:
	std::string									_levelFile;
	int											_width;
	int											_height;

	std::list<AEntity*>						_entities;
	std::vector<std::vector<Block*> >	_map;

	std::string									_tilesetPath;
	long											_score;

	bool											_controlsInverted;
	double										_speedModifier;
};

#endif	/* LEVEL_HPP */
