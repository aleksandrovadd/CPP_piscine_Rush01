#include "MonitorRam.hpp"

MonitorRam::MonitorRam() : AMonitorModule::AMonitorModule("RAM Module")
{
	totalRAM = getTotalRAM();
	updateData();
}

MonitorRam::MonitorRam(MonitorRam const &objToCopy)
{
	*this = objToCopy;
}

MonitorRam::~MonitorRam()
{
}

MonitorRam &MonitorRam::operator=(MonitorRam const &obj)
{
	if (this != &obj)
	{
		totalRAM = obj.totalRAM;
		freeRAM = obj.freeRAM;
		usedRAM = obj.usedRAM;
		wiredRAM = obj.wiredRAM;
	}
	return (*this);
}

static std::string setPrec(const float x, const int decDigits)
{
	std::stringstream ss;

	ss << std::fixed;
	ss.precision(decDigits);
	ss << x;
	return (ss.str());
}

void MonitorRam::updateData(void)
{
	mach_port_t				mach_port;
	mach_msg_type_number_t	count;
	vm_size_t				page_size;
	vm_statistics64_data_t	vm_stats = {};

	mach_port = mach_host_self();
	count = sizeof(vm_stats) / sizeof(natural_t);
	if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
		KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO, reinterpret_cast<host_info64_t>(&vm_stats), &count))
	{
		usedRAM = (static_cast<int64_t>(vm_stats.active_count) + static_cast<int64_t>(vm_stats.inactive_count)) * static_cast<int64_t>(page_size);
		wiredRAM = static_cast<int64_t>(vm_stats.wire_count) * static_cast<int64_t>(page_size);
		freeRAM = totalRAM - usedRAM;
	}
	result["Total Memory: "] = setPrec(static_cast<float>(totalRAM) / (1024 * 1024), 2) + "Mb";
	result["Free Memory: "] = setPrec(static_cast<float>(freeRAM) / (1024 * 1024), 2) + "Mb";
	result["Used Memory: "] = setPrec(static_cast<float>(usedRAM) / (1024 * 1024), 2) + "Mb";
	result["Wired Memory: "] = setPrec(static_cast<float>(wiredRAM) / (1024 * 1024), 2) + "Mb";
	result["Swap Memory: "] =  getSwapRAM();

	result["Used Memory (percentage): "] = setPrec(static_cast<float>(usedRAM) / totalRAM * 100, 2) + "%";
	result["Free Memory (percentage): "] = setPrec(static_cast<float>(freeRAM) / totalRAM * 100, 2) + "%";
}

std::string MonitorRam::getSwapRAM(void)
{
	std::string str = AMonitorModule::exec("sysctl -n vm.swapusage");
	str.erase(str.length() - 1);
	return (str);
}

int64_t MonitorRam::getTotalRAM(void)
{
	int		mib[2];
	size_t	length;
	int64_t	physical_memory;

	mib[0] = CTL_HW;
	mib[1] = HW_MEMSIZE;
	length = sizeof(int64_t);
	sysctl(mib, 2, &physical_memory, &length, NULL, 0);
	return (physical_memory);
}
