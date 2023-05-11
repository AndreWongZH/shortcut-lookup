#include "fileparser.hpp"
#include "helper.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void Explorer::load_data() {
  // read all the commands available in the directory path into memory

  std::filesystem::path dirPath = "./cmds";

  if (!std::filesystem::is_directory(dirPath)) {
    std::cout << "default command directory is empty" << std::endl;
    std::filesystem::create_directory(dirPath);
    std::cout << "command directory is created" << std::endl;
  }

  // look into each file
  for (const auto &file : std::filesystem::directory_iterator(dirPath)) {
    std::vector<Command> commands;
    std::string title;
    std::string temp;
    Command tempCmd;

    auto fullPath = dirPath.string() + "/" + file.path().filename().string();
    std::cout << fullPath << std::endl;

    std::ifstream File(fullPath);

    if (!File) {
      std::cout << "File does not exist" << std::endl;
    }

    if (File) {
      getline(File, title);

      while (getline(File, temp)) {
        std::stringstream ss(temp);
        std::string token;

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
      Explorer::data.insert(std::make_pair(title, commands));
    }

    File.close();
  }

}

void Explorer::print_data()
{
 
  for (auto d : Explorer::data) {
    std::cout << d.first << std::endl;
    for (auto v : d.second) {
      std::cout << v.name << std::endl;
      std::cout << v.desc << std::endl;

      std::cout << "" << std::endl;
    }
  }   
}

std::vector<std::string> Explorer::show_keys()
{
    std::vector<std::string> keys;
    for (const auto &key : data) {
        keys.push_back(key.first);
    }

    return keys;
}









