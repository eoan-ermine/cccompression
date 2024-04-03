#include <config.hpp>

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>

#include "algorithms/frequency_table.hpp"
#include "algorithms/huffman_tree.hpp"

namespace fs = std::filesystem;
namespace po = boost::program_options;

void print_help(const po::options_description& visible) {
    std::cout << "OVERVIEW: " << PROJECT_NAME << " compression tool\n"
              << std::endl;
    std::cout << "USAGE: " << PROJECT_NAME << " [options] file\n" << std::endl;
    std::cout << visible << std::endl;
}

void print_version() {
    std::cout << PROJECT_NAME << " version " << PROJECT_VERSION << std::endl;
    std::cout << "Includes: ";
    std::cout << "Boost " << BOOST_VERSION / 100000 << "."
              << BOOST_VERSION / 100 % 1000 << "." << BOOST_VERSION % 100
              << std::endl;
}

int main(int argc, char *argv[]) {
  po::options_description visible("OPTIONS");
  po::options_description hidden("HIDDEN");

  // clang-format off
  visible.add_options()
    ("help", "produce help message")
    ("version", "Print version information")
  ;
  hidden.add_options()
    ("inputs", po::value<std::string>());
  // clang-format on

  po::positional_options_description desc_pos;
  desc_pos.add("inputs", 1);
  po::options_description all;
  all.add(visible).add(hidden);

  po::variables_map vm;
  try {
    po::store(po::command_line_parser(argc, argv)
                  .options(all)
                  .positional(desc_pos)
                  .run(),
              vm);
  } catch (po::error &e) {
    return EXIT_FAILURE;
  }
  po::notify(vm);

  if (vm.count("help")) {
    print_help(visible);
    return EXIT_SUCCESS;
  } else if (vm.count("version")) {
    print_version();
    return EXIT_SUCCESS;
  } else if (vm.count("inputs")) {
    auto path = fs::path(vm["inputs"].as<std::string>());
    auto status = fs::status(path);
    if (status.type() != fs::file_type::regular) {
      std::cerr << "Can't open " << path << std::endl;
      return EXIT_FAILURE;
    }
    std::ifstream fstream{path, std::ios::binary};
    
    auto frequency_table = eoanermine::cccompression::frequency_table::from_file(fstream);
    auto huffman_tree = eoanermine::cccompression::huff_tree::create(frequency_table);
    auto prefix_table = huffman_tree->table();

    return EXIT_SUCCESS;  
  } else {
    print_help(visible);
    return EXIT_FAILURE;
  }
}