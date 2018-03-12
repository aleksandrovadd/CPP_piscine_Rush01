#ifndef MONITORDISK_HPP
# define MONITORDISK_HPP

#include <iostream>
#include <sstream>

#include "AMonitorModule.hpp"

class MonitorDisk : public AMonitorModule
{
public:
	MonitorDisk();
	MonitorDisk(MonitorDisk const &objToCopy);
	~MonitorDisk();

	MonitorDisk &operator = (MonitorDisk const &obj);

	void updateData(void);
};

#endif