#ifndef MONITORRAM_HPP
#define MONITORRAM_HPP

#include <sys/sysctl.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <sstream>

#include "AMonitorModule.hpp"

class MonitorRam : public AMonitorModule
{
public:
	MonitorRam();
	MonitorRam(MonitorRam const &objToCopy);
	~MonitorRam();

	MonitorRam &operator = (MonitorRam const &obj);

	void updateData(void);

private:
	std::string getSwapRAM(void);
	int64_t getTotalRAM(void);

	int64_t totalRAM;
	int64_t usedRAM;
	int64_t freeRAM;
	int64_t wiredRAM;
};


#endif
