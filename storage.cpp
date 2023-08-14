#include "storage.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

static const char *SCORE_FILE_NAME = "hiscore_table.txt";

// 3 - maximum number of decimal digits per byte
static const size_t RESULT_MAX_LENGTH = sizeof(int) * 3;

bool read_score_line(const std::string &line, int &result,
                     std::string &user_name) {
  auto str_result =  line.substr(line.length() - RESULT_MAX_LENGTH);                     
  result = std::stoi(str_result);
  user_name = line.substr(0, line.length() - RESULT_MAX_LENGTH - 1);
  return true;
}

//name 11---
bool read_score_line(std::fstream &file, int &result, std::string &user_name) {
  std::string line;
  if (!std::getline(file, line)) {
    return false;
  }

  return read_score_line(line, result, user_name);
}

void write_score_result(std::fstream &file, const std::string &user_name,
                        int result) {
  std::string result_line = std::to_string(result);
  result_line = user_name + ' ' + result_line +
                std::string(RESULT_MAX_LENGTH - result_line.length(), ' ');
  file.write(result_line.c_str(), result_line.length());
  file.put('\n');
}

void show_score_table() {
  std::cout << "High scores table: " << std::endl;
  std::fstream file(SCORE_FILE_NAME, std::fstream::in);
  if (!file) {
    return;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
      std::cout << line << std::endl;
  }
}

void append_score_line(const std::string &user_name, int result) {
  std::fstream file(SCORE_FILE_NAME, std::fstream::app);
  if (!file) {
    throw storage_exception(
        (std::string("File opening error: ") + SCORE_FILE_NAME).c_str());
  }

  file.seekp(0, file.end);
  write_score_result(file, user_name, result);
}

void update_score_table(const std::string &user_name, int result) {
  std::fstream file(SCORE_FILE_NAME, std::fstream::out | std::fstream::in |
                                         std::fstream::binary);

  if (!file) {
    append_score_line(user_name, result);
    return;
  }

  int tmp_result;
  std::string tmp_user;
  for (;;) {
    auto line_pos = file.tellg();
    if (!read_score_line(file, tmp_result, tmp_user)) {
      append_score_line(user_name, result);
      return;

    } else if (tmp_user == user_name) {
      if (result < tmp_result) {
        file.seekp(line_pos);
        write_score_result(file, user_name, result);
      }
      return;
    }
  }
}
