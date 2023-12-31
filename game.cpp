#include <ctime>
#include <iostream>
#include <random>
#include <string>

#include "storage.h"

void game(const std::string &user_name, int rnd);
bool ask_new_game();

void play(int max_number_arg) {
  std::string user_name;

  std::cout << "Enter your name: " << std::endl;
  //user_name = std::cin.getline();
  getline(std::cin >> std::ws,user_name);

  std::mt19937 engine;
  std::random_device device;
  engine.seed(device());
  std::uniform_int_distribution<int> distr(0, max_number_arg - 1);
 
  for (;;) {
    //int rnd = engine() % max_number_arg;
    int rnd = distr(engine);

    game(user_name, rnd);

    if (!ask_new_game()) {
      std::cout << "Goodbye!" << std::endl;
      break;
    }
  }
}

bool ask_new_game() {
  char answer;
  for (;;) {
    std::cout << "Do you want to play again? (y/n): ";
    std::cin >> answer;

    switch (answer) {
      case 'y':
      case 'Y':
        return true;

      case 'n':
      case 'N':
        return false;

      default:
        std::cout << "Unknown answer: " << answer << std::endl;
    }
  }
}

int get_user_number(bool firstTime) {
  if (firstTime) {
    std::cout << "try to guess the number: ";
  } else {
    std::cout << ", try to guess the number again: ";
  }

  int user_input_number;
  std::cin >> user_input_number;
  return user_input_number;
}

bool check_result(int rnd, int user_input_number) {
  if (rnd == user_input_number) {
    std::cout << "you win!" << std::endl;
    return true;
  } 
 
   const bool less = rnd < user_input_number;
   std::cout << (less?"less":"greater") << " than " << user_input_number << std::endl;
   return false;
}

void game(const std::string &user_name, int rnd) {
  for (int i = 1;; i++) {
    int user_input_number = get_user_number(i == 1);
    if (check_result(rnd, user_input_number)) {
      std::cout << user_name << ", you guessed the number in " << i
                << " attempts" << std::endl;
      update_score_table(user_name, i);
      show_score_table();

      break;
    }
  }
}