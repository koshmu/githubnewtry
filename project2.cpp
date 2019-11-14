#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <map>

// adds words to a vector and returns it
std::vector<std::string> file_import(void) {
  std::ifstream input("common_passwords.txt");
  std::vector<std::string> dictionary;
  while (input.good()) {
    std::string word;
    if (!input.good()) {
      break;
    }
    while (input >> word) {
      dictionary.push_back(word);
    }
  }
  return dictionary;
}

// checks if word is similar
std::map<std::string, int> check_validity(
    std::string passcode, std::string list_word,
    std::map<std::string, int>& map_to_return) {
  int counter = 0;
  // find the biggest word between both password and the dictionary word in check
  int end = std::max(static_cast<int>(passcode.size()),
                     static_cast<int>(list_word.size()));
  for (int i = 0; i < end; i++) {
    if (passcode[i] != list_word[i]) {
      counter++;
    }
  }
  map_to_return.insert(std::pair<std::string, int>(list_word, counter));
  return map_to_return;
}

// prints out similar words
void print(std::map<std::string, int>& map_of_words, int number,
           std::string word) {
  std::cout << "The most similar passwords to " << word << " are:" << std::endl;

  for (auto item : map_of_words) {
    if (item.second == number) {
      std::cout << item.first << ", ";
    }
  }
  std::cout << std::endl;
  std::cout << "All of which are " << number << " character(s) different."
            << std::endl;
}

void distance_check(std::string word) {
    //Check similarity between two words in password with distance check
  std::map<std::string, int> return_map;

  std::vector<std::string> dictionary = file_import();

  // Check each word in common passwords dictionary with password for similarity
  std::for_each(dictionary.begin(), dictionary.end(),
                [&](std::string common_word) {
                  check_validity(word, common_word, return_map);
                });

  // Find the minimum value in the dictionary of passwords created
  auto min_item =
      std::min_element(return_map.begin(), return_map.end(),
                       [](const auto& last_number, const auto& current_number) {
                         return last_number.second < current_number.second;
                       });

  int number = min_item->second;
  print(return_map, number, word);
}

int main() {
  std::string password;
  std::cout << "Give me a password:" << std::endl;
  std::cin >> password;
  std::cout << "You provided a password of " << password << std::endl;
  distance_check(password);
}