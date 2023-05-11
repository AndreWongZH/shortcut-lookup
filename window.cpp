#include "window.hpp"
#include <curses.h>

WINDOW *Window_Manager::create_win(int width, int height, int starty,
                                   int startx) {
  WINDOW *win = newwin(height, width, starty, startx);
  box(win, 0, 0);

  wrefresh(win);

  return win;
}

void Window_Manager::update_side() {
  Window_Manager::keys = explorer.show_keys();

  for (int i = 1; i <= keys.size(); ++i) {
    mvwprintw(side_win, i, 2, "%s", keys.at(i - 1).c_str());
    wrefresh(side_win);
    refresh();
  }
  highlight_side(side_curr, A_STANDOUT);
}

void Window_Manager::update_main() {
  werase(main_win);
  box(main_win, 0, 0);
  wrefresh(main_win);
  refresh();

  auto cmdVec = explorer.get(keys.at(side_curr - 1));

  for (int i = 0; i < cmdVec.size(); ++i) {
    mvwprintw(main_win, i + 1, 2, "%s", cmdVec.at(i).name.c_str());
    wrefresh(main_win);
    refresh();
  }
}

void Window_Manager::highlight_side(int row, attr_t attribute) {
  mvwchgat(side_win, row, 2, side_col - 3, attribute, 0, NULL);
  wrefresh(side_win);
  refresh();
}

int Window_Manager::listen_key() {
  int ch = getch();
  switch (ch) {
  case 'q':
    return 1;
  case KEY_UP:
    highlight_side(side_curr, A_NORMAL);
    if (side_curr > 1) {
      side_curr--;
      update_main();
    }
    break;
  case KEY_DOWN:
    highlight_side(side_curr, A_NORMAL);
    if (side_curr < keys.size()) {
      side_curr++;
      update_main();
    }
    break;
  }

  highlight_side(side_curr, A_STANDOUT);

  return 0;
}
