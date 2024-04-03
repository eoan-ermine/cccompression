#include <fstream>
#include <unordered_map>

namespace eoanermine::cccompression {

struct frequency_table {
    static frequency_table from_file(std::ifstream&);

    int at(char) const;
    
    auto begin();
    auto begin() const;

    auto end();
    auto end() const;
private:
    frequency_table() = default;
    std::unordered_map<char, int> table;
};

}