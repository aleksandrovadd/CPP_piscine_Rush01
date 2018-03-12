
#include "MonitorHostUser.hpp"

MonitorHostUser::MonitorHostUser() : AMonitorModule::AMonitorModule("User/Hostname Module")
{
	updateData();
}

MonitorHostUser::MonitorHostUser(MonitorHostUser const &objToCopy)
{
	*this = objToCopy;
}

MonitorHostUser::~MonitorHostUser()
{
}

MonitorHostUser &MonitorHostUser::operator=(MonitorHostUser const &obj)
{
	(void)obj;
	return (*this);
}

void MonitorHostUser::updateData(void)
{
	char buf[256];
	std::string str;

	gethostname(buf, 256);
	str = buf;
	result["Hostname: "] = str;
	getlogin_r(buf, 256);
	str = buf;
	result["Username: "] = str;
}
