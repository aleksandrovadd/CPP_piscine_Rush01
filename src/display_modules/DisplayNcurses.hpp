#ifndef DISPLAYNCURSES_HPP
#define DISPLAYNCURSES_HPP

#include "AMonitorDisplay.hpp"

#include <ncurses.h>
#include <sys/ioctl.h>

class DisplayNcurses : public AMonitorDisplay
{
public:
	DisplayNcurses();
	DisplayNcurses(DisplayNcurses const &objToCopy);
	~DisplayNcurses();

	DisplayNcurses &operator = (DisplayNcurses const &obj);

	void displayData(void);
	void updateData(void);
	int start();

private:

};

#endif
