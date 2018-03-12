#include "DisplayGtk.hpp"

static gboolean monitorModuleCallback(DisplayGtk *screen)
{
	screen->updateData();
	return (true);
}

static void activate(GtkApplication *app, DisplayGtk *screen)
{
	(void)app;
	screen->displayData();
}

void gtk_remove_child_recursive(GtkWidget *widget)
{
	if (GTK_IS_CONTAINER(widget)) {
		GList *childList = gtk_container_get_children(GTK_CONTAINER(widget));
		while (childList != nullptr)
		{
			gtk_remove_child_recursive(GTK_WIDGET(childList->data));
			gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(childList->data));
			childList = childList->next;
		}
	}
}

DisplayGtk::DisplayGtk()
{
	app = gtk_application_new("cpp.ft_gkrellm", G_APPLICATION_FLAGS_NONE);
}

DisplayGtk::DisplayGtk(DisplayGtk const &objToCopy)
{
	*this = objToCopy;
}

DisplayGtk::~DisplayGtk()
{
	widgetModules.clear();
	g_object_unref(app);
}

DisplayGtk &DisplayGtk::operator=(DisplayGtk const &obj)
{
	if (this != &obj)
	{
		widgetModules = obj.widgetModules;
		app = obj.app;
		mainWindow = obj.mainWindow;
	}
	return (*this);
}

void DisplayGtk::displayData(void)
{
	this->mainWindow = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(this->mainWindow), "ft_gkrellm");
	gtk_window_set_default_size(GTK_WINDOW(this->mainWindow), 300, 200);
	gtk_container_set_border_width(GTK_CONTAINER(this->mainWindow), 10);

	GtkWidget *mainBox = gtk_flow_box_new();
	gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(mainBox), GTK_SELECTION_NONE);
	gtk_container_add(GTK_CONTAINER(this->mainWindow), mainBox);

	for (std::map<std::string, AMonitorModule *>::iterator it = modules.begin(); it != modules.end(); it++) {

		GtkWidget *moduleBox = gtk_flow_box_child_new();
		GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
		GtkWidget *widgetDataBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
		gtk_container_add(GTK_CONTAINER(moduleBox), hbox);
		GtkWidget *moduleName = gtk_label_new(it->first.c_str());
		gtk_box_pack_start(GTK_BOX(hbox), moduleName, false, false, 0);
		gtk_container_add(GTK_CONTAINER(hbox), widgetDataBox);
		gtk_container_add(GTK_CONTAINER(mainBox), moduleBox);
		Widget widgetMonitorModule = {};
		widgetMonitorModule.module = it->second;
		widgetMonitorModule.widgetModule = moduleBox;
		widgetMonitorModule.widgetData = widgetDataBox;
		widgetModules[it->second->getModuleName()] = widgetMonitorModule;
	}
	g_timeout_add(1200, reinterpret_cast<GSourceFunc>(monitorModuleCallback), this);
}

void DisplayGtk::updateData(void)
{
	std::map<std::string, std::string> data;

	for (std::map<std::string, Widget>::iterator itModule =  widgetModules.begin(); itModule != widgetModules.end(); itModule++) {
		GtkWidget *widget = itModule->second.widgetData;
		IMonitorModule *module = itModule->second.module;

		module->updateData();
		gtk_remove_child_recursive(widget);

		data = module->getData();
		for (std::map<std::string, std::string>::iterator itData = data.begin(); itData != data.end(); itData++)
		{
			GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
			std::string nameVal = itData->first + itData->second;
			gtk_box_pack_start(GTK_BOX(box), gtk_label_new(nameVal.c_str()), false, true, 0);
			gtk_container_add(GTK_CONTAINER(widget), box);
		}
	}
	gtk_widget_show_all(this->mainWindow);
}

int DisplayGtk::start()
{
	int status = 1;

	g_signal_connect(app, "activate", G_CALLBACK(activate), this);
	status = g_application_run(G_APPLICATION(app), 0, NULL);
	return (status);
}
