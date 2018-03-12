#include "AMonitorDisplay.hpp"

AMonitorDisplay::AMonitorDisplay()
{
}

AMonitorDisplay::AMonitorDisplay(AMonitorDisplay const & objToCopy)
{
	*this = objToCopy;
}

AMonitorDisplay::~AMonitorDisplay()
{
	modules.clear();
}

AMonitorDisplay & AMonitorDisplay::operator=(AMonitorDisplay const & obj)
{
	modules = obj.modules;
	return (*this);
}

void AMonitorDisplay::addNewMonitor(AMonitorModule *module)
{
	if (modules.find(module->getModuleName()) == modules.end()) {
		modules[module->getModuleName()] = module;
	}
}

void AMonitorDisplay::deleteMonitor(std::string const & moduleName)
{
	std::map<std::string, AMonitorModule *>::iterator it = modules.find(moduleName);
	if (it != modules.end()) {
		modules.erase(it);
	}
}
