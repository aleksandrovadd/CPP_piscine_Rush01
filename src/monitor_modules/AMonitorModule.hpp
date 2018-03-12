#ifndef MONITORMODULE_HPP
#define MONITORMODULE_HPP

#include <map>

#include "IMonitorModule.hpp"

class AMonitorModule : public IMonitorModule
{
public:
	AMonitorModule();
	AMonitorModule(std::string moduleName);
	AMonitorModule(AMonitorModule const &objToCopy);
	virtual ~AMonitorModule();

	AMonitorModule &operator = (AMonitorModule const &objToCopy);

	std::map<std::string, std::string> const &getData(void) const;
	virtual void updateData(void) = 0;

	const std::string &getModuleName() const;

protected:
	std::string exec(const char* cmd);

	std::map<std::string, std::string> result;
	std::string moduleName;
};

#endif
