#include "MonitorCpu.hpp"

MonitorCpu::MonitorCpu() : AMonitorModule::AMonitorModule("CPU Module")
{
	previousStateTicks[0] = 0;
	previousStateTicks[1] = 0;
	previousStateTicks[2] = 0;
	previousTotalTicks[0] = 0;
	previousTotalTicks[1] = 0;
	previousTotalTicks[2] = 0;
}

MonitorCpu::MonitorCpu(MonitorCpu const &objToCopy)
{
	*this = objToCopy;
}

MonitorCpu::~MonitorCpu()
{
}

MonitorCpu &MonitorCpu::operator=(MonitorCpu const &obj)
{
	if (this != &obj)
	{
		previousTotalTicks[0] = obj.previousTotalTicks[0];
		previousTotalTicks[1] = obj.previousTotalTicks[1];
		previousTotalTicks[2] = obj.previousTotalTicks[2];
		previousStateTicks[0] = obj.previousStateTicks[0];
		previousStateTicks[1] = obj.previousStateTicks[1];
		previousStateTicks[2] = obj.previousStateTicks[2];
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

void MonitorCpu::updateData(void)
{
	std::string	tmp;
	float cpuIdle = getCurrentLoad(CPU_STATE_IDLE);
	float cpuUser = getCurrentLoad(CPU_STATE_USER);
	float cpuSystem = getCurrentLoad(CPU_STATE_SYSTEM);

	tmp = AMonitorModule::exec("sysctl -n machdep.cpu.brand_string");
	result["Model: "] = tmp.erase(tmp.length() - 1);
	tmp = AMonitorModule::exec("sysctl -n machdep.cpu.core_count");
	result["Cores number: "] = tmp.erase(tmp.length() - 1);
	tmp = AMonitorModule::exec("sysctl -n machdep.cpu.thread_count");
	result["Threads: "] = tmp.erase(tmp.length() - 1);
	tmp = AMonitorModule::exec("sysctl -n machdep.cpu.cache.size");
	result["Cache size: "] = tmp.erase(tmp.length() - 1);
	result["CPU Idle: "] = setPrec(cpuIdle * 100, 2) + "%";
	result["CPU CPU User: "] = setPrec(cpuUser * 100, 2) + "%";
	result["CPU System: "] = setPrec(cpuSystem * 100, 2) + "%";
}

float MonitorCpu::getCurrentLoad(int state)
{
	host_cpu_load_info_data_t	cpuinfo = {};
	mach_msg_type_number_t		count = HOST_CPU_LOAD_INFO_COUNT;
	unsigned long long			totalTicks = 0;

	if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count) == KERN_SUCCESS)
	{
		totalTicks = 0;
		for (int i = 0; i < 3; i++)
			totalTicks += cpuinfo.cpu_ticks[i];
		return (calcCpuLoad(cpuinfo.cpu_ticks[state], totalTicks, state));
	}
	else
		return (-1.0f);
}

float MonitorCpu::calcCpuLoad(unsigned long long idleTicks, unsigned long long totalTicks, int stateType)
{
	unsigned long long	totalTicksSinceLastTime;
	unsigned long long	idleTicksSinceLastTime;
	float				load = 0;
	
	totalTicksSinceLastTime = totalTicks - previousTotalTicks[stateType];
	idleTicksSinceLastTime = idleTicks - previousStateTicks[stateType];
	if (totalTicksSinceLastTime > 0)
		load = static_cast<float>(idleTicksSinceLastTime) / static_cast<float>(totalTicksSinceLastTime);
	previousTotalTicks[stateType] = totalTicks;
	previousStateTicks[stateType] = idleTicks;
	return (load);
}
