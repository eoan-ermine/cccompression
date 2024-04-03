#pragma once

#include <fstream>
#include <unordered_map>

namespace eoanermine::cccompression {

class frequency_table {
    using Table = std::unordered_map<char, int>;
public:
    static frequency_table from_file(std::ifstream&);

    int at(char ch) const {
        return table.at(ch);
    }

    Table::iterator begin() {
        return table.begin();
    }

    Table::const_iterator begin() const {
        return table.begin();
    }

    Table::iterator end() {
        return table.end();
    }

    Table::const_iterator end() const {
        return table.end();
    }
private:
    frequency_table() = default;
    Table table;
};

}