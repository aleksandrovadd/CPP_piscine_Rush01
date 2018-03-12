#include "MonitorOsInfo.hpp"

MonitorOsInfo::MonitorOsInfo() : AMonitorModule::AMonitorModule("OS Info Module")
{

}

MonitorOsInfo::MonitorOsInfo(MonitorOsInfo const &objToCopy)
{
	*this = objToCopy;
}

MonitorOsInfo::~MonitorOsInfo()
{
}

MonitorOsInfo &MonitorOsInfo::operator=(MonitorOsInfo const &obj)
{
	(void)obj;
	return (*this);
}

void MonitorOsInfo::updateData(void)
{
	std::string tmp = AMonitorModule::exec("sw_vers | grep ProductName:");
	std::string str;
	std::size_t pos = 0;

	pos = tmp.find_first_of(": ", pos + 2);
	tmp = tmp.substr(pos + 2, tmp.length());
	result["ProductName: "] = tmp.erase(tmp.length() - 1);
	pos = 0;
	tmp = AMonitorModule::exec("sw_vers | grep ProductVersion:");
	pos = tmp.find_first_of(": ", pos + 2);
	tmp = tmp.substr(pos + 2, tmp.length());
	result["ProductVersion: "] = tmp.erase(tmp.length() - 1);
	pos = 0;
	tmp = AMonitorModule::exec("sw_vers | grep BuildVersion:");
	pos = tmp.find_first_of(": ", pos + 2);
	tmp = tmp.substr(pos + 2, tmp.length());
	result["ProductVersionBuild: "] = tmp.erase(tmp.length() - 1);
	pos = 0;
	tmp = AMonitorModule::exec("system_profiler SPSoftwareDataType | grep \"Kernel Version:\"");
	pos = tmp.find_first_of(":", pos + 1);
	tmp = tmp.substr(pos + 2, tmp.length());
	result["Kernel Version: "] = tmp.erase(tmp.length() - 1);
}
