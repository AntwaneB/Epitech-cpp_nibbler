/*
 * File:   Config.cpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 2:49 PM
 */

#include "pugixml.hpp"
#include "Exception.hpp"
#include "Config.hpp"

void Config::parseConfig(const std::string filename)
{
	this->_filename = filename;

	pugi::xml_document configFile;

	pugi::xml_parse_result result = configFile.load_file(this->_filename.c_str());
	if (!result)
		throw ParserException("Invalid file.");

	/* Getting tileset infos */
	pugi::xml_node tileset = configFile.child("config").child("tileset");
	for (pugi::xml_node param = tileset.child("param"); param; param = param.next_sibling("param"))
	{
		this->_config["tileset." + std::string(param.attribute("name").value())] = param.text().get();
	}

	/* Getting blocks infos */
	pugi::xml_node available_entities = configFile.child("config").child("available_entities");
	for (pugi::xml_node entity = available_entities.child("entity"); entity; entity = entity.next_sibling("entity"))
	{
		for (pugi::xml_node param = entity.child("param"); param; param = param.next_sibling("param"))
		{
			this->_config["entities." + std::string(entity.attribute("type").value()) + "." + std::string(param.attribute("name").value())] = param.text().get();
		}
	}
}

Config::~Config(void)
{

}

void Config::putValue(const std::string key, const std::string value)
{
	if (_config.find(key) == _config.end())
	{
		_config[key] = value;
	}
}

template <typename _T>
_T Config::getValue(const std::string key) const
{
	_T	value;

	value = this->_config.find(key);
	if (value == this->_config.end())
		return (NULL);
	else
		return (value);
}

template<>
std::string Config::getValue<std::string>(const std::string key) const
{
	if (this->_config.find(key) == this->_config.end())
		return (std::string(""));
	else
		return (this->_config.find(key)->second);
}

template<>
int Config::getValue<int>(const std::string key) const
{
	if (this->_config.find(key) == this->_config.end())
		return (0);
	else
		return (atoi(this->_config.find(key)->second.c_str()));
}

template<>
double Config::getValue<double>(const std::string key) const
{
	if (this->_config.find(key) == this->_config.end())
		return (0);
	else
		return (atof(this->_config.find(key)->second.c_str()));
}

template<>
bool Config::getValue<bool>(const std::string key) const
{
	if (this->_config.find(key) == this->_config.end())
		return (false);
	else
		return (this->_config.find(key)->second != "false" && this->_config.find(key)->second != "0");
}
