#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

#include <iostream>

class IMonitorModule
{
public:
	virtual std::map<std::string, std::string> const &getData(void) const = 0;
	virtual void updateData(void) = 0;
	virtual const std::string &getModuleName() const = 0;
};

#endif
