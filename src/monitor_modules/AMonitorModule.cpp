#include "AMonitorModule.hpp"

AMonitorModule::AMonitorModule() : moduleName()
{
}

AMonitorModule::AMonitorModule(std::string moduleName) : moduleName(moduleName)
{
}

AMonitorModule::AMonitorModule(AMonitorModule const &objToCopy)
{
	*this = objToCopy;
}

AMonitorModule::~AMonitorModule()
{
	result.clear();
}

AMonitorModule &AMonitorModule::operator=(AMonitorModule const &objToCopy)
{
	if (this != &objToCopy)
	{
		this->moduleName = objToCopy.moduleName;
		result = objToCopy.result;
	}
	return (*this);
}

std::map<std::string, std::string> const &AMonitorModule::getData(void) const
{
	return (result);
}

const std::string & AMonitorModule::getModuleName() const
{
	return (moduleName);
}

std::string AMonitorModule::exec(const char* cmd)
{
	char		buffer[128];
	std::string	result;
	FILE*		pipe = popen(cmd, "r");

	if (!pipe) throw std::runtime_error("popen() failed!");
	try
	{
		while (!feof(pipe))
		{
			if (fgets(buffer, 128, pipe) != NULL)
				result += buffer;
		}
	}
	catch (...)
	{
		pclose(pipe);
		throw;
	}
	pclose(pipe);
	return (result);
}
