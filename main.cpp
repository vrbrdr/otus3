#include <iostream>
#include <random>

#include "args.h"
#include "game.h"
#include "storage.h"

int main(int argc, char const *argv[]) {
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