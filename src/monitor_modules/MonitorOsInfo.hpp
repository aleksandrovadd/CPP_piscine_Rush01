#ifndef MONITOROSINFO_HPP
#define MONITOROSINFO_HPP

#include <sstream>
#include "AMonitorModule.hpp"

class MonitorOsInfo : public AMonitorModule
{
public:
	MonitorOsInfo();
	MonitorOsInfo(MonitorOsInfo const &objToCopy);
	~MonitorOsInfo();

	MonitorOsInfo &operator = (MonitorOsInfo const &obj);

	void updateData(void);
};

#endif
