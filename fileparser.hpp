#include <unordered_map>
#include <string>
#include <vector>


struct Command {
    std::string name;
    std::string desc;
};

struct CommandData {
    std::vector<Command> data;
    std::string filename;
};

class Explorer {
private:
    std::unordered_map<std::string, std::vector<Command>> data;

public:
    Explorer() : data{} {
        load_data();
    }

    void load_data();
    void print_data();
    std::vector<std::string> show_keys();
    std::vector<Command> get(std::string key) {
        return data.at(key);
    }
};

