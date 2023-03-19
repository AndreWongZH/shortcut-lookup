#include <string>

using namespace std;

string strip(const string& s) {
    auto start = s.begin();
    while (start != s.end() && isspace(*start)) {
        start++;
    }

    auto end = s.end();
    do {
        end--;
    } while (end != start && isspace(*end));

    return string(start, end + 1);
}