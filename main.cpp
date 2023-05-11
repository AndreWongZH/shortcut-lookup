#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include "window.hpp"

using namespace std;

struct TreeNode
{
  string value;
  string desc;
  vector<TreeNode> children;
};

int main() {
    //Explorer explorer = Explorer();
    //explorer.print_data();
  
    //cout << "keys available:" << endl;
    //explorer.show_keys();

    Window_Manager win = Window_Manager();

    win.update_side();
    win.update_main();

    while (true)
        if (win.listen_key() == 1)
            break;

  return 0;
}
