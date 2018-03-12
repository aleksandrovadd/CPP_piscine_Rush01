#ifndef IMONITORDISPLAY_HPP
# define IMONITORDISPLAY_HPP

#include <iostream>

#include "../monitor_modules/AMonitorModule.hpp"

class IMonitorDisplay
{
public:
	virtual void addNewMonitor(AMonitorModule *module) = 0;
	virtual void deleteMonitor(std::string const &module) = 0;
	virtual void displayData(void) = 0;
	virtual void updateData(void) = 0;
	virtual int	start() = 0;
};

#endif
