#pragma once
#include <exception>
#include <string>

void show_score_table();
void update_score_table(const std::string &user_name, int result);

class storage_exception : std::exception {
 private:
  const char *message;

 public:
  storage_exception(const char *_message) : message{_message} {};

  //const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
  //  return message;
  //}

  const char *what() const noexcept override {
    return message;
  }
};
