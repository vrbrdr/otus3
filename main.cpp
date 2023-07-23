#include <iostream>
#include <random>

#include "game.h"
#include "storage.h"

bool parse_args(int argc, char **argv, bool &show_table_arg,
                int &max_number_arg);
void print_help();

int main(int argc, char **argv) {
  bool show_table_arg = false;
  int max_number_arg = -1;

  if (!parse_args(argc, argv, show_table_arg, max_number_arg)) {
    print_help();
    return -1;
  }

  if (show_table_arg) {
    show_score_table();
  } else {
    play(max_number_arg);
  }

  return 0;
}

bool parse_args(int argc, char **argv, bool &show_table_arg,
                int &max_number_arg) {
  //-table
  //-max N
  //-level N 1-3 (10,50,100)

  if (argc < 2) {
    return false;
  }

  auto cmd = std::string(argv[1]);
  if (cmd == "-table") {
    show_table_arg = true;
    return argc == 2;
  }

  if (argc != 3) {
    return false;
  }

  int num;
  try {
    num = std::stoi(argv[2]);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  if (cmd == "-max") {
    max_number_arg = num;
    return true;
  } else if (cmd == "-level") {
    switch (num) {
      case 1:
        max_number_arg = 10;
        return true;
      case 2:
        max_number_arg = 50;
        return true;
      case 3:
        max_number_arg = 100;
        return true;
      default:
        return false;
    }
  }

  return false;
}

void print_help() {
  using std::cout;
  using std::endl;

  cout << "usage: -max N|level N|-table" << endl;
  cout << "  -max N, N from 1 to 32767" << endl;
  cout << "  -level 1, N = 1|2|3" << endl;
  cout << "    -level 1 equals '-max 10'" << endl;
  cout << "    -level 2 equals '-max 50'" << endl;
  cout << "    -level 3 equals '-max 100'" << endl;
  cout << "  -table, show score and exit" << endl;
}