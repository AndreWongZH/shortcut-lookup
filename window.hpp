#include "ncurses.h"
#include <curses.h>
#include <iostream>
#include <string>
#include <vector>
#include "fileparser.hpp"

class Window_Manager {
private:
    Explorer explorer;

  int row;
  int col;

  WINDOW *main_win;
  int main_row;
  int main_col;

  WINDOW *side_win;
  std::vector<std::string> keys;
  int side_curr = 1;
  int side_row;
  int side_col;

  int win_curr = 0;

public:
  Window_Manager() {
    explorer = Explorer();

    initscr();
    getmaxyx(stdscr, row, col);
    std::cout << row << " " << col << std::endl;
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    refresh();

    side_win = create_win(col / 5, row, 0, 0);
    main_win = create_win((col / 5) * 4, row, 0, (col / 5) + 1);

    getmaxyx(side_win, side_row, side_col);
    getmaxyx(main_win, main_row, main_col);


    refresh();
  }

  ~Window_Manager() {
    // delwin(side_win);
    // delwin(main_win);
    endwin();
  }

  WINDOW *create_win(int width, int height, int starty, int startx);
  void update_side();
  void update_main();
  void highlight_side(int side_curr, attr_t attribute);
  int listen_key();
};
