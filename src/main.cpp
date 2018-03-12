#include <iostream>

#include "display_modules/DisplayGtk.hpp"
#include "display_modules/DisplayNcurses.hpp"
#include "monitor_modules/MonitorDateTime.hpp"
#include "monitor_modules/MonitorCpu.hpp"
#include "monitor_modules/MonitorNetwork.hpp"
#include "monitor_modules/MonitorDisk.hpp"
#include "monitor_modules/MonitorHostUser.hpp"
#include "monitor_modules/MonitorRam.hpp"
#include "monitor_modules/MonitorOsInfo.hpp"

int main(int ac, char **av)
{
	std::string flag;
	IMonitorDisplay *monitor = nullptr;

	if (ac == 2)
	{
		flag = av[1];
		if (flag == "-nc")
		{
			monitor = new DisplayNcurses();
			monitor->addNewMonitor(new MonitorHostUser());
			monitor->addNewMonitor(new MonitorOsInfo());
			monitor->addNewMonitor(new MonitorDateTime());
			monitor->addNewMonitor(new MonitorCpu());
			monitor->addNewMonitor(new MonitorRam());
			monitor->addNewMonitor(new MonitorDisk());
			monitor->addNewMonitor(new MonitorNetwork());
			monitor->start();
		}
	}
	else if (ac == 1)
	{
		monitor = new DisplayGtk();
		monitor->addNewMonitor(new MonitorHostUser());
		monitor->addNewMonitor(new MonitorOsInfo());
		monitor->addNewMonitor(new MonitorDateTime());
		monitor->addNewMonitor(new MonitorCpu());
		monitor->addNewMonitor(new MonitorRam());
		monitor->addNewMonitor(new MonitorDisk());
		monitor->addNewMonitor(new MonitorNetwork());
		monitor->start();
	}
	else
		std::cout << "Usage: No flags will start gtk mode. Use \"-nc\" to start Ncurses mode." << std::endl;
	return (0);
}