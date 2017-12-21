/*
 * File:   TypeException.hpp
 * Author: buchse_a
 *
 * Created on February 9, 2015, 1:12 PM
 */

#ifndef EXCEPTION_HPP
#define	EXCEPTION_HPP

#include <string>
#include <exception>

class Exception : public std::exception
{
public:
	Exception(std::string const & s)
		: _message(s)
	{

	}

	virtual ~Exception() throw() {}

	virtual const char*	what() const throw()
	{
		return (_message.c_str());
	}

protected:
	std::string	_message;
};

class InitException : public Exception
{
public:
	InitException(std::string const & s) : Exception(s) {}

	virtual ~InitException() throw() {}
};

class ExitException : public Exception
{
public:
	ExitException(std::string const & s) : Exception(s) {}

	virtual ~ExitException() throw() {}
};

class CollisionException : public Exception
{
public:
	CollisionException(std::string const & s) : Exception(s) {}

	virtual ~CollisionException() throw() {}
};

class MovementException : public Exception
{
public:
	MovementException(std::string const & s) : Exception(s) {}

	virtual ~MovementException() throw() {}
};

class PositionException : public Exception
{
public:
	PositionException(std::string const & s) : Exception(s) {}

	virtual ~PositionException() throw() {}
};

class DeathException : public Exception
{
public:
	DeathException(std::string const & s = "") : Exception(s) {}

	virtual ~DeathException() throw() {}
};

class ParserException : public Exception
{
public:
	ParserException(std::string const & s) : Exception(s) {}

	virtual ~ParserException() throw() {}
};

class GraphicsException : public Exception
{
public:
	GraphicsException(std::string const & s = "") : Exception(s) {}

	virtual ~GraphicsException() throw() {}
};

class NoDeleteException : public Exception
{
public:
	NoDeleteException(std::string const & s = "") : Exception(s) {}

	virtual ~NoDeleteException() throw() {}
};

#endif	/* EXCEPTION_HPP */
