#include "args.h"

#include <iostream>
#include <string>
#include <array>

bool parse_args(int argc, const char **argv, bool &show_table_arg,
                int &max_number_arg) {
  //-table
  //-max N
  //-level N 1-3 (10,50,100)

  if (argc == 1) {
    max_number_arg = DEFAULT_MAX_NUMBER;
    return true;
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
    return false;
  }

  if (cmd == "-max") {
    if (num >= MAX_NUMBER_LOW_VALUE && num <= MAX_NUMBER_HI_VALUE) {
      max_number_arg = num;
      return true;
    } else {
      return false;
    }
  } else if (cmd == "-level") {
  /*
    switch (num) {
      case 1:
        max_number_arg = MAX_NUMBER_LEVEL1;
        return true;

      case 2:
        max_number_arg = MAX_NUMBER_LEVEL2;
        return true;

      case 3:
        max_number_arg = MAX_NUMBER_LEVEL3;
        return true;

      default:
        return false;
    }*/

    static const std::array<int, 3> levels = {MAX_NUMBER_LEVEL1, MAX_NUMBER_LEVEL2, MAX_NUMBER_LEVEL3};
      
    if (num < 1 || num > levels.max_size()) {
      return false;
    }

    max_number_arg = levels[num - 1];
    return true;   
  }

  return false;
}

void print_help() {
  using std::cout;
  using std::endl;

  cout << "usage: -max N|level N|-table" << endl;
  cout << "  -max N, N from " << MAX_NUMBER_LOW_VALUE << " to " << MAX_NUMBER_HI_VALUE << endl;
  cout << "  -level 1, N = 1|2|3" << endl;
  cout << "    -level 1 equals '-max 10'" << endl;
  cout << "    -level 2 equals '-max 50'" << endl;
  cout << "    -level 3 equals '-max 100'" << endl;
  cout << "  -table, show score and exit" << endl;
}