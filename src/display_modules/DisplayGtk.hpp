#ifndef DISPLAYGTK_HPP
#define DISPLAYGTK_HPP

#include <iostream>
#include <map>
#include "gtk/gtk.h"

#include "AMonitorDisplay.hpp"

struct Widget
{
	GtkWidget *widgetModule;
	GtkWidget *widgetData;
	IMonitorModule *module;
};

class DisplayGtk : public AMonitorDisplay
{
public:
	DisplayGtk();
	DisplayGtk(DisplayGtk const &objToCopy);
	~DisplayGtk();

	DisplayGtk &operator = (DisplayGtk const &obj);

	void displayData(void);
	void updateData(void);

	int	start(void);

private:
	std::map<std::string, Widget> widgetModules;
	GtkApplication	*app;
	GtkWidget		*mainWindow;
};


#endif
