#include <algorithm>
#include <cstdint>
#include <vector>

#include <iostream>

void print_vec(std::vector<int> &vec) {

  std::cout << "[";
  for (const auto &elm : vec) {

      std::cout << std::to_string(elm) << " ";
  }

  std::cout << "]\n";



}

int main() {

    std::vector<int> vec = {-1, 3, 10, 44, 4, 11, 7, 5, 22, 4, 3, 2, 22};
  print_vec(vec);

  vec.erase(
      std::remove_if(vec.begin(), vec.end(), [](int elm) { return elm <= 10; }),
      vec.end());

  print_vec(vec);

}
