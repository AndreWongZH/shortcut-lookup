#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <ncurses.h>
#include <vector>

using namespace std;


struct TreeNode
{
  string value;
  string desc;
  vector<TreeNode> children;
};

int main() {
  // read all the commands available in the directory path into memory

  filesystem::path dirPath = "./cmds";

  if (!filesystem::is_directory(dirPath)) {
    cout << "default command directory is empty" << endl;
    filesystem::create_directory(dirPath);
    cout << "command directory is created" << endl;
  }

  string mytext;
  TreeNode rootCmd;

  for (const auto &file : filesystem::directory_iterator(dirPath)) {
    auto fullPath = dirPath.string() + "/" + file.path().filename().string();
    cout << fullPath << endl;

    ifstream File(fullPath);

    if (!File) {
      cout << "File does not exist" << endl;
    }

    if (File) {
      while (getline(File, mytext)) {
        cout << mytext << endl;
      }
    }

    File.close();
  }

  // show ncurse page
  {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    printw("Welcome");

    while (auto ch = getch()) {
      if (ch == KEY_F(1)) {
        printw("F1 key pressed");
      } else {
        printw(me.c_str());
      }
    }

    refresh();
    endwin();
  }


  return 0;
}