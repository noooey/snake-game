#include <ncurses.h>

int main(){
  WINDOW *win1;
  WINDOW *win2;

  initscr();
  resize_term(25, 25);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_RED);
  init_pair(2, COLOR_WHITE, COLOR_YELLOW);

  border('*', '*', '*', '*', '*', '*', '*', '*');
  mvprintw(1, 1, "default");
  refresh();
  getch();

  win1 = newwin(20, 20, 3, 3);
  wbkgd(win1, COLOR_PAIR(1));
  wattron(win1, COLOR_PAIR(1));
  mvwprintw(win1, 1, 1, "new");
  wborder(win1, '@', '@', '@', '@', '@', '@', '@', '@');
  wrefresh(win1);

  getch();
  delwin(win1);
  getch();

  win2 = newwin(20, 20, 3, 3);
  wbkgd(win2, COLOR_PAIR(2));
  wattron(win2, COLOR_PAIR(2));
  mvwprintw(win2, 1, 1, "new2");
  wborder(win2, '@', '@', '@', '@', '@', '@', '@', '@');
  wrefresh(win2);

  getch();
  endwin();

  return 0;
}
