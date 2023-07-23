#include <ctime>
#include <iostream>
#include <random>
#include <string>

#include "storage.h"

void game(std::string user_name, int max_number_arg);
bool ask_new_game();

void play(int max_number_arg) {
  std::string user_name;

  std::cout << "Введите имя" << std::endl;
  std::cin >> user_name;

  std::mt19937 engine;
  std::random_device device;
  engine.seed(device());

  for (;;) {
    int rnd = engine() % max_number_arg;
    game(user_name, rnd);

    if (!ask_new_game()) {
      break;
    }
  }
}

bool ask_new_game() {
  char answer;
  for (;;) {
    std::cout << "Хотите сыграть еще раз (y/n): ";
    std::cin >> answer;

    switch (answer) {
      case 'y':
      case 'Y':
        return true;

      case 'n':
      case 'N':
        return false;

      default:
        std::cout << "Не понятный ответ: " << answer << std::endl;
    }
  }
}

int get_user_number(bool firstTime) {
  if (firstTime) {
    std::cout << "Введите число: ";
  } else {
    std::cout << ", введите число еще раз: ";
  }

  int user_input_number;
  std::cin >> user_input_number;
  return user_input_number;
}

bool check_result(int rnd, int user_input_number) {
  if (rnd < user_input_number) {
    std::cout << "Искомое число меньше";
    return false;
  } else if (user_input_number < rnd) {
    std::cout << "Искомое число больше";
    return false;
  } else {
    return true;
  }
}

void save_result(std::string user_name, int result) {
  std::cout << user_name << ", вы угадали число за " << result << " попыток"
            << std::endl;

  update_score_table(user_name, result);
  show_score_table();
}

void game(std::string user_name, int rnd) {
  for (int i = 1;; i++) {
    int user_input_number = get_user_number(i == 1);
    if (check_result(rnd, user_input_number)) {
      save_result(user_name, i);
      break;
    }
  }
}