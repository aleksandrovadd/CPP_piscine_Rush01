#include "MonitorDisk.hpp"

MonitorDisk::MonitorDisk() : AMonitorModule::AMonitorModule("Disk Module")
{
}

MonitorDisk::MonitorDisk(MonitorDisk const & objToCopy)
{
	*this = objToCopy;
}

MonitorDisk::~MonitorDisk()
{
}

MonitorDisk & MonitorDisk::operator=(MonitorDisk const & obj)
{
	(void)obj;
	return (*this);
}

void MonitorDisk::updateData(void)
{
	std::stringstream 	ss(AMonitorModule::exec("top -l 1 | grep -E \"^Disks\""));
	std::string			diskTmp;

	ss >> diskTmp;
	ss >> diskTmp;
	result["Disk stats:"] = "";
	result["Read: "] = diskTmp;
	ss >> diskTmp;
	ss >> diskTmp;
	result["Write: "] = diskTmp;
}
