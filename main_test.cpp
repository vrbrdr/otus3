#include <iostream>
#include <string>
#include <vector>

#include "args.h"
#include "storage.h"

#define CHECK_TEST(res_sum, res_cur) \
  if (!(res_cur)) {                  \
    res_sum = false;                 \
    test_error(__FILE__, __LINE__);  \
  }

bool test_args();

int main(int argc, char const *argv[]) {
  test_args();

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

bool test_arg(std::vector<const char *> arg, bool show_table_expected,
              int max_number_expected, bool result_expected) {
  bool show_table_parsed = false;
  int max_number_parsed = 0;

  bool result = parse_args(arg.size(), (const char **)arg.data(),
                           show_table_parsed, max_number_parsed);

  if (result_expected != result) {
    return false;
  }

  if (!result) {
    return true;
  }

  if (show_table_parsed != show_table_expected) {
    return false;
  }

  if (max_number_parsed != max_number_expected) {
    return false;
  }

  return true;
}

bool test_error(const char *file, int line) {
  std::cout << "Test failed, line:  " << line << ", file: " << file
            << std::endl;

  return false;
}

bool test_args() {
  //
  //-table
  //-max N
  //-level N 1-3 (10,50,100)

  bool res = true;
  CHECK_TEST(res, test_arg({""}, false, DEFAULT_MAX_NUMBER, true))
  CHECK_TEST(res, test_arg({"", "-table"}, true, 0, true))
  CHECK_TEST(res, test_arg({"", "-table1"}, false, 0, false))
  CHECK_TEST(res, test_arg({"", "--table"}, false, 0, false))
  CHECK_TEST(res, test_arg({"", "-table", "-max"}, false, 0, false))
  CHECK_TEST(res, test_arg({"", "-table", "-max", "10"}, false, 0, false))
  CHECK_TEST(res, test_arg({"", "-table", "-level", "1"}, false, 0, false))
  CHECK_TEST(res, test_arg({"", "-table"}, true, 0, true))
  CHECK_TEST(res, test_arg({"", "-max"}, false, 0, false))
  CHECK_TEST(res, test_arg({"", "-max", "10"}, false, 10, true))
  CHECK_TEST(res, test_arg({"", "-max", "123"}, false, 123, true))
  CHECK_TEST(res, test_arg({"", "-max", std::to_string(MAX_NUMBER_HI_VALUE).c_str()}, false, MAX_NUMBER_HI_VALUE, true))
  CHECK_TEST(res, test_arg({"", "-max", std::to_string(MAX_NUMBER_HI_VALUE+1).c_str()}, false, 0, false))
  CHECK_TEST(res, test_arg({"", "-max", std::to_string(MAX_NUMBER_LOW_VALUE).c_str()}, false, MAX_NUMBER_LOW_VALUE, true))
  CHECK_TEST(res, test_arg({"", "-max", std::to_string(MAX_NUMBER_LOW_VALUE-1).c_str()}, false, 0, false))
  CHECK_TEST(res, test_arg({"", "-max", "12345678901234567"}, false, 123, false))
  CHECK_TEST(res, test_arg({"", "-max", "-level", "1"}, false, 0, false))
  CHECK_TEST(res, test_arg({"", "-level", "1"}, false, MAX_NUMBER_LEVEL1, true))
  CHECK_TEST(res, test_arg({"", "-level", "2"}, false, MAX_NUMBER_LEVEL2, true))
  CHECK_TEST(res, test_arg({"", "-level", "3"}, false, MAX_NUMBER_LEVEL3, true))

  return res;
}
