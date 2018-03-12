#ifndef MONITORDISPLAY_HPP
# define MONITORDISPLAY_HPP

#include <iostream>
#include <map>

#include "AMonitorDisplay.hpp"
#include "IMonitorDisplay.hpp"

class AMonitorDisplay : public IMonitorDisplay
{
public:
	AMonitorDisplay();
	AMonitorDisplay(AMonitorDisplay const &objToCopy);

	virtual ~AMonitorDisplay();

	AMonitorDisplay &operator = (AMonitorDisplay const &obj);

	void addNewMonitor(AMonitorModule *module);
	void deleteMonitor(std::string const &moduleName);

	virtual void displayData(void) = 0;
	virtual void updateData(void) = 0;
	virtual int start() = 0;
	
protected:
	std::map<std::string, AMonitorModule *> modules;
};

#endif