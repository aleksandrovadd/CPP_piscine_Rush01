#ifndef MONITORDATETIME_HPP
# define MONITORDATETIME_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>

#include "AMonitorModule.hpp"

class MonitorDateTime : public AMonitorModule
{
public:
	MonitorDateTime();
	MonitorDateTime(MonitorDateTime const & objToCopy);
	~MonitorDateTime();

	MonitorDateTime &operator = (MonitorDateTime const &obj);

	void updateData(void);
};

#endif