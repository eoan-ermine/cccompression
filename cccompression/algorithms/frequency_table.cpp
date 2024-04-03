#include "frequency_table.hpp"

namespace eoanermine::cccompression {

frequency_table frequency_table::from_file(std::ifstream& stream) {
    frequency_table res;

    constexpr auto read_size = std::size_t{4096};
    auto buf = std::string(read_size, '\0');
    while (stream.read(&buf[0], read_size)) {
        for (auto it = buf.begin(), end = it + stream.gcount(); it != end; ++it) {
            ++res.table[*it];
        }
    }

    return res;
}

}