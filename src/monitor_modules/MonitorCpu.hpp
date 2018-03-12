#ifndef CPUMONITOR_HPP
#define CPUMONITOR_HPP

#include <map>
#include <iostream>
#include <sys/sysctl.h>
#include <mach/host_info.h>
#include <mach/mach_host.h>
#include <sstream>

#include "AMonitorModule.hpp"

class MonitorCpu : public AMonitorModule
{
public:
	MonitorCpu();
	MonitorCpu(MonitorCpu const &objToCopy);
	~MonitorCpu();

	MonitorCpu &operator = (MonitorCpu const &obj);

	void updateData(void);
private:
	float getCurrentLoad(int state);
	float calcCpuLoad(unsigned long long idleTicks, unsigned long long totalTicks, int stateType);

	unsigned long long previousTotalTicks[3];
	unsigned long long previousStateTicks[3];
};


#endif
