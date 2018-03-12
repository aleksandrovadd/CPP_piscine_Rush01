#include "MonitorDateTime.hpp"

MonitorDateTime::MonitorDateTime() : AMonitorModule::AMonitorModule("DateTime Module")
{
}

MonitorDateTime::MonitorDateTime(MonitorDateTime const & objToCopy)
{
	*this = objToCopy;
}

MonitorDateTime::~MonitorDateTime()
{
}

MonitorDateTime &MonitorDateTime::operator=(MonitorDateTime const &obj)
{
	(void)obj;
	return (*this);
}

void MonitorDateTime::updateData(void)
{
	std::stringstream ss;
	std::time_t time_now = std::time(nullptr);

	ss << std::put_time(std::localtime(&time_now), "%Y.%m.%d");
	this->result["Date: "] = ss.str();
	ss.str("");
	ss << std::put_time(std::localtime(&time_now), "%H:%M:%S");
	this->result["Time: "] = ss.str();
}
