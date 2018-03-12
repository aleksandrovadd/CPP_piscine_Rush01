#ifndef MONITORNETWORK_HPP
#define MONITORNETWORK_HPP

#include <iostream>
#include <map>
#include <sstream>

#include "AMonitorModule.hpp"

class MonitorNetwork : public AMonitorModule
{
public:
	MonitorNetwork();
	MonitorNetwork(MonitorNetwork const &objToCopy);
	~MonitorNetwork();

	MonitorNetwork &operator = (MonitorNetwork const &obj);

	void updateData(void);
};


#endif
