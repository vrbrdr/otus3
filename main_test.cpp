#include <string>

#include "storage.h"

int main(int argc, char const *argv[]) {
  update_score_table("user#12", 13);
  update_score_table("user#1", 2);
  update_score_table("user#20", 21);
  update_score_table("user#12", 123);

  update_score_table("user user user", 123456);
  update_score_table("user#7", 7);

  update_score_table("user user user", 1123456);

  show_score_table();

  return 0;
}
