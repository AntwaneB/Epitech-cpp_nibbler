/*
 * File:   Config.hpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 2:49 PM
 */

#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <map>

class Config
{
public:
	Config(void){};
	~Config(void);
	static Config &get()
	{
		static Config	instance;

		return (instance);
	}

	void parseConfig(std::string filename);

	template <typename _T>
	_T getValue(const std::string key) const;
	void putValue(const std::string key, const std::string value);

private:
	Config(const Config &config);

private:
	std::map<std::string, std::string>	_config;
	std::string									_filename;
};

#endif	/* CONFIG_HPP */
