#include <string>

#include <iostream>

void reverse(std::string &str) {

  if (!str.empty()) {

      auto start = str.begin();
      auto end = str.end() - 1;

    while (start < end) {
      *end = (*start) ^ (*end);
      *start = (*end) ^ (*start);
      *end = (*start) ^ (*end);

      start = start + 1;
      end = end - 1;
    }
  }




}

int main() {

  std::string test = "test";

  std::cout << test << "\n";
  reverse(test);
  std::cout << test << "\n";


  test = "Palindrom";
  std::cout << test << "\n";
  reverse(test);
  std::cout << test << "\n";


  test = "abcba";
  std::cout << test << "\n";
  reverse(test);
  std::cout << test << "\n";


}
