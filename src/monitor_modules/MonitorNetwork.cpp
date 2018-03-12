#include "MonitorNetwork.hpp"

MonitorNetwork::MonitorNetwork() : AMonitorModule::AMonitorModule("Network Module")
{
}

MonitorNetwork::MonitorNetwork(MonitorNetwork const &objToCopy)
{
	*this = objToCopy;
}

MonitorNetwork::~MonitorNetwork()
{
}

MonitorNetwork &MonitorNetwork::operator=(MonitorNetwork const &obj)
{
	(void)obj;
	return (*this);
}

void MonitorNetwork::updateData(void)
{
	std::stringstream 	ss(AMonitorModule::exec("top -l 1 | grep -E \"^Networks\""));
	std::string			networkTmp;

	ss >> networkTmp;
	ss >> networkTmp;
	result["Network: packets: "] = "";
	ss >> networkTmp;
	result["in: "] = networkTmp;
	ss >> networkTmp;
	ss >> networkTmp;
	result["out: "] = networkTmp;
}
