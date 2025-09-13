#include <algorithm>
#include <vector>
#include <iostream>


bool is_all_even(const auto& col)
{
    return std::all_of(col.begin(), col.end(), [](int val){return val % 2 == 0;});
}

bool is_all_positive(const auto& col)
{
    return std::all_of(col.begin(), col.end(), [](int val) {return val >= 0;});
}

int main()
{

    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};

    std::cout << "Is all even: " << (is_all_even(vec) ? "Yes" : "No") << "\n";
    std::cout << "Is all positivie: " << (is_all_positive(vec) ? "Yes" : "No") << "\n";    
}
