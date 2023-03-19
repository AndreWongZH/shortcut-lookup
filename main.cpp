#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <ncurses.h>
#include <vector>
#include <unordered_map>

#include "helper.hpp"

using namespace std;


struct TreeNode
{
  string value;
  string desc;
  vector<TreeNode> children;
};

struct Command {
  string name;
  string desc;
};

struct Data {
  unordered_map<string, vector<Command>> cmdMap;
};

int main() {
  // read all the commands available in the directory path into memory

  filesystem::path dirPath = "./cmds";

  if (!filesystem::is_directory(dirPath)) {
    cout << "default command directory is empty" << endl;
    filesystem::create_directory(dirPath);
    cout << "command directory is created" << endl;
  }
  
  Data data;

  for (const auto &file : filesystem::directory_iterator(dirPath)) {
    vector<Command> commands;
    string title;
    string temp;
    Command tempCmd;

    auto fullPath = dirPath.string() + "/" + file.path().filename().string();
    cout << fullPath << endl;

    ifstream File(fullPath);

    if (!File) {
      cout << "File does not exist" << endl;
    }

    
    if (File) {
      getline(File, title);

      while (getline(File, temp)) {
        stringstream ss(temp);
        string token;

        for (int i = 0; i < 2; ++i) {
          getline(ss, token, ';');
          if (i == 0) {
            tempCmd.name = strip(token);
          } else {
            tempCmd.desc = strip(token);
          }
        }
        commands.push_back(tempCmd);
      }
      data.cmdMap[title] = commands;
    }

    File.close();
  }
  
  for (auto d : data.cmdMap) {
    cout << d.first << endl;
    for (auto v : d.second) {
      cout << v.name << endl;
      cout << v.desc << endl;

      cout << "" << endl;
    }
  }

  // show ncurse page
  {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    // mvprintw(1, 0, "Welcome");
    refresh();


    int sideHeight = LINES;
    int sideWidth = 30;
    // WINDOW *sidebar = create_newwin(sideHeight, sideWidth, 0, 0);

    int mainHeight = LINES; 
    int mainWidth = (COLS - sideWidth - 1);
    // WINDOW *mainpanel = create_newwin(mainHeight, mainWidth, 0, sideWidth + 1);

    // mvwprintw(sidebar, 1, 1, "Welcome");
    // wrefresh(sidebar);
    // while (auto ch = getch()) {
    //   if (ch == KEY_F(1)) {
    //     printw("F1 key pressed");
    //     return 0;
    //   }
    // }

    refresh();
    getch();
    // destroy_win(sidebar);
    // destroy_win(mainpanel);
    endwin();
  }


  return 0;
}