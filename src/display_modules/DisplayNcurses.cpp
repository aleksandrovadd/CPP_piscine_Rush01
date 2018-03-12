#include "DisplayNcurses.hpp"

DisplayNcurses::DisplayNcurses()
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	clear();
	refresh();
	start_color();
	init_pair(1, COLOR_GREEN, 0);
	init_pair(2, COLOR_RED, 0);
	init_pair(3, COLOR_BLUE, 0);
	init_pair(4, COLOR_CYAN, 0);
	init_pair(5, COLOR_WHITE, 0);
}

DisplayNcurses::DisplayNcurses(DisplayNcurses const &objToCopy)
{
	*this = objToCopy;
}

DisplayNcurses::~DisplayNcurses()
{
	endwin();
}

DisplayNcurses &DisplayNcurses::operator=(DisplayNcurses const &obj)
{
	(void)obj;
	return (*this);
}

void DisplayNcurses::displayData(void)
{
	std::map<std::string, AMonitorModule *>::iterator it;
	std::map<std::string, std::string> map;

	int row, col;
	getmaxyx(stdscr, row, col);
	int ch;

	while (1)
	{
		updateData();
		int y = 0;
		attron(A_BOLD);
		attron(COLOR_PAIR(3));
		box(stdscr, 0, 0);
		attroff(A_BOLD);
		attroff(COLOR_PAIR(3));

		attron(COLOR_PAIR(1));
		attron(A_BOLD);
		mvwprintw(stdscr, ++y, col / 2 - 14, "%s", "S Y S T E M    M O N I T O R");
		attroff(COLOR_PAIR(1));
		attroff(A_BOLD);
		
		if ((ch = getch()) == KEY_F(1))
			break;

		it = modules.begin();
		for (; it != modules.end(); it++)
		{
			attron(COLOR_PAIR(3));
			attron(A_BOLD);
			move(++y, 1);
			hline(ACS_HLINE, col - 2);
			attroff(COLOR_PAIR(3));
			attroff(A_BOLD);

			attron(COLOR_PAIR(1));
			attron(A_UNDERLINE);
			attron(A_BOLD);
			mvwprintw(stdscr, ++y, 2, "%s", (it->second->getModuleName()).c_str());
			attroff(A_UNDERLINE);
			attroff(A_BOLD);
			attroff(COLOR_PAIR(1));

			attron(COLOR_PAIR(4));
			map = it->second->getData();
			for (std::map<std::string, std::string>::iterator it = map.begin(); it != map.end(); it++)
				mvwprintw(stdscr, ++y, 2, "%s %s", (it->first).c_str(), (it->second).c_str());
			attroff(COLOR_PAIR(4));

			attron(COLOR_PAIR(3));
			attron(A_BOLD);
			move(++y, 1);
			hline(ACS_HLINE, col - 2);
			attroff(COLOR_PAIR(3));
			attroff(A_BOLD);
		}
		refresh();
		clear();
		curs_set(0);
	}

}

void DisplayNcurses::updateData(void)
{

	for (std::map<std::string, AMonitorModule *>::iterator it = modules.begin(); it != modules.end(); it++)
		it->second->updateData();
}

int DisplayNcurses::start()
{
	this->displayData();

	return 0;
}
