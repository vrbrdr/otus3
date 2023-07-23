#include "storage.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

static const char *score_file_name = "score_table.txt";
static const int RESULT_MAX_LENGTH = sizeof(int) * 3;

bool read_score_line(std::fstream &file, int &result, std::string &user_name) {
  std::string line;
  if (!std::getline(file, line)) {
    return false;
  }
  result = std::stoi(line);
  user_name = line.substr(RESULT_MAX_LENGTH + 1);

  return true;
}

void write_score_result(std::fstream &file, int result) {
  std::string str = std::to_string(result);
  int fill_size = RESULT_MAX_LENGTH - str.length();
  for (int i = 0; i < fill_size; ++i) {
    str = " " + str;
  }

  str += " ";

  file.write(str.c_str(), str.length());
}

void show_score_table() {
  std::cout << "Score table: " << std::endl;
  std::fstream file(score_file_name, std::fstream::in);
  if (!file.is_open()) {
    return;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  std::sort(lines.begin(), lines.end());

  for (auto &line : lines) {
    std::cout << line << std::endl;
  }
}

void append_score_line(std::string user_name, int result) {
  std::fstream file(score_file_name, std::fstream::app);
  if (!file) {
    throw storage_exception(
        (std::string("File opening error: ") + score_file_name).c_str());
  }

  file.seekp(0, file.end);
  write_score_result(file, result);
  file.write(user_name.c_str(), user_name.length());
  file.put('\n');
}

void update_score_table(std::string user_name, int result) {
  std::fstream file(score_file_name, std::fstream::out | std::fstream::in |
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
      if (result != tmp_result) {
        file.seekp(line_pos);
        write_score_result(file, result);
      }
      return;
    }
  }
}
