#ifndef MONITORHOSTUSER_HPP
#define MONITORHOSTUSER_HPP

#include <sstream>
#include <zconf.h>

#include "AMonitorModule.hpp"

class MonitorHostUser : public AMonitorModule
{
public:
	MonitorHostUser();
	MonitorHostUser(MonitorHostUser const &objToCopy);
	~MonitorHostUser();

	MonitorHostUser &operator = (MonitorHostUser const &obj);

	void updateData(void);
};

#endif
